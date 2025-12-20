#!/bin/bash

CMSIS_DIR=cmsis/

git clone --depth 1 --branch 'v6.3.0-rc0' https://github.com/ARM-software/CMSIS_6.git $CMSIS_DIR/cmsis_core
git clone --depth 1 --branch 'v1.12.3' https://github.com/STMicroelectronics/cmsis_device_wb.git $CMSIS_DIR/cmsis_wb

git clone --depth 1 https://github.com/tensorflow/tflite-micro
cd tflite-micro

echo "Checking python, pip, numpy and pil versions, needed for building tflite-micro tests"
python3 --version     
python3 -m pip --version
python3 -m pip show numpy
python3 -m pip show pillow


make -f tensorflow/lite/micro/tools/make/Makefile \
    TARGET=cortex_m_generic \
    TARGET_ARCH=cortex-m4 \
    OPTIMIZED_KERNEL_DIR=cmsis_nn \
    BUILD_TYPE=release \
    microlite
