# sources.make - source files

# path of source files
SOURCEPATH=src

# build list of source files
# categorize source files

SOURCE_MAIN=prototype-main.cpp game.cpp player-ship.cpp entity.cpp collision-box.cpp input.cpp random-numbers.cpp alien-ship.cpp level.cpp tile.cpp bullet.cpp gun.cpp basic-bullet.cpp resources.cpp log.cpp


# add categories to SOURCES as needed
SOURCES+=$(SOURCE_MAIN)

# add the SOURCEPATH to each source file
SOURCES:=$(addprefix $(SOURCEPATH)/,$(SOURCES))

# extra files to remove
TRASHFILES = stdout.txt stderr.txt

# extra directories to remove
TRASHDIRS = junkdir

# generate object files
OBJECTS = $(patsubst %.cpp,%.o,$(SOURCES))

# generate dependency files
DEPENDS = $(patsubst %.cpp,%.d,$(SOURCES))
