
OSTARGET ?= UNKNOWN

# autodetect os
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
	CFLAGS :=
	CXXFLAGS := -Wpedantic -Wall -Wextra -Wno-deprecated -Wno-deprecated-declarations -ggdb -std=c++11 -I/usr/include
	CPPFLAGS := -DSFML
	LDFLAGS := -L/usr/lib
	LDLIBS := -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-network
	RM := rm -f
	RMDIR := rm -rf

	# source directory
	SRC := src

	# output directory
	BUILD := build

	# compiler/linker programs
	CC := gcc
	CPP := g++
	LD := g++

	# name of output program
	program := gamealpha
endif
ifeq ($(OSTARGET),MACOSX)
	CFLAGS :=
	CXXFLAGS := -Wpedantic -Wall -Wextra -Wno-deprecated -Wno-deprecated-declarations -ggdb -std=c++11 -I/usr/include
	CPPFLAGS := -DSFML
	LDFLAGS := -L/usr/lib
	LDLIBS := -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-network
	RM := rm -f
	RMDIR := rm -rf

	# source directory
	SRC := src

	# output directory
	BUILD := build

	# compiler/linker programs
	CC := gcc
	CPP := g++
	LD := g++

	# name of output program
	program := gamealpha
endif
ifeq ($(OSTARGET),WINDOWS)
	CFLAGS :=
	CXXFLAGS := -Wpedantic -Wall -Wextra -Wno-deprecated -Wno-deprecated-declarations -ggdb -std=c++11 -Iinclude
	CPPFLAGS := -DSFML
	LDFLAGS := -Llib
	LDLIBS := -lmingw32 -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-network
	RM := del /F/Q
	RMDIR := rmdir /S/Q

	# source directory
	SRC := src

	# output directory
	BUILD := build

	# compiler/linker programs
	CC := gcc
	CPP := g++
	LD := g++

	# name of output program
	program := gamealpha.exe
endif

cppsrc = $(wildcard $(SRC)/*.cpp)
objects = $(patsubst $(SRC)/%.o,$(BUILD)/%.o,$(cppsrc:.cpp=.o))
#objects = $(cppsrc:.cpp=.o)
depends = $(objects:.o=.d)
#depends = $(patsubst  $(BUILD)/%.d,$(BUILD)/%.d,$(objects:.o=.d))

all: $(BUILD)/$(program)

$(BUILD):
	mkdir $(BUILD)

$(BUILD)/$(program): $(objects)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDLIBS)

$(objects): $(BUILD)/%.o: $(SRC)/%.cpp | $(BUILD)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

# rule to generate a dep file by using the C preprocessor
$(BUILD)/%.d:  $(SRC)/%.cpp | $(BUILD)
	@$(CPP) $(CXXFLAGS) $< -MM -MT $(@:.d=.o) >$@

-include $(depends)   # include all dep files in the makefile

.PHONY: clean cleandep
clean:
	$(RM) $(subst /,\,$(objects)) RM $(subst /,\,$(depends)) $(subst /,\,$(program))
	$(RMDIR) $(BUILD)

cleandep:
	$(RM) $(subst /,\,$(depends))