#!/usr/bin/env bash
p="$(basename "$0")" # gets the name of the file for the usage

# Need exactly 2 args
[ "$#" -eq 2 ] || { echo "Usage: $p <Velocity|Distance|Length|Temperature> <0|1>"; exit 1; } # checks that the user did input only 2

r="$1" # Read/line read
o="$2" # Sort/number read

# Validate reading + option
case "$r" in Velocity|Distance|Length|Temperature) ;; *) echo "Usage: $p <Velocity|Distance|Length|Temperature> <0|1>"; exit 1;; esac 
# Makes sure the word is one of the 4 above

case "$o" in 0|1) ;; *) echo "Usage: $p <Velocity|Distance|Length|Temperature> <0|1>"; exit 1;; esac
#Makes sure the number is either 0 or 1

out="${r}_metric_sorted_${o}.log" #Makes the correct file name

# Extract + convert
find dir_* -type f -name 'data_*.log' -exec cat {} + 2>/dev/null | 
# looks through the files with data_(ignoring any no permission files), prints the content


awk -F $'\t' -v OFS=$'\t' -v R="$r" ' # colums seperated by tabs, when printing also seperate by tabs, telling the finder (awk) to look for r
  $2==R{ #Looking at lines where column 2 is the input of r
    if($4=="MPH"){ $3=sprintf("%.2f",$3*1.6093); $4="km/h" } 
    else if($4=="ft"){ $3=sprintf("%.2f",$3*0.3048); $4="m" }
    else if($4=="in"){ $3=sprintf("%.2f",$3*2.54); $4="cm" }
    else if($4=="F"){ $3=sprintf("%.2f",(5*($3-32))/9); $4="C" }
    print
#Converting from imperical to metric according to the column ^^ (in col 4 if its MPH, take col 3 and conv according to the math and rename 
#col 4 as metric

  }
' |
# Sort + save
if [ "$o" -eq 0 ]; then   # checks the option of the number, if its 0 or 1
  sort -t $'\t' -k3,3nr > "$out"  # Sort according to col 3 (-k3,3), numeric(n), decending(r)
else
  sort -t $'\t' -k5,5 > "$out" #Sort by col 5, ascending order
fi

echo "Wrote: $out" #print to file
