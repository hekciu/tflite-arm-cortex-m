#!/bin/bash


MODEL_PATH=${PWD}/../model/models/sine_model.tflite
MODEL_OUTPUT_PATH=${PWD}/sine_model.h

xxd -name model -i ${MODEL_PATH} > ${MODEL_OUTPUT_PATH}
