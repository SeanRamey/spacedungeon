# default to using clang as the c/c++ compiler
#USE_CLANG ?= true

#default to debug build
BUILDTYPE ?= DEBUG

# master output directory
BUILD := build

ifeq ($(BUILDTYPE),DEBUG)
# standard compile and link flags and link libraries (DEBUG)
CFLAGS =
CXXFLAGS = -Wpedantic -Wall -Wextra -Wno-deprecated -Wno-deprecated-declarations -ggdb -std=c++11 -fno-omit-frame-pointer
CPPFLAGS = -DSFML
LDFLAGS = -fno-omit-frame-pointer
LDLIBS = -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-network

# output subdirectory
SUBBUILD := debug

else ifeq ($(BUILDTYPE),RELEASE)
# standard compile and link flags and link libraries (RELEASE)
CFLAGS =
CXXFLAGS = -Wpedantic -Wall -Wextra -Wno-deprecated -Wno-deprecated-declarations -std=c++11 -O3 -flto
CPPFLAGS = -DSFML
LDFLAGS = -s -O3 -flto
LDLIBS = -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-network

# output subdirectory
SUBBUILD := release
endif

# source directory
SRC := src

# where to find additional c++ source and header files
# make sure to use the $(SLASH) variable for the directory seperator if
# a subdirectory is included
# example: dir$(SLASH)nextdir
cppdirs = entities util entities$(SLASH)weapons UI manager gamestate
unit-test-cppdirs = unit-tests

# a list of headers to pre-compile
pchfiles = sfmlpch.hpp stdpch.hpp allpch.hpp doctestpch.hpp

# main files
program-main = main.cpp
unit-test-main = tests-main.cpp

# name of output program
program = spacedungeon
# name of unit tests program
testprogram = tests


# autodetect os
OSTARGET ?= UNKNOWN

ifeq ($(OSTARGET),UNKNOWN)
	ifeq ($(OS),Windows_NT)
		OSTARGET := WINDOWS
	else
		UNAME := $(shell uname -s)
		ifeq ($(UNAME),Linux)
			OSTARGET := LINUX
		endif
		ifeq ($(UNAME),Darwin)
			OSTARGET := MACOSX
		endif
	endif
endif

ifeq ($(OSTARGET),LINUX)
	# OS specific options
	CFLAGS +=
	CXXFLAGS += -I/usr/include $(addprefix -I,$(INCDIRS))
	CPPFLAGS +=
	LDFLAGS += -L/usr/lib
	LDLIBS +=
	RM := rm -f
	RMDIR := rm -rf
	MKDIR := mkdir -p
	SLASH = /
	CP := cp
	PREFIX ?= /usr/local

	# compiler/linker programs
    ifeq ($(USE_CLANG), true)
	    CC := clang
	    CXX := clang++
	    CPP := clang++
	    LD := clang++

        ifeq ($(USE_LIBC++), true)
	        CXXFLAGS += -stdlib=libc++
	        LDFLAGS += -L/home/sean/Coding/spacedungeon/lib
	        LDFLAGS += -stdlib=libc++
        endif
    else
	    CC := gcc
	    CXX := g++
	    CPP := cpp
	    LD := g++
    endif

	# extension of output program
	#program +=
endif
ifeq ($(OSTARGET),MACOSX)
	# OS specific options
	CFLAGS +=
	CXXFLAGS += -I/usr/include $(addprefix -I,$(INCDIRS))
	CPPFLAGS +=
	LDFLAGS += -L/usr/lib
	LDLIBS +=
	RM := rm -f
	RMDIR := rm -rf
	MKDIR := mkdir -p
	CP := cp
	SLASH = /
	PREFIX ?= /usr/local

	# compiler/linker programs
	CC := gcc
	CXX := g++
	CPP := cpp
	LD := g++

	# extension of output program
	#program +=
endif
ifeq ($(OSTARGET),WINDOWS)
	# OS specific options
	CFLAGS +=
	CXXFLAGS += -Iinclude $(addprefix -I,$(INCDIRS))
	CPPFLAGS +=
	LDFLAGS += -Llib
	LDLIBS += -lmingw32
	RM := del /F/Q
	RMDIR := rmdir /S/Q
	MKDIR := mkdir
	CP := robocopy
	SLASH = \\
	PREFIX ?=

	# compiler/linker programs
	CC := gcc
	CXX := g++
	CPP := cpp
	LD := g++

	# extension of output program
	program := $(addsuffix .exe,$(program))
	testprog := $(addsuffix .exe,$(testprog))
endif

