Руководство по настройке VSCode для программирования PIC1F на Си.

1. Что должно быть установлено:
- ОС Windows + MS VS Code;
- компилятор XC8 (У меня установлен в папке: C:\Microchip\xc8\v4.00);
- Microchip PIC16Fxxx Series Device Family Pack (DFP)(У меня в папке: C:\Microchip\_DFP);

2. Установлены расширения (эти точно...)
- C/C++ Extension for VSCode;
- Makefiles Tools;

3. Настраиваем проект.
- в папке .vscode 
        c_cpp_properties.json
---
        {
    "configurations": [
        {
            "name": "PIC16F877A XC8_v4_00",
            "intelliSenseMode": "windows-gcc-x64",
            "includePath": [
                "C:/Microchip/xc8/v4.00/pic/include",
                "C:/Microchip/xc8/v4.00/pic/include/C99",
                "C:/Microchip/_DFP/xc8/pic/include",
                "C:/Microchip/_DFP/xc8/pic/include/proc",
                "${workspaceFolder}/",
                "${workspaceFolder}/**"
            ],
            "defines": [
                "_XTAL_FREQ=12000000UL",
                "__XC",
                "__XC8",
                "__XC8_VERSION=4000",
                "_16F877A",
                "__PICC__",
                "__unsupported__(x)=",
                "__bit="
            ],
            "compilerPath": "",
            "cStandard": "c99",
            "cppStandard": "c++14"
        }
    ],
    "version": 4
}

      Makefile (он в корневой папке)
---
    
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


Все сохранить и ререзапустить VSCode

запускаем в командной строке сборку: make clean && make
в каталоге /build должен появиться .hex

СТРУКТУРА Workspace
---
16F877A-master/
├── Makefile
├── main.c                # точка входа, минимальный «оркестратор»
├── main.h
├── build/                # артефакты сборки (hex, lst, map)
│
├── src/                  # прикладная логика проекта
│   ├── blink.c
│   ├── blink.h
│   ├── uart.c
│   └── uart.h
│
├── drivers/              # драйверы периферии (PIC-специфичные)
│   ├── timer0.c
│   ├── timer0.h
│   ├── port_io.c
│   └── port_io.h
│
├── hal/                  # аппаратно-независимые абстракции (если нужны)
│   ├── delay.c
│   └── delay.h
│
└── inc/                   # общие заголовки (опционально, можно класть в drivers/ или src/)
    ├── config.h          # фьюзы, частоты, пины
    └── types.h           # typedefs, общие типы

•	src/ — только логика приложения (Blink, UART-протокол, меню, автомат состояний). Если проект вырастет — можно разбить на подпапки по фичам (src/menu, src/protocol).
•	drivers/ — низкоуровневые драйверы под конкретный чип. Это аналог твоих HAL-файлов для STM32, но без тяжёлой иерархии.
•	hal/ — если хочешь переносимость: delay_ms() поверх таймера, абстракция «светодиод вкл/выкл». На PIC это часто избыточно, но удобно, если планируешь мигрировать код между чипами.
•	inc/ — общие конфиги и типы. Фьюзы и пины лучше вынести в отдельный config.h, чтобы не править каждый драйвер при смене платы.


PS Огромная благодарность Mostafa Hendy за исходный проект.