# build configuration

# build options here
# 1 = yes
# 0 = no
USESDL ?= 0
USESFML ?= 1

# build type
# RELEASE or DEBUG
BUILD ?= DEBUG

# os target, UNKNOWN to autodetect
# valid options are:
# WINDOWS
# MACOSX
# LINUX
OSTARGET ?= UNKNOWN

# name of output program
PROG?=gamealpha

# build output directory
BUILDPATH ?= build
