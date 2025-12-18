#!/bin/bash

CMSIS_DIR=cmsis/

git clone --depth 1 --branch 'v6.3.0-rc0' https://github.com/ARM-software/CMSIS_6.git $CMSIS_DIR/cmsis_core
git clone --depth 1 --branch 'v1.12.3' https://github.com/STMicroelectronics/cmsis_device_wb.git $CMSIS_DIR/cmsis_wb

git clone --depth 1 https://github.com/tensorflow/tflite-micro
cd tflite-micro

echo "Checking python version, needed for building tflite-micro"
python3 --version

echo "Creating venv"
mkdir -p venv
python3 -m venv ./venv
./venv/bin/python3 -m pip install numpy

echo "Creating alias for python3 so google's python script will execute using our venv"

alias python3='./venv/bin/python3'

make -f tensorflow/lite/micro/tools/make/Makefile \
    TARGET=cortex_m_generic \
    TARGET_ARCH=cortex-m4 \
    OPTIMIZED_KERNEL_DIR=cmsis_nn \
    microlite
