# Normalize PVSNESLIB_HOME to forward slashes for GNU Make compatibility on Windows
export PVSNESLIB_HOME := $(subst \,/,$(PVSNESLIB_HOME))

ifeq ($(strip $(PVSNESLIB_HOME)),)
$(error "Please set the PVSNESLIB_HOME environment variable to your PVSnesLib directory (e.g., C:/pvsneslib)")
endif

# ROM and Game Information (Used in SNES Cartridge Header)
export ROMNAME := mallow_paint
export ROMTITLE := MALLOW PAINT
export AUTOHDR := 0
export CFLAGS := -Iinclude

# Include standard PVSnesLib rules and toolchain targets
include ${PVSNESLIB_HOME}/devkitsnes/snes_rules

.PHONY: all clean

all: $(OBJS) $(ROMNAME).sfc

clean: cleanBuildRes cleanRom cleanGfx cleanLogs
