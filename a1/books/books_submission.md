


# II. Pride and Prejudice

## Part 1. Download and explore the file


### Q1. Write a command to count the number of lines in the pride_and_prejudice.txt and provide the output.

```
$ wc -l pride_and_prejudice.txt
14537 pride_and_prejudice.txt
```

## Part 2. Time different pipelines

### Q2. Fill in the table to indicate the fastest and slowest by their average sys time

| summary | pipeline | real fastest (1) to slowest (5)  | user fastest (1) to slowest (5)  | sys  fastest (1) to slowest (5)  |
| --- | --- | --- | --- | --- |
| **`sed`** | `sed -n '1000,2000p' pride_and_prejudice.txt > /dev/null` |2  |1  |1  |
| **`tail | head`** | `tail -n +1000 pride_and_prejudice.txt | head -n 1001 > /dev/null` |3  |4  |2  |
| **`head | tail`** | `head -n 2000 pride_and_prejudice.txt | tail -n 1001 > /dev/null` |1  |2  |4  |
| **`cat | awk`** | `cat pride_and_prejudice.txt | awk 'NR>=1000 && NR<=2000' > /dev/null` |5  |5  |5  |
| **`awk`** | `awk 'NR>=1000 && NR<=2000' pride_and_prejudice.txt > /dev/null` |4  |3  |3  |


### Q3. Reflection questions:

1. Describe the difference observed between `cat | awk` and `awk` in the timed trials. What effect does cat appear to have?
   Answer:

awk by itself is faster. Adding cat (cat | awk) adds an extra process and an extra pipe, so the system has to spawn cat, pipe all the text 
through it, and then awk reads from stdin instead of reading the file directly. That extra overhead increases time (especially sys time).

2. Imagine running these on a 10GB file with 100 million lines (instead of the fairly small `pride_and_prejudice.txt` file). Rank them from fastest to slowest and explain your reasoning. For each pipeline, describe what it does and why you ranked it where you did.
   Answer:

1) sed -n '1000,2000p' file

Fastest because sed reads only up to line 2000 and then stops, so it processes a tiny part of the file.

2) head -n 2000 file | tail -n 1001

Fast because head stops after the first 2000 lines, so only a small prefix of the file is read.

3) awk 'NR>=1000 && NR<=2000' file > /dev/null

Slower than sed/head because awk still reads up to line 2000 and does more per-line processing than simple line tools.

4) cat file | awk 'NR>=1000 && NR<=2000' > /dev/null

Slower because it does the same work as awk but adds an unnecessary extra cat process and a pipe.

5) tail -n +1000 file | head -n 1001 > /dev/null

Slowest because tail -n +1000 effectively has to read through the file and would output almost everything from line 1000 onward, 
even though head only keeps 1001 lines.


## Part 3. Automating file creation with content extraction

### Q4. Write a for-loop

Write your own for-loop that creates 5 files part[1-5].txt, each containing 1000 lines from pride_and_prejudice.txt as follows:

- `part1.txt` → lines 1–1000
- `part2.txt` → lines 1001–2000
- … up to `part5.txt` → lines 4001–5000

```bash
for i in {1..5}; do
  start=$(( (i-1)*1000 + 1 ))
  end=$(( i*1000 ))
  sed -n "${start},${end}p" pride_and_prejudice.txt > "part${i}.txt"
done
```

### Q5. Write one command to observe the file sizes in human-readable format.

```bash
$ ls -lh part*.txt
-rw-r--r-- 1 udesh_linux udesh_linux 48K Jan 28 22:22 part1.txt
-rw-r--r-- 1 udesh_linux udesh_linux 47K Jan 28 22:22 part2.txt
-rw-r--r-- 1 udesh_linux udesh_linux 47K Jan 28 22:22 part3.txt
-rw-r--r-- 1 udesh_linux udesh_linux 53K Jan 28 22:22 part4.txt
-rw-r--r-- 1 udesh_linux udesh_linux 53K Jan 28 22:22 part5.txt
```
