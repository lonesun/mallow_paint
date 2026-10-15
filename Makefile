# Normalize PVSNESLIB_HOME to forward slashes for GNU Make compatibility on Windows
export PVSNESLIB_HOME := $(subst \,/,$(PVSNESLIB_HOME))

ifeq ($(strip $(PVSNESLIB_HOME)),)
$(error "Please set the PVSNESLIB_HOME environment variable to your PVSnesLib directory (e.g., C:/pvsneslib)")
endif

# Impulse Tracker (.it) modules compiled into the SNESMod soundbank (Bank 5)
AUDIOFILES := res/mallow_title.it res/pollen8.it
export SOUNDBANK := res/soundbank

# ROM and Game Information (Used in SNES Cartridge Header)
export ROMNAME := mallow_paint
export ROMTITLE := MALLOW PAINT
export AUTOHDR := 0
export CFLAGS := -Iinclude

# Include standard PVSnesLib rules and toolchain targets
include ${PVSNESLIB_HOME}/devkitsnes/snes_rules

# Soundbank conversion flags (-s: soundbank mode, -b 5: place in ROM Bank 5)
SMCONVFLAGS := -s -o $(SOUNDBANK) -V -b 5

.PHONY: all musics clean

musics: $(SOUNDBANK).obj

# Ensure res/soundbank.h is generated before C sources are compiled
$(CFILES:.c=.ps): $(SOUNDBANK).asm

all: musics $(OBJS) $(ROMNAME).sfc

clean: cleanBuildRes cleanRom cleanGfx cleanAudio cleanLogs

