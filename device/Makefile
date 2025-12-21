# The base path for downloaded arm gcc toolchain
ARM_NONE_EABI=${PWD}/tflite-micro/tensorflow/lite/micro/tools/make/downloads/gcc_embedded/bin/arm-none-eabi

TFLITE_INCLUDE_PATH=${PWD}/tflite-micro
ARM_NONE_EABI_INCLUDE_PATH=${PWD}/tflite-micro/tensorflow/lite/micro/tools/make/downloads/gcc_embedded/arm-none-eabi/include
FLATBUFFERS_INCLUDE_PATH=${PWD}/tflite-micro/tensorflow/lite/micro/tools/make/downloads/flatbuffers/include
GEMMLOWP_INCLUDE_PATH=${PWD}/tflite-micro/tensorflow/lite/micro/tools/make/downloads/gemmlowp

CMSIS_CORE_INCLUDE=cmsis/cmsis_core/CMSIS/Core/Include
CMSIS_WB_INCLUDE=cmsis/cmsis_wb/Include


uart.o: cc/uart.cc Makefile
	${ARM_NONE_EABI}-g++ \
    -mcpu=cortex-m4 \
    -fno-exceptions \
    -fno-unwind-tables \
    -g \
    -I${CMSIS_CORE_INCLUDE} \
    -I${CMSIS_WB_INCLUDE} \
    -I./inc \
    cc/uart.cc -c -o uart.o

main.o: main.cc Makefile
	${ARM_NONE_EABI}-g++ \
    -mcpu=cortex-m4 \
    -fno-exceptions \
    -fno-unwind-tables \
    -g \
    -I${TFLITE_INCLUDE_PATH} \
    -I${FLATBUFFERS_INCLUDE_PATH} \
    -I${GEMMLOWP_INCLUDE_PATH} \
    -I./inc \
    main.cc -c -o main.o

firmware.elf: main.o uart.o link.ld Makefile
	${ARM_NONE_EABI}-g++ \
	-T link.ld \
    -nostdlib \
    -mcpu=cortex-m4 \
    -fno-exceptions \
    -fno-unwind-tables \
    -g \
	main.o uart.o -o firmware.elf

firmware.bin: firmware.elf
	${ARM_NONE_EABI}-objcopy -O binary firmware.elf firmware.bin

firmware.s: main.c
	${ARM_NONE_EABI}-g++ -mcpu=cortex-m4 main.cc -S -o firmware.s

.PHONY: build flash clean assembly

build: firmware.bin

assembly: firmware.s

flash:
	st-flash --reset write firmware.bin 0x8000000

clean:
	rm -f -- *.o *.elf *.bin *.s
