# General Microcontroller Makefile

# --- EDIT THESE SETTINGS --- {{{

TARGET = firmware
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

PORT :=
TOOLCHAIN_PATH := /opt/homebrew/Cellar/arm-none-eabi-gcc/15.2.0/bin/
TOOLCHAIN_PREFIX := arm-none-eabi-
BOSSAC_PATH := /opt/homebrew/Cellar/bossa/1.9.1/bin/
CORE := ArduinoCore-renesas
VARIANT := UNOWIFIR4

ARDUINO_PATH := /opt/Arduino/
CORE_PATH := $(ARDUINO_PATH)configs/$(CORE)/
VARIANT_PATH := $(CORE_PATH)variants/$(VARIANT)/

# Toolchain C compiler, C++ compiler, archiver, assembler, object file copier,
# and size reader
CC := $(TOOLCHAIN_PATH)$(TOOLCHAIN_PREFIX)gcc
CXX := $(TOOLCHAIN_PATH)$(TOOLCHAIN_PREFIX)g++
AR := $(TOOLCHAIN_PATH)$(TOOLCHAIN_PREFIX)ar
AS := $(TOOLCHAIN_PATH)$(TOOLCHAIN_PREFIX)g++
OBJCOPY := $(TOOLCHAIN_PATH)$(TOOLCHAIN_PREFIX)objcopy
SIZE := $(TOOLCHAIN_PATH)$(TOOLCHAIN_PREFIX)size

# }}}

# --- INCLUDED FLAGS, SOURCEFILES, AND OBJECTFILES --- {{{

# --- FLAGS --- {{{
CFLAGS := \
	$(CORE_PATH)/cflags.txt \
	$(VARIANT_PATH)/cflags.txt

CXXFLAGS := \
	$(CORE_PATH)/cxxflags.txt \
	$(VARIANT_PATH)/cxxflags.txt

LDFLAGS := \
	$(CORE_PATH)/ldflags.txt \
	$(VARIANT_PATH)/ldflags.txt

ARFLAGS := \
	$(CORE_PATH)/arflags.txt \
	$(VARIANT_PATH)/arflags.txt

ASFLAGS := \
	$(CORE_PATH)/asflags.txt \
	$(VARIANT_PATH)/asflags.txt

# }}}

# --- SOURCEFILES --- {{{

CSOURCES := \
	$(shell find $(SRC_DIR) -type f -name '*.c') \
	$(CORE_PATH)/csources.txt \
	$(VARIANT_PATH)/csources.txt 

CXXSOURCES := \
	$(shell find $(SRC_DIR) -type f -name '*.cpp') \
	$(CORE_PATH)/cxxsources.txt \
	$(VARIANT_PATH)/cxxsources.txt

ASSOURCES := \
	$(shell find $(SRC_DIR) -type f name '*.S') \
	$(CORE_PATH)/assources.txt \
	$(VARIANT_PATH)/assources.txt

# }}}

# --- OBJECTFILES --- {{{

COBJECTS := $(patsubst %.c,$(BUILD_DIR)/%.o,$(CSOURCES))

CXXOBJECTS := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(CXXSOURCES))

ASOBJECTS := $(patsubst %.S,$(BUILD_DIR)/%.o,$(ASSOURCES))

OBJECTS := $(COBJECTS) $(CXXOBJECTS) $(ASOBJECTS)

# }}}

# }}}zo

# --- TARGETS --- {{{

# --- COMPILATION --- {{{

$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.S
	$(AS) $(ASFLAGS) -c $< -o $@

# }}}

# --- LINKING --- {{{

$(BIN_DIR/$(TARGET).elf: $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $@

# }}}

# --- ARCHIVAL --- {{{

$(BIN_DIR)/lib$(TARGET).a: $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $(OBJECTS)

# }}}

# --- ELF CONVERSION --- {{{

$(BIN_DIR)/$(TARGET).bin: $(BIN_DIR)/$(TARGET).elf
	$(OBJCOPY) -O binary $< $@

$(BIN_DIR)/$(TARGET).hex: $(BIN_DIR)/$(TARGET).elf
	$(OBJCOPY) -O ihex $< $@

# }}}

# --- UPLOAD, ALL, AND CLEAN --- {{{

upload: $(BIN_DIR)/$(TARGET).bin
	$(BOSSAC) --p=$(PORT) -U true -i -e -w -v $< -R

all: $(BIN_DIR)/$(TARGET).elf

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# }}}

# }}}

