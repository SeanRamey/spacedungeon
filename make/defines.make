# define variables


# autodetect os
ifeq ($(OSTARGET),UNKNOWN)
	ifeq ($(OS),Windows_NT)
		OSTARGET = WINDOWS
	else
		UNAME = $(shell uname -s)
		ifeq ($(UNAME),Linux)
			OSTARGET = LINUX
		endif
		ifeq ($(UNAME),Darwin)
			OSTARGET = MACOSX
		endif
	endif
endif


# program name and extension
PROG?=example

ifeq ($(OSTARGET),LINUX)
	EXT=
endif
ifeq ($(OSTARGET),MACOSX)
	EXT=
endif
ifeq ($(OSTARGET),WINDOWS)
	EXT=.exe
endif

# setup defines for compiler and
# libraries for linking
ifeq ($(OSTARGET),LINUX)
	INCPATHS := /usr/include
	LIBPATHS := /usr/lib
endif
ifeq ($(OSTARGET),MACOSX)
	INCPATHS := /usr/include
	LIBPATHS := /usr/lib
endif
ifeq ($(OSTARGET),WINDOWS)
	INCPATHS := include
	LIBPATHS := lib
endif

# for build compatibility on windows
ifeq ($(OSTARGET),WINDOWS)
	LIBS += -lmingw32
endif
ifeq ($(USESDL),1)
	DEFINES += -DSDL
	LIBS += -lSDL2main -lSDL2
	LIBPATHS +=
endif
ifeq ($(USESFML),1)
	DEFINES += -DSFML
	LIBS += -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-network
	LIBPATHS +=
endif

DEFINES += -D$(BUILD)
DEFINES += -D$(OSTARGET)

INCPATHS := $(addprefix -I,$(INCPATHS))
LIBPATHS := $(addprefix -L,$(LIBPATHS))

# compiler/linker programs
CC = gcc
CPP = g++
LD = g++

# compiler/linker flags for debug
CFLAGS_DEBUG =-Wpedantic -Wall -Wextra -Wno-deprecated -Wno-deprecated-declarations -ggdb -std=c11
CPPFLAGS_DEBUG =-Wpedantic -Wall -Wextra -Wno-deprecated -Wno-deprecated-declarations -ggdb -std=c++11
LDFLAGS_DEBUG =-static-libgcc

# compiler/linker flags for release
CFLAGS_RELEASE =-Wpedantic -Wall -Wextra -Wno-deprecated -Wno-deprecated-declarations -std=c11 -O3 -flto
CPPFLAGS_RELEASE =-Wpedantic -Wall -Wextra -Wno-deprecated -Wno-deprecated-declarations -std=c++11 -O3 -flto
LDFLAGS_RELEASE =-static-libgcc -s -mwindows -O3 -flto

# final compiler/linker flags
CBUILD = $(CC) $(CFLAGS_$(BUILD)) -c $< -o $(subst $(SOURCEPATH)/,$(BUILDPATH)/,$@) -MMD $(DEFINES) -I$(SOURCEPATH) $(INCPATHS)
CPPBUILD = $(CPP) $(CPPFLAGS_$(BUILD)) -c $< -o $(subst $(SOURCEPATH)/,$(BUILDPATH)/,$@) -MMD $(DEFINES) -I$(SOURCEPATH) $(INCPATHS)
LDBUILD = $(LD) $(LDFLAGS_$(BUILD)) -o $(addprefix $(BUILDPATH)/,$@) $(subst $(SOURCEPATH)/,$(BUILDPATH)/,$^) $(LDFLAGS) $(LIBPATHS) $(LIBS)

# resource compiler (win32 only)
ifeq ($(OSTARGET),WINDOWS)
	RC = windres
	RCFLAGS = --input-format=rc --output-format=coff
endif

# install variables
# path to install the executable
ifeq ($(OSTARGET),LINUX)
	INSTALLPATH=/usr/bin
endif
ifeq ($(OSTARGET),OSX)
	INSTALLPATH=/usr/bin
endif
ifeq ($(OSTARGET),WIN32)
	INSTALLPATH="/Program Files/$(PROG)"
endif

# path to install data
ifeq ($(OSTARGET),LINUX)
	DATAPATH=/usr/share/$(PROG)
endif
ifeq ($(OSTARGET),OSX)
	DATAPATH=/usr/share/$(PROG)
endif
ifeq ($(OSTARGET),WIN32)
	DATAPATH="/Program Files/$(PROG)"
endif

GRAPHICSPATH=resources$(DIRSEP)graphics
SOUNDSPATH=resources$(DIRSEP)sounds

#GRAPHICSFILES=$(GRAPHICSPATH)/image1.png $(GRAPHICSPATH)/image2.png
#SOUNDSFILES=$(SOUNDSPATH)/sound1.wav $(SOUNDSPATH)/sound2.wav

ALLDATAPATHS=$(DATAPATH)$(DIRSEP)$(GRAPHICSPATH) $(DATAPATH)$(DIRSEP)$(SOUNDSPATH)


# build target
TARGET = $(PROG)$(EXT)

# command line commands
# DIRSEP is the OS specific directory path seperator
ifeq ($(OSTARGET),LINUX)
	MKDIR := mkdir -p
	REMOVE := rm -rf
	COPY := cp
	DIRSEP := /
endif
ifeq ($(OSTARGET),MACOSX)
	MKDIR := mkdir -p
	REMOVE := rm -rf
	COPY := cp
	DIRSEP := /
endif
ifeq ($(OSTARGET),WINDOWS)
	MKDIR :=  mkdir
	REMOVE := rmdir /Q/S
	COPY := xcopy
	DIRSEP :=\\
endif