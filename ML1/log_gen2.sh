#!/bin/bash

if [ -z "$1" ]; then
    echo "Usage: $0 <number_of_lines>"
    exit 1
fi

num_lines=$1

# We pass the Bash arrays into AWK as one long string
locations="New York, NY|Los Angeles, CA|Chicago, IL|Houston, TX|Phoenix, AZ|Philadelphia, PA|San Antonio, TX|San Diego, CA|Dallas, TX|San Jose, CA|Austin, TX|Jacksonville, FL|Fort Worth, TX|Columbus, OH|Charlotte, NC|San Francisco, CA|Indianapolis, IN|Seattle, WA|Denver, CO|Washington, DC|Boston, MA|El Paso, TX|Nashville, TN|Detroit, MI|Oklahoma City, OK|Portland, OR|Las Vegas, NV|Memphis, TN|Louisville, KY|Baltimore, MD"

awk -v n="$num_lines" -v loc_str="$locations" 'BEGIN {
    split(loc_str, locs, "|");
    split("Velocity Distance Temperature Length", data_types, " ");
    split("MPH ft F in", unit_types, " ");
    srand();

    for (i = 1; i <= n; i++) {
        l_idx = int(rand() * 30) + 1;
        t_idx = int(rand() * 4) + 1;
        reading = rand() * 150;
        
        month = int(rand() * 12) + 1;
        day = int(rand() * 28) + 1;
        
        printf("%s\t%s\t%.2f\t%s\t2025-%02d-%02d\n", 
            locs[l_idx], data_types[t_idx], reading, unit_types[t_idx], month, day);
    }
}'