INCDIRS = $(SRC) $(addprefix $(SRC)/,$(cppdirs)) $(addprefix $(SRC)/,$(unit-test-cppdirs))
VPATH = $(INCDIRS)
cppsrc = $(wildcard $(SRC)/*.cpp $(addsuffix /*.cpp,$(addprefix $(SRC)/,$(cppdirs))))
unit-test-cppsrc = $(wildcard $(addsuffix /*.cpp,$(addprefix $(SRC)/,$(unit-test-cppdirs))))
objects = $(patsubst $(SRC)/%.o,$(BUILD)/$(SUBBUILD)/%.o,$(cppsrc:.cpp=.o))
unit-test-objects = $(patsubst $(SRC)/%.o,$(BUILD)/$(SUBBUILD)/%.o,$(unit-test-cppsrc:.cpp=.o))
depends = $(objects:.o=.d) $(unit-test-objects:.o=.d)
gchfiles = $(addsuffix .gch, $(pchfiles))
DESTDIR =

all: $(BUILD)/$(SUBBUILD)/$(program) $(BUILD)/$(SUBBUILD)/$(testprogram)
	@echo running tests...
	$(BUILD)$(SLASH)$(SUBBUILD)$(SLASH)$(testprogram)
	@echo build complete!

$(program): $(BUILD)/$(SUBBUILD)/$(program)
	@echo done building $(program)!

$(testprogram): $(BUILD)/$(SUBBUILD)/$(testprogram)
	@echo done building $(testprogram)!
	@echo running tests...
	@$(BUILD)$(SLASH)$(SUBBUILD)$(SLASH)$(testprogram)

# build single file
single: $(BUILD)/$(SUBBUILD)/$(in).o

$(BUILD)/$(SUBBUILD)/$(program): $(objects)
	@echo linking "$^" into "$@" using these libraries: "$(LDLIBS)"
	@$(LD) -o $@ $^ $(LDFLAGS) $(LDLIBS)

$(BUILD)/$(SUBBUILD)/$(testprogram): $(unit-test-objects) $(filter-out $(BUILD)/$(SUBBUILD)/$(program-main:.cpp=.o),$(objects))
	@echo linking "$^" into "$@" using these libraries: "$(LDLIBS)"
	@$(LD) -o $@ $^ $(LDFLAGS) $(LDLIBS)

$(objects): $(gchfiles)

$(unit-test-objects): $(gchfiles)

$(BUILD)/$(SUBBUILD)/%.o: %.cpp
	@echo compiling "$<" to "$@" with $(CXX)
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

%.hpp.gch: %.hpp
	@echo precompiling header "$<" to "$@" with $(CXX)
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) $<

$(objects) $(depends): | $(BUILD) $(BUILD)/$(SUBBUILD)

$(BUILD) $(BUILD)/$(SUBBUILD):
	@echo creating directories
	@$(MKDIR) $(BUILD) $(addprefix $(BUILD)$(SLASH)$(SUBBUILD)$(SLASH),$(cppdirs)) $(addprefix $(BUILD)$(SLASH)$(SUBBUILD)$(SLASH),$(unit-test-cppdirs))

# rule to generate a dependency file
$(BUILD)/$(SUBBUILD)/%.d: %.cpp
	@echo generating dependencies for "$<"
	@$(CXX) $(CXXFLAGS) $< -MM -MT $(@:.d=.o) >$@

# include all dependency files in the makefile
-include $(depends)

.PHONY: clean cleandep install uninstall
clean:
#	$(RM) $(subst /,$(SLASH),$(objects)) $(subst /,$(SLASH),$(depends)) $(subst /,$(SLASH),$(BUILD)/$(program))
	@echo cleaning...
	@$(RMDIR) $(BUILD)
	@$(RM) $(SRC)$(SLASH)*.gch
	@echo done.

cleandep:
	@echo cleaning dependencies...
	@$(RM) $(subst /,$(SLASH),$(depends))
	@echo done.

install: $(BUILD)/$(SUBBUILD)/$(program)
ifeq ($(OSTARGET),WINDOWS)
	-$(CP) /S $(BUILD) $(DESTDIR)$(PREFIX)bin $(program)
	-$(CP) /S data $(DESTDIR)$(PREFIX)bin$(SLASH)data
	-$(CP) ./ $(DESTDIR)$(PREFIX)bin *.dll
else
	$(MKDIR) $(DESTDIR)$(PREFIX)/bin/$(program)
	$(CP) $< $(DESTDIR)$(PREFIX)/bin/$(program)
	$(CP) -r ./data $(DESTDIR)$(PREFIX)/bin/$(program)
endif

uninstall:
ifeq ($(OSTARGET), WINDOWS) 
	$(RMDIR) $(DESTDIR)$(PREFIX)bin
else 
	$(RMDIR) $(DESTDIR)$(PREFIX)$(SLASH)bin$(SLASH)$(program)
endif

help:
	#@echo Commands:
	#@echo make all ---------------------------------- builds the program and puts all the output files in a directory called build
	#@echo make single in=<path-to-file/file> -------- builds only a single file (omit the .cpp or .c extension and ignore the quotes as well)
	#@echo make install ------------------------------ builds the program just like make all and installs the final files to a directory
	#@echo make uninstall ---------------------------- will remove all the files from the install directory
	#@echo make clean -------------------------------- will remove the build directory
