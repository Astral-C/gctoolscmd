# Shell Integration

#  Linux

This will depend on file manager, below are examples for a few common file managers. Feel free to contribute some!

## Archive / Compressed Files
### Thunar

Make sure you have the custom actions plugin installed and add the following to your `uca.xml`. May need some tweaking.

```xml
<actions>
<action>
	<icon>archive</icon>
	<name>SZS Compress</name>
	<submenu>Nintendo</submenu>
	<command>gctools -i %f -p -c YAZ0</command>
	<description></description>
	<range></range>
	<patterns>*</patterns>
	<directories/>
</action>
<action>
	<icon>archive</icon>
	<name>SZP Compress</name>
	<submenu>Nintendo</submenu>
	<command>gctools -i %f -p -c YAY0</command>
	<description></description>
	<range></range>
	<patterns>*</patterns>
	<directories/>
</action>
<action>
	<icon>archive</icon>
	<name>Pack Archive</name>
	<submenu>Nintendo</submenu>
	<command>gctools -i %f -p </command>
	<description></description>
	<range></range>
	<patterns>*</patterns>
	<directories/>
</action>
<action>
	<icon>cm_extractfiles</icon>
	<name>Extract Archive</name>
	<submenu>Nintendo</submenu>
	<command>gctools -i %f -x</command>
	<description></description>
	<range></range>
	<patterns>*.szp;*.szs;*.arc</patterns>
	<other-files/>
</action>
```

### Nautilus

Small example Nautilus script for calling gctoolscmd. Modify as needed referencing the help menu.

#### Extract
```bash
    #!/bin/bash
    # This one extracts a given archive
    FILEPATH=`echo $NAUTILUS_SCRIPT_SELECTED_URIS | sed 's@file://@@g'`

    if [[ ($FILEPATH == "*.szp") || ($FILEPATH == "*.arc") || ($FILEPATH == "*.szs") ]]
    then
        gctools -i $FILEPATH -x
    fi

    exit 0
```

## BTI

### Mime Type

Install mime type with `xdg-mime install --mode user bti-mime.xml` for user `sudo xdg-mime install --mode system bti-mime.xml` for system

Update mime database with `update-mime-database .local/share/mime/` for user `sudo update-mime-database /usr/share/mime/` for system

```xml
<?xml version="1.0" encoding="utf-8"?>
<mime-info xmlns="http://www.freedesktop.org/standards/shared-mime-info">
<mime-type type="image/bti">
  <comment>BTI image</comment>
  <comment xml:lang="zh_TW">BTI 影像</comment>
  <comment xml:lang="zh_CN">BTI 图像</comment>
  <comment xml:lang="vi">Ảnh BTI</comment>
  <comment xml:lang="uk">зображення BTI</comment>
  <comment xml:lang="tr">BTI görüntüsü</comment>
  <comment xml:lang="sv">BTI-bild</comment>
  <comment xml:lang="sr">ПНГ слика</comment>
  <comment xml:lang="sq">figurë BTI</comment>
  <comment xml:lang="sl">Slikovna datoteka BTI</comment>
  <comment xml:lang="si">BTI රූපය</comment>
  <comment xml:lang="sk">Obrázok BTI</comment>
  <comment xml:lang="ru">Изображение BTI</comment>
  <comment xml:lang="ro">Imagine BTI</comment>
  <comment xml:lang="pt_BR">Imagem BTI</comment>
  <comment xml:lang="pt">imagem BTI</comment>
  <comment xml:lang="pl">Obraz BTI</comment>
  <comment xml:lang="oc">imatge BTI</comment>
  <comment xml:lang="nn">BTI-bilete</comment>
  <comment xml:lang="nl">BTI-afbeelding</comment>
  <comment xml:lang="nb">BTI-bilde</comment>
  <comment xml:lang="ms">Imej BTI</comment>
  <comment xml:lang="lv">BTI attēls</comment>
  <comment xml:lang="lt">BTI paveikslėlis</comment>
  <comment xml:lang="ko">BTI 그림</comment>
  <comment xml:lang="kk">BTI суреті</comment>
  <comment xml:lang="ka">BTI გამოსახულება</comment>
  <comment xml:lang="ja">BTI 画像</comment>
  <comment xml:lang="it">Immagine BTI</comment>
  <comment xml:lang="is">BTI mynd</comment>
  <comment xml:lang="id">Citra BTI</comment>
  <comment xml:lang="ia">Imagine BTI</comment>
  <comment xml:lang="hu">BTI-kép</comment>
  <comment xml:lang="hr">BTI slika</comment>
  <comment xml:lang="he">תמונת BTI</comment>
  <comment xml:lang="gl">imaxe BTI</comment>
  <comment xml:lang="ga">íomhá BTI</comment>
  <comment xml:lang="fur">imagjin BTI</comment>
  <comment xml:lang="fr">image BTI</comment>
  <comment xml:lang="fo">BTI mynd</comment>
  <comment xml:lang="fi">BTI-kuva</comment>
  <comment xml:lang="eu">BTI irudia</comment>
  <comment xml:lang="es">imagen BTI</comment>
  <comment xml:lang="eo">BTI-bildo</comment>
  <comment xml:lang="en_GB">BTI image</comment>
  <comment xml:lang="el">Εικόνα BTI</comment>
  <comment xml:lang="de">BTI-Bild</comment>
  <comment xml:lang="da">BTI-billede</comment>
  <comment xml:lang="cy">Delwedd BTI</comment>
  <comment xml:lang="cs">obrázek BTI</comment>
  <comment xml:lang="ca">imatge BTI</comment>
  <comment xml:lang="bg">Изображение — BTI</comment>
  <comment xml:lang="be@latin">Vyjava BTI</comment>
  <comment xml:lang="be">выява BTI</comment>
  <comment xml:lang="az">BTI rəsmi</comment>
  <comment xml:lang="ar">صورة BTI</comment>
  <comment xml:lang="af">BTI-beeld</comment>
  <acronym>BTI</acronym>
  <expanded-acronym>Binary Texture Image</expanded-acronym>
  <glob pattern="*.bti"/>
</mime-type>
</mime-info>

```

### Thumbnailer
Create `/usr/share/thumbnailers/bti.thumbnailer` with contents
```
[Thumbnailer Entry]
Version=1.0
Encoding=UTF-8
Type=X-Thumbnailer
Name=BTI Thumbnailer
Exec=/usr/bin/gctools -i %i -o %o -t
MimeType=image/bti;
```
Set `/usr/bin/gctools` to your installed gctools path

## Windows

## CUATION: This section is in developement! Directions may or may not be correct!

Add entries to your registry, [this stackoverflow thread](https://stackoverflow.com/questions/20449316/how-add-context-menu-item-to-windows-explorer-for-folders) has a few examples.
