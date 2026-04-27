#!/bin/bash
# compute_avg_time.sh
# Usage: ./compute_avg_time.sh <TIME_TYPE> <TIMING_FILE>
# TIME_TYPES: real, user, sys

# basic argument check
if [[ $# -ne 2 ]]; then
    echo "Usage: $0 <TIME_TYPE> <TIMING_FILE>"
    exit 1
fi

# function to compute average time from the files
avg_time() {
    local TIME_TYPE=$1
    local FILE=$2
    local COMMAND=${FILE%_times.txt} # removes _times.txt suffix

    grep -E "^${TIME_TYPE}[[:space:]]+[0-9]+m[0-9]+(\.[0-9]+)?s" "$FILE" | \
    awk -v command="$COMMAND" -v type="$TIME_TYPE" '{
        split($NF, t, "[ms]");
        sum += t[1]*60 + t[2];
        n++
    }
    END {
        printf "%s %s avg: %.5f\n", command, type, sum/n
    }'

}

# call the function with command line arguments
avg_time "$1" "$2"