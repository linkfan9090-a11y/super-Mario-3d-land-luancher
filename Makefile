
ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment.")
endif

TOPDIR ?= $(CURDIR)
include $(DEVKITARM)/3ds_rules

TARGET := MarioLandLauncher
BUILD := build
SOURCES := source
DATA :=
INCLUDES :=
GRAPHICS :=
GFXBUILD := $(BUILD)

APP_TITLE := Mario Land Mod Launcher
APP_DESCRIPTION := Fan-made profile selector prototype
APP_AUTHOR := Fan Project

ARCH := -march=armv6k -mtune=mpcore -mfloat-abi=hard -mtp=soft
CFLAGS := -g -Wall -Wextra -O2 -mword-relocations -ffunction-sections $(ARCH)
CFLAGS += $(INCLUDE) -D__3DS__
LDFLAGS := -specs=3dsx.specs -g $(ARCH) -Wl,-Map,$(notdir $*.map)
LIBS := -lctru -lm
LIBDIRS := $(CTRULIB)
