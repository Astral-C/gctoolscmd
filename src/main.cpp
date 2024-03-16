#include <thread>
#include <filesystem>
#include <Archive.hpp>
#include <Compression.hpp>
#include <argparse/argparse.hpp>
#include <QApplication>
#include <QMessageBox>
#include <QLabel>
#include <QLayout>


void ExtractFolder(std::shared_ptr<Archive::Folder> folder){
    std::filesystem::create_directory(folder->GetName());
    std::filesystem::current_path(std::filesystem::current_path() / folder->GetName());

    for(auto file : folder->GetFiles()){
        bStream::CFileStream extractFile(file->GetName(), bStream::Endianess::Big, bStream::OpenMode::Out);
        extractFile.writeBytes(file->GetData(), file->GetSize());
    }

    for(auto subdir : folder->GetSubdirectories()){
        ExtractFolder(subdir);
    }

    std::filesystem::current_path(std::filesystem::current_path().parent_path());
}

void PackFolder(std::shared_ptr<Archive::Rarc> arc, std::shared_ptr<Archive::Folder> folder, std::filesystem::path path){
    std::filesystem::current_path(path);
    
    for (auto const& dir_entry : std::filesystem::directory_iterator(path)){
        if(std::filesystem::is_directory(dir_entry.path())){
            std::shared_ptr<Archive::Folder> subdir = Archive::Folder::Create(arc);
            subdir->SetName(dir_entry.path().filename().string());
            folder->AddSubdirectory(subdir);
            
            PackFolder(arc, subdir, dir_entry.path());

        } else {
            std::shared_ptr<Archive::File> file = Archive::File::Create();

            bStream::CFileStream fileStream(dir_entry.path(), bStream::Endianess::Big, bStream::OpenMode::In);
            
            uint8_t* fileData = new uint8_t[fileStream.getSize()];
            fileStream.readBytesTo(fileData, fileStream.getSize());
            
            file->SetData(fileData, fileStream.getSize());
            file->SetName(dir_entry.path().filename().string());

            folder->AddFile(file);

            delete[] fileData;
        }
    }
    std::filesystem::current_path(std::filesystem::current_path().parent_path());
}

void PackArchive(std::filesystem::path path, Compression::Format format, int level){
    std::shared_ptr<Archive::Rarc> archive = Archive::Rarc::Create();
    std::shared_ptr<Archive::Folder> root = Archive::Folder::Create(archive);
    archive->SetRoot(root);
    root->SetName(path.filename().string());

    std::string ext = ".arc";
    if(format == Compression::Format::YAY0){
        ext = ".szp";
    } else if (format == Compression::Format::YAZ0){
        ext = ".szs";
    }

    PackFolder(archive, root, std::filesystem::current_path() / path);

    archive->SaveToFile(path.filename().string()+ext, format, (uint8_t)(level % 9));


}

int main(int argc, char* argv[]){
    QApplication app(argc, argv);
    int level; //compression level for yaz0

    argparse::ArgumentParser gctools("gctoolscmd", "0.0.1", argparse::default_arguments::help);

    gctools.add_argument("-i", "--input").required().help("File/Directory to operate on");
    gctools.add_argument("-l", "--level").help("Compression level for yaz0 compression (0-9)").default_value(7).store_into(level);
    gctools.add_argument("-c", "--compress").help("Compression method to use [YAY0, yay0, YAZ0, yaz0]");
    gctools.add_argument("-x", "--extract").help("Extract input archive").flag();
    gctools.add_argument("-p", "--pack").help("Pack input folder").flag();

    try {
        gctools.parse_args(argc, argv);
    } catch(const std::exception& e){
        std::cerr << e.what() << std::endl;
        std::cerr << gctools;
        return 1;
    }

    auto path = std::filesystem::path(gctools.get<std::string>("--input"));

    if(!std::filesystem::exists(path)){
        std::cerr << "Couldn't find path " << path.string() << std::endl;
        return 1;
    }

    if(gctools.is_used("--extract")){
        if(std::filesystem::is_directory(path)){
            std::cerr << path.string() << " is a directory" << std::endl;
            return 1;
        }

        std::shared_ptr<Archive::Rarc> archive = Archive::Rarc::Create();
        
        bStream::CFileStream archiveStream(path.string(), bStream::Endianess::Big, bStream::OpenMode::In);
        if(!archive->Load(&archiveStream)){
            std::cerr << "Couldn't parse file " << path.string() << std::endl;
            return 1;
        }

        ExtractFolder(archive->GetRoot());

    } else if(gctools.is_used("--pack")){
        if(!std::filesystem::is_directory(path)){
            std::cerr << path.string() << " is not a directory" << std::endl;
            return 1;
        }

        Compression::Format format = Compression::Format::None;

        if(gctools.is_used("--compress")){
            if(gctools.get("--compress")== "YAY0" || gctools.get("--compress") == "yay0"){
                format = Compression::Format::YAY0;
            } else if(gctools.get("--compress") == "YAZ0" || gctools.get("--compress") == "yaz0"){
                format = Compression::Format::YAZ0;
            }
        }

        QMessageBox msg(QMessageBox::NoIcon, "GCTools", "<h4 align='center'>Compressing Archive</h4>", QMessageBox::NoButton);
        if(format != Compression::Format::None){
            msg.setStandardButtons(QMessageBox::NoButton);
            msg.setModal(true);
            
            // Hack to make it look a little nicer.
            auto labelIcon = msg.findChild<QLabel*>("qt_msgboxex_icon_label");
            if (labelIcon) {
                labelIcon->setMaximumSize(QSize(0, 0));
            }
            auto layout = msg.findChild<QGridLayout*>();
            if (layout) {
                layout->setSpacing(0);
                layout->setContentsMargins(0, 10, 12, 10);
            }

            msg.open();
            
            // Call this three times as a complete hack so it draws the ui. Very funny!
            QCoreApplication::processEvents();
            QCoreApplication::processEvents();
            QCoreApplication::processEvents();
        }

        PackArchive(path, format, level);
        if(format != Compression::Format::None) msg.close();
    }



    return 0;
}