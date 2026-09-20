CC = xc8-cc
MCU = 16F877A

BUILD_DIR := build
TARGET := application
OUTPUT_HEX := $(BUILD_DIR)/$(TARGET).hex
OUTPUT_LST := $(BUILD_DIR)/$(TARGET).lst
OUTPUT_MAP := $(BUILD_DIR)/$(TARGET).map

DFP_PATH = C:/Microchip/_DFP/xc8

# Пути к заголовочным файлам
CFLAGS = -mcpu=$(MCU) -mdfp="$(DFP_PATH)" -O0 -std=c99 \
         -Isrc -Idrivers -Ihal -Iinc \
         -L -M

SRCS = main.c \
	   $(wildcard src/*.c) \
       $(wildcard drivers/*.c) \
       $(wildcard hal/*.c)

all: $(OUTPUT_HEX)
	@echo "Build complete. Files in $(BUILD_DIR):"
	@dir $(BUILD_DIR) 2>nul || ls $(BUILD_DIR)

$(OUTPUT_HEX): $(SRCS)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $(SRCS)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
