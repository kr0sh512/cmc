#!/bin/bash

# Compile and run as in unicorn

if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <cpp_file> <argument>"
    exit 1
fi

CPP_FILE=$1
ARGUMENT=$2

# Format the C++ file with clang-format
clang-format -i -style=file "$CPP_FILE"

# Compile the C++ file
g++ "$CPP_FILE" -o run -O2 -Wall -Werror -std=gnu++23 -lm

# Check if the compilation was successful
if [ $? -ne 0 ]; then
    echo "Compilation failed"
    exit 1
fi

# Run the compiled program with the provided argument
./run "$ARGUMENT"