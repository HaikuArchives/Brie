## BeOS Makefile for BRIE ##
## Author: Sikosis
## Created for BRIE (http://brie.sf.net/)

## Application Specific Settings ---------------------------------------------

# specify the name of the binary
NAME= BRIE
# specify the type of binary
#	APP:	Application
#	SHARED:	Shared library or add-on
#	STATIC:	Static library archive
#	DRIVER: Kernel Driver
TYPE= APP

#	specify the source files to use
#	Note that spaces in folder names do not work well with this makefile.
SRCS= brie.cpp AboutWindow.cpp AboutWindowView.cpp FileWindow.cpp FileWindowView.cpp NewProjectWindow.cpp NewProjectWindowView.cpp ProjectWindow.cpp ProjectWindowView.cpp PropertiesWindow.cpp PropertiesWindowView.cpp ToolboxWindow.cpp ToolboxWindowView.cpp URLView.cpp HelpTipWindow.cpp HelpTipView.cpp
# end of srcs

#	specify the resource files to use
RSRCS= brie.rsrc

#	specify additional libraries to link against
LIBS= be root

#	specify additional paths to directories 
LIBPATHS=

#	additional paths to look for system headers
SYSTEM_INCLUDE_PATHS =

#	additional paths to look for local headers
LOCAL_INCLUDE_PATHS =

#	specify the level of optimization that you desire - NONE, SOME, FULL
OPTIMIZE=

#	specify any preprocessor symbols to be defined.  
DEFINES=

#	specify special warning levels - NONE, ALL
WARNINGS = ALL

#	specify whether image symbols will be created
SYMBOLS = TRUE

#	specify debug settings
DEBUGGER =

#	specify additional compiler flags for all files
COMPILER_FLAGS =

#	specify additional linker flags
LINKER_FLAGS =

## include the makefile-engine
include /boot/develop/etc/makefile-engine
