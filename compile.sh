#!/bin/bash

# Check if the correct number of arguments are provided
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <cpp_file> <argument>"
    exit 1
fi

CPP_FILE=$1
ARGUMENT=$2

# Format the C++ file with clang-format
clang-format -i -style=file "$CPP_FILE"

# Compile the C++ file
g++ "$CPP_FILE" -o run

# Check if the compilation was successful
if [ $? -ne 0 ]; then
    echo "Compilation failed"
    exit 1
fi

# Run the compiled program with the provided argument
./run "$ARGUMENT"