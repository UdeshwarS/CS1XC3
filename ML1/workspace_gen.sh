#!/bin/bash

# 1. Validation: Ensure 3 arguments are provided

if [ "$#" -ne 3 ]; then
    echo "Usage: $0 <num_dirs> <num_data_files> <num_junk_files>"
    echo "Example: $0 5 10 20"
    if [ "$#" -eq 1 ] && [ "$1" == "help" ]; then
        exit 0
    else
        exit 1
    fi
fi

# Assign arguments to descriptive variables
num_dirs=$1
num_data=$2
num_junk=$3

# 2. Check if run_me.sh exists and is executable
if [ ! -x "./log_gen2.sh" ]; then
    echo "Error: ./log_gen2.sh not found or not executable."
    exit 1
fi

# 3. Outer Loop: Create Directories
for ((i=1; i<=num_dirs; i++))
do
    dir_name="dir_$i"
    mkdir -p "$dir_name"

    # 4. Inner Loop A: Create "Irrelevant" files
    for ((j=1; j<=num_junk; j++))
    do
        # Generate a random 8-character filename
        rand_name=$(LC_ALL=C tr -dc 'a-zA-Z0-9' < /dev/urandom | head -c 8)
        echo "This file is irrelevant Velocity Temperature Distance Length MPH in ft F" > "$dir_name/$rand_name.log"
    done

    # 5. Inner Loop B: Create Data files via run_me.sh
    for ((k=1; k<=num_data; k++))
    do
        ./log_gen2.sh 200 > "$dir_name/data_$k.log"
    done
done

echo "Done! Created $num_dirs directories with $(($num_data + $num_junk)) files in each."
