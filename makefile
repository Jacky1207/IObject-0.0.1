#Note:
#1.variable explain

#TOPDIR         variable must be define,this indicates the top directory

#follow variable only defind one or didn't defined(for example,nor source directory)

#TARGETV         variable indicates build a executed file that name is variable value
#LIB            variable indicates build a lib file that name is variable value
#SHAREDLIBV     variable indicates build a shared lib file that name is variable value
#BUILDOBJ       variable indicates build a object file. the value can be anything but didn't empty

#exclude_dirs   variable indicates this directory didn't need build,for example 'include' or 'build'
#project_dirs   variable indicates which directory is project directory
#AutoNeedAppLib	add the library that can auto AR when this lib modify 

export VERSIONSTR := 0
ARCH		= 
CROSS_COMPILE	=

AS				= $(CROSS_COMPILE)as
LD				= $(CROSS_COMPILE)ld
CC				= $(CROSS_COMPILE)gcc
CPP				= $(CC) -E
CXX				= $(CROSS_COMPILE)g++
AR				= $(CROSS_COMPILE)ar
NM				= $(CROSS_COMPILE)nm
STRIP			= $(CROSS_COMPILE)strip
OBJCOPY			= $(CROSS_COMPILE)objcopy
OBJDUMP			= $(CROSS_COMPILE)objdump

export ARCH AS LD CC CPP CXX AR NM STRIP OBJCOPY OBJDUMP
	
exclude_dirs= build include sourceInsight
project_dirs = src

#didn't modify,but remove -g if didn't need debug information
CFLAGS += -Wall -g -std=c++0x
CPPFLAGS += -Wall -g -std=c++0x

# need to be placed at the end of the file
mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
export TOPDIR := $(patsubst %/,%,$(dir $(mkfile_path)))
export MAKEFILELIB=$(TOPDIR)/makefile.env

#include $(TOPDIR)/makefile.env
include $(MAKEFILELIB)
