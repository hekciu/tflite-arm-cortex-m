## Tensorflow Lite Micro on arm-cortex-m4 without RTOS or any other libraries
This project is a basic example of using tflite-micro in "bare-metal" environment - without RTOS or wrappers.
Code also includes handling of USART peripheral which is specific for this particular Stm32 MCU.

#### Hardware used
- STM32WB55RG Microcontroller on P-NUCLEO-WB55 board
- Laptop running x86-64 Debian 12 Linux    

#### Pre-installed software
- Globally available python3 with numpy and pil/pillow packages
- st-flash
- xxd

#### Training model (model/)
- ./init.sh # Create venv and install requirements
- ./train.sh # Train, quantize and save model


#### Compiling and flashing MCU project (device/)
- ./init.sh # Download CMSIS and tflite-micro, compile the latter
- ./compile_model.sh # Transform .tflite model into C array inside sine_model.h
- make clean # Clean binaries from previous runs
- make build # Build project
- make flash # Flash project to device via st-flash


#### Verification
Program should periodically evaluate NN model with few hardcoded values and send output via UART (baud rate 115200).
On the board that I used this particular USART's output is redirected into USB port via ST-Link.
Example way of viewing this data would be:
- sudo screen /dev/ttyACM0 115200
