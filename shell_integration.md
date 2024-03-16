# Shell Integration

##  Linux

This will depend on file manager, below are examples for a few common file managers. Feel free to contribute some!

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

## Windows

## CUATION: This section is in developement! Directions may or may not be correct!

Add entries to your registry, [this stackoverflow thread](https://stackoverflow.com/questions/20449316/how-add-context-menu-item-to-windows-explorer-for-folders) has a few examples.