#!/bin/bash

echo "Version: "
python3 --version

mkdir -p venv
python3 -m venv ./venv

./venv/bin/pip3 install -r requirements.txt --no-cache-dir

