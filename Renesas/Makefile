# Arduino Core

PORT=/dev/ttyACM0

TUSB_PATH = /home/parkervannah/Documents/Microcontroller_EZcompile/.libs/Adafruit_TinyUSB_Arduino
RENESAS_CORE_PATH = /home/parkervannah/Documents/Microcontroller_EZcompile/.cores/ArduinoCore-renesas
RENESAS_CORE_ARDUINO_PATH = $(RENESAS_CORE_PATH)/cores/arduino
RENESAS_LIB_PATH = $(RENESAS_CORE_PATH)/libraries
VARIANT_PATH = $(RENESAS_CORE_PATH)/variants/UNOWIFIR4

# Toolchain
CROSS_PATH = /usr/bin/
CROSS_PREFIX = $(CROSS_PATH)arm-none-eabi-
CXX = $(CROSS_PREFIX)g++
OBJCOPY = $(CROSS_PREFIX)objcopy
SIZE = $(CROSS_PREFIX)size
BOSSAC_PATH = /bin/
BOSSAC = $(BOSSAC_PATH)bossac

MCU = cortex-m4
FPU = fpv4-sp-d16
FLOAT_ABI = hard

EX_CXXFLAGS := $(shell tr '\n' ' ' <  $(VARIANT_PATH)/cxxflags.txt) -DF_CPU=48000000

EX_INCLUDES := $(patsubst -iwithprefixbefore/%,-I$(RENESAS_CORE_PATH)/%,$(file < $(VARIANT_PATH)/includes.txt))

EX_LDFLAGS = \
	--specs=nano.specs \
	-lstdc++ \
	-lsupc++ \
	-lm \
	-lc \
	-lgcc \
	-lnosys \
	-L$(VARIANT_PATH) \
	-L$(VARIANT_PATH)/libs \
	-lfsp \
	-T$(VARIANT_PATH)/fsp.ld

# --- FLAGS --- {{{

WFLAGS = -w -Wall -Wextra
OFLAGS = -Os

BASE_CXXFLAGS = \
	$(WFLAGS) \
	$(OFLAGS) \
	-g3 \
	-fno-use-cxa-atexit \
	-fno-rtti \
	-fno-exceptions \
	-MMD \
	-std=gnu++17 \
	-mcpu=$(MCU) \
	-mfloat-abi=$(FLOAT_ABI) \
	-mfpu=$(FPU) \
	-fsigned-char \
	-ffunction-sections \
	-fdata-sections \
	-fmessage-length=0 \
	-fno-builtin \
	-mthumb

BASE_LDFLAGS = \
    -Wl,--gc-sections \
    --specs=nosys.specs \
    -mcpu=$(MCU) \
    -mfloat-abi=$(FLOAT_ABI) \
    -mfpu=$(FPU)
# }}}

CXXFLAGS = $(BASE_CXXFLAGS) $(EX_CXXFLAGS)
LDFLAGS = $(BASE_LDFLAGS) $(EX_LDFLAGS)
INCLUDES = $(EX_INCLUDES) -I$(RENESAS_LIB_PATH)/Arduino_LED_Matrix/src -I$(RENESAS_CORE_ARDUINO_PATH)/api -I$(RENESAS_CORE_ARDUINO_PATH) -I$(VARIANT_PATH) -I$(TUSB_PATH)/src

TARGET = firmware

SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

APP_SRCS := $(wildcard $(SRC_DIR)/*.cpp)

CORE_CPP := $(shell find $(RENESAS_CORE_ARDUINO_PATH) -name "*.cpp")

VARIANT_CPP := $(shell find $(VARIANT_PATH) -name "*.cpp")

FSP_C := $(shell find $(VARIANT_PATH)/../ra_gen -name "*.c")

FSP_EXTRA_C := $(shell find $(VARIANT_PATH)/../includes/ra/fsp -name "*.c")

SRCS := $(APP_SRCS) $(CORE_CPP) $(VARIANT_CPP) $(FSP_C) $(FSP_EXTRA_C)
OBJS := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(filter %.cpp,$(SRCS))) \
	$(patsubst %.c,$(BUILD_DIR)/%.o,$(filter %.c,$(SRCS)))

# compile c
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# compile c++
$(BUILD_DIR)/%.o: %.cpp
	@echo "Creating build directory..."
	@mkdir -p $(dir $@)
	@echo "Build directory created."
	@echo "Compiling source files..."
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MMD -c $< -o $@
	echo "Build compiled."

# link
$(BIN_DIR)/$(TARGET).elf: $(OBJS)
	@echo "Creating bin directory..."
	@mkdir -p $(dir $@)
	@echo "Bin directory created."
	@echo "Linking build..."
	$(CXX) $(OBJS) $(LDFLAGS) -o $@
	@echo "ELF file created."
	$(SIZE) $@

# create binary
$(BIN_DIR)/%.bin: $(BIN_DIR)/$(TARGET).elf
	@echo "Copying ELF file to binary..."
	$(OBJCOPY) -O binary $< $@
	@echo "Binary target successfully created."

all: $(BIN_DIR)/$(TARGET).bin

# upload
upload: $(BIN_DIR)/$(TARGET).bin
	@echo "Flashing firmware..."
	sudo $(BOSSAC) --port=$(PORT) -a >/dev/null 2>&1 || true
	sudo $(BOSSAC) --port=$(PORT) -d -U -e -w $< -R 2>&1 || true
	@echo "Firmware flashed."
# clean
clean:
	@echo "Recursively and forcibly removing the build and bin directories..."
	rm -rf $(BUILD_DIR) $(BIN_DIR)
	@echo "Removal complete."

.PHONY: all clean upload

debug:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c src/main.cpp -o build/main.o
	$(CXX) $(OBJS) $(LDFLAGS) -o $(BIN_DIR)/$(TARGET)
