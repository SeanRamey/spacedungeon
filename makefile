# default to using clang as the c/c++ compiler
USE_CLANG ?= true

#default to debug build
BUILDTYPE ?= DEBUG

# master output directory
BUILD := build

ifeq ($(BUILDTYPE),DEBUG)
# standard compile and link flags and link libraries (DEBUG)
CFLAGS =
CXXFLAGS = -Wpedantic -Wall -Wextra -Wno-deprecated -Wno-deprecated-declarations -ggdb -std=c++11 -march=native -fno-omit-frame-pointer
CPPFLAGS = -DDEBUG -DSFML
LDFLAGS = -march=native -fno-omit-frame-pointer
LDLIBS = -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-network
TESTPROGFLAGS = -ne

# output subdirectory
SUBBUILD := debug

else ifeq ($(BUILDTYPE),RELEASE)
# standard compile and link flags and link libraries (RELEASE)
CFLAGS =
CXXFLAGS = -Wpedantic -Wall -Wextra -Wno-deprecated -Wno-deprecated-declarations -std=c++11 -O3 -march=native -flto
CPPFLAGS = -DRELEASE -DSFML
LDFLAGS = -s -O3 -march=native -flto
LDLIBS = -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-network
TESTPROGFLAGS = -ne

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

# color config

# Black        0;30     Dark Gray     1;30
# Red          0;31     Light Red     1;31
# Green        0;32     Light Green   1;32
# Brown/Orange 0;33     Yellow        1;33
# Blue         0;34     Light Blue    1;34
# Purple       0;35     Light Purple  1;35
# Cyan         0;36     Light Cyan    1;36
# Light Gray   0;37     White         1;37
NC = '\033[0m' # no color
BLACK = '\033[0;30m'
RED = '\033[0;31m'
GREEN = '\033[0;32m'
BROWN = '\033[0;33m'
BLUE = '\033[0;34m'
PURPLE = '\033[0;35m'
CYAN = '\033[0;36m'
LGRAY = '\033[0;37m'
DGRAY = '\033[1;30m'
LRED = '\033[1;31m'
LGREEN = '\033[1;32m'
YELLOW = '\033[1;33m'
LBLUE = '\033[1;34m'
LPURPLE = '\033[1;35m'
LCYAN = '\033[1;36m'
WHITE = '\033[1;37m'

COMPILE_COLOR = $(CYAN)
LINK_COLOR = $(CYAN)
DONE_COLOR = $(GREEN)
PRECOMPILE_COLOR = $(LRED)
GENDEPENDS_COLOR = $(LPURPLE)
COMPILER_PROG_COLOR = $(LGREEN)
LINK_PROG_COLOR = $(LGREEN)

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
	ECHO := echo -e
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
	ECHO := echo -e
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
	ECHO := echo
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
	@$(ECHO) running tests...
	$(BUILD)$(SLASH)$(SUBBUILD)$(SLASH)$(testprogram) $(TESTPROGFLAGS)
	@$(ECHO) $(DONE_COLOR)build complete!$(NC)

$(program): $(BUILD)/$(SUBBUILD)/$(program)
	@$(ECHO) $(DONE_COLOR)done building $(program)!$(NC)

$(testprogram): $(BUILD)/$(SUBBUILD)/$(testprogram)
	@$(ECHO) $(DONE_COLOR)done building $(testprogram)!$(NC)
	@$(ECHO) running tests...
	@$(BUILD)$(SLASH)$(SUBBUILD)$(SLASH)$(testprogram) $(TESTPROGFLAGS)

# build single file
single: $(BUILD)/$(SUBBUILD)/$(in).o

$(BUILD)/$(SUBBUILD)/$(program): $(objects)
	@$(ECHO) linking $(LINK_COLOR)"$^"$(NC) into "$@" using these libraries: "$(LDLIBS)"
	@$(LD) -o $@ $^ $(LDFLAGS) $(LDLIBS)
	@$(ECHO) $(LINK_COLOR)linking "$@" done!$(NC)
	@$(ECHO) ""

$(BUILD)/$(SUBBUILD)/$(testprogram): $(unit-test-objects) $(filter-out $(BUILD)/$(SUBBUILD)/$(program-main:.cpp=.o),$(objects))
	@$(ECHO) linking $(LINK_COLOR)"$^"$(NC) into "$@" using these libraries: "$(LDLIBS)"
	@$(LD) -o $@ $^ $(LDFLAGS) $(LDLIBS)
	@$(ECHO) $(LINK_COLOR)linking "$@" done!$(NC)
	@$(ECHO) ""

$(objects): $(gchfiles)

$(unit-test-objects): $(gchfiles)

$(BUILD)/$(SUBBUILD)/%.o: %.cpp
	@$(ECHO) compiling $(COMPILE_COLOR)"$<"$(NC) to "$@" with $(COMPILER_PROG_COLOR)$(CXX)$(NC)
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

%.hpp.gch: %.hpp
	@$(ECHO) precompiling header $(PRECOMPILE_COLOR)"$<"$(NC) to "$@" with $(COMPILER_PROG_COLOR)$(CXX)$(NC)
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) $<

$(objects) $(depends): | $(BUILD) $(BUILD)/$(SUBBUILD)

$(BUILD) $(BUILD)/$(SUBBUILD):
	@$(ECHO) $(DGRAY)creating directories$(NC)
	@$(MKDIR) $(BUILD) $(addprefix $(BUILD)$(SLASH)$(SUBBUILD)$(SLASH),$(cppdirs)) $(addprefix $(BUILD)$(SLASH)$(SUBBUILD)$(SLASH),$(unit-test-cppdirs))

# rule to generate a dependency file
$(BUILD)/$(SUBBUILD)/%.d: %.cpp
	@$(ECHO) generating dependencies for $(GENDEPENDS_COLOR)"$<"$(NC)
	@$(CXX) $(CXXFLAGS) $< -MM -MT $(@:.d=.o) >$@

# include all dependency files in the makefile
-include $(depends)

.PHONY: clean cleandep install uninstall
clean:
#	$(RM) $(subst /,$(SLASH),$(objects)) $(subst /,$(SLASH),$(depends)) $(subst /,$(SLASH),$(BUILD)/$(program))
	@$(ECHO) cleaning...
	@$(RMDIR) $(BUILD)
	@$(RM) $(SRC)$(SLASH)*.gch
	@$(ECHO) $(DONE_COLOR)done.$(NC)

cleandep:
	@$(ECHO) cleaning dependencies...
	@$(RM) $(subst /,$(SLASH),$(depends))
	@$(ECHO) $(DONE_COLOR)done.$(NC)

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
	#@$(ECHO) Commands:
	#@$(ECHO) make all ---------------------------------- builds the program and puts all the output files in a directory called build
	#@$(ECHO) make single in=<path-to-file/file> -------- builds only a single file (omit the .cpp or .c extension and ignore the quotes as well)
	#@$(ECHO) make install ------------------------------ builds the program just like make all and installs the final files to a directory
	#@$(ECHO) make uninstall ---------------------------- will remove all the files from the install directory
	#@$(ECHO) make clean -------------------------------- will remove the build directory
