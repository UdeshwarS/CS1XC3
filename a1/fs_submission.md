# I. Understanding the File System

## Part 1: Basic exploration

### Q1 Use `ls` to list the content in the cwd in long listing and human-readable format.

```bash
$ ls -lh
total 40K
-rwxr-xr-x 1 udesh_linux udesh_linux  545 Jan 28 21:03 README.md
-rwxr-xr-x 1 udesh_linux udesh_linux  586 Jan 28 21:03 archive_submission.md
drwxr-xr-x 2 udesh_linux udesh_linux 4.0K Jan 28 21:03 ascii
drwxr-xr-x 2 udesh_linux udesh_linux 4.0K Jan 28 21:03 books
drwxr-xr-x 4 udesh_linux udesh_linux 4.0K Jan 28 21:03 data
drwxr-xr-x 2 udesh_linux udesh_linux 4.0K Jan 28 21:03 foo
-rwxr-xr-x 1 udesh_linux udesh_linux 5.1K Jan 28 21:03 fs_submission.md
drwxr-xr-x 2 udesh_linux udesh_linux 4.0K Jan 28 21:03 images
-rwxr-xr-x 1 udesh_linux udesh_linux 1.3K Jan 28 21:03 script_submission.md
```

### Q2. `du -h foo && du -h images`

Replace the blank with the correct answer.

This command line shows the sizes and names of the foo and images directories. 


### Q3. Matching command lines to their descriptions

1. `du -h fooo && du -h images`: A 
2. `du -h foo || du -h images`: E
3. `du -h fooo || du -h images`: F
4. `du -h foo ; du -h images`: D
5. `du -h fooo ; du -h images`: B
6. `du -h foo && du -h images`: C

Match each command line with the best description below. Each description may be used once. Replace the blanks above with the correct letter.

A. The second command does not run because the first command fails.

B. The first command fails, but it doesn’t matter, the second command will run anyway.

C. The second command runs only because the first command succeeded. 

D. The first command runs successfully and then the second command runs. 

E. Only the first command runs. 

F. The second command runs only because the first command fails.

### Q4. Use an appropriate command line from above to check the sizes of the foo and images directories. 

```bash
$ du -h foo && du -h images
1.3M    foo
964K    images
```

### Q5. Which directory takes up more space on disk?

Answer: foo

### Q6. List the contents of foo and images using only long listing and human-readable format.

```bash
$ ls -lh foo
total 0
$ ls -lh images
total 960K
-rwxr-xr-x 1 udesh_linux udesh_linux    2 Jan 28 21:03 a.txt
-rwxr-xr-x 1 udesh_linux udesh_linux    2 Jan 28 21:03 b.txt
-rwxr-xr-x 1 udesh_linux udesh_linux  29K Jan 28 21:03 black-cat.png
-rwxr-xr-x 1 udesh_linux udesh_linux    2 Jan 28 21:03 c.txt
-rwxr-xr-x 1 udesh_linux udesh_linux 913K Jan 28 21:03 phone.gif
```

### Q7. Which directory has a longer list of files?
Answer: images 

### Q8. Modify the flags of `ls` to list *all* files in `foo`, including hidden files.

```bash
$ ls -lah foo
total 1.3M
drwxr-xr-x 2 udesh_linux udesh_linux 4.0K Jan 28 21:03 .
drwxr-xr-x 7 udesh_linux udesh_linux 4.0K Jan 28 21:27 ..
-rwxr-xr-x 1 udesh_linux udesh_linux  29K Jan 28 21:03 .black-cat.png
-rwxr-xr-x 1 udesh_linux udesh_linux 913K Jan 28 21:03 .phone.gif
-rwxr-xr-x 1 udesh_linux udesh_linux 294K Jan 28 21:03 .secret

```

### Q9. Creating files

Make a directory called `find_test` and `cd` into it. Write for-loop on one line that creates files `1.txt`, `2.txt`, ... `5.txt` using `touch`. Then, using `echo` create a file called `"spaces in the name.txt"` that has one line of text that reads “my name has spaces”. 

```bash
$ for i in {1..5}; do touch "$i.txt"; done
$ echo "my name has spaces" > "spaces in the name.txt"
```

### Q10. Run the following command and paste the output in your submission.

```bash
$ find . -type f -name "*"
./archive_submission.md
./books/compute_avg_time.sh
./books/books_submission.md
./foo/.black-cat.png
./foo/.secret
./foo/.phone.gif
./.gitignore
./ascii/owl.txt
./ascii/ascii_submission.md
./find_test/4.txt
./find_test/3.txt
./find_test/2.txt
./find_test/1.txt
./find_test/spaces in the name.txt
./find_test/5.txt
./fs_submission.md
./README.md
./images/a.txt
./images/phone.gif
./images/b.txt
./images/c.txt
./images/black-cat.png
./data/lorem/loremipsum.txt
./data/climate_data/climate_station_list.csv
./data/climate_data/daily_csv_list.html
./data/climate_data/ml_pattern_match.html
./data/climate_data/ontario_page1.html
./data/climate_data/csv_pattern_match_test.txt
./script_submission.md
```

## Part 2. Find Pipelines
Your cwd should be find_test.
Explore the following commands and how they differ.

```bash
find . -type f -name "*"
find . -type f -name "*" | xargs
find . -type f -name "*" | xargs ls
```

1. What happens to the output of the first command in `find . -type f -name "*" | xargs` ?

xargs takes the lines output by find and combines them into a single space-separated list of arguments.

2. Describe the issue that occurs in in `find . -type f -name "*" | xargs ls` and explain why it happens.

It breaks on the filename with spaces (spaces in the name.txt). xargs splits input on whitespace, so ./spaces in the name.txt becomes
 separate arguments (./spaces, in, the, name.txt), and ls errors because those files don’t exist.

3. Run the following commands and paste the output in your submission.
    
    ```bash
find . -type f -name "*" | xargs -I {} ls -l
total 4
-rw-r--r-- 1 udesh_linux udesh_linux 0 Jan 28 21:28  1.txt
-rw-r--r-- 1 udesh_linux udesh_linux 0 Jan 28 21:28  2.txt
-rw-r--r-- 1 udesh_linux udesh_linux 0 Jan 28 21:28  3.txt
-rw-r--r-- 1 udesh_linux udesh_linux 0 Jan 28 21:28  4.txt
-rw-r--r-- 1 udesh_linux udesh_linux 0 Jan 28 21:28  5.txt
-rw-r--r-- 1 udesh_linux udesh_linux 19 Jan 28 23:09 'spaces in the name.txt'
total 4
-rw-r--r-- 1 udesh_linux udesh_linux 0 Jan 28 21:28  1.txt
-rw-r--r-- 1 udesh_linux udesh_linux 0 Jan 28 21:28  2.txt
-rw-r--r-- 1 udesh_linux udesh_linux 0 Jan 28 21:28  3.txt
-rw-r--r-- 1 udesh_linux udesh_linux 0 Jan 28 21:28  4.txt
-rw-r--r-- 1 udesh_linux udesh_linux 0 Jan 28 21:28  5.txt
-rw-r--r-- 1 udesh_linux udesh_linux 19 Jan 28 23:09 'spaces in the name.txt'
total 4
-rw-r--r-- 1 udesh_linux udesh_linux 0 Jan 28 21:28  1.txt
-rw-r--r-- 1 udesh_linux udesh_linux 0 Jan 28 21:28  2.txt
-rw-r--r-- 1 udesh_linux udesh_linux 0 Jan 28 21:28  3.txt
-rw-r--r-- 1 udesh_linux udesh_linux 0 Jan 28 21:28  4.txt
-rw-r--r-- 1 udesh_linux udesh_linux 0 Jan 28 21:28  5.txt
-rw-r--r-- 1 udesh_linux udesh_linux 19 Jan 28 23:09 'spaces in the name.txt'
total 4
-rw-r--r-- 1 udesh_linux udesh_linux 0 Jan 28 21:28  1.txt
-rw-r--r-- 1 udesh_linux udesh_linux 0 Jan 28 21:28  2.txt
-rw-r--r-- 1 udesh_linux udesh_linux 0 Jan 28 21:28  3.txt
-rw-r--r-- 1 udesh_linux udesh_linux 0 Jan 28 21:28  4.txt
-rw-r--r-- 1 udesh_linux udesh_linux 0 Jan 28 21:28  5.txt
-rw-r--r-- 1 udesh_linux udesh_linux 19 Jan 28 23:09 'spaces in the name.txt'
total 4
-rw-r--r-- 1 udesh_linux udesh_linux 0 Jan 28 21:28  1.txt
-rw-r--r-- 1 udesh_linux udesh_linux 0 Jan 28 21:28  2.txt
-rw-r--r-- 1 udesh_linux udesh_linux 0 Jan 28 21:28  3.txt
-rw-r--r-- 1 udesh_linux udesh_linux 0 Jan 28 21:28  4.txt
-rw-r--r-- 1 udesh_linux udesh_linux 0 Jan 28 21:28  5.txt
-rw-r--r-- 1 udesh_linux udesh_linux 19 Jan 28 23:09 'spaces in the name.txt'
total 4
-rw-r--r-- 1 udesh_linux udesh_linux 0 Jan 28 21:28  1.txt
-rw-r--r-- 1 udesh_linux udesh_linux 0 Jan 28 21:28  2.txt
-rw-r--r-- 1 udesh_linux udesh_linux 0 Jan 28 21:28  3.txt
-rw-r--r-- 1 udesh_linux udesh_linux 0 Jan 28 21:28  4.txt
-rw-r--r-- 1 udesh_linux udesh_linux 0 Jan 28 21:28  5.txt
-rw-r--r-- 1 udesh_linux udesh_linux 19 Jan 28 23:09 'spaces in the name.txt'

find . -type f -name "*" | xargs -I {} ls -l {}
-rw-r--r-- 1 udesh_linux udesh_linux 0 Jan 28 21:28 ./4.txt
-rw-r--r-- 1 udesh_linux udesh_linux 0 Jan 28 21:28 ./3.txt
-rw-r--r-- 1 udesh_linux udesh_linux 0 Jan 28 21:28 ./2.txt
-rw-r--r-- 1 udesh_linux udesh_linux 0 Jan 28 21:28 ./1.txt
-rw-r--r-- 1 udesh_linux udesh_linux 19 Jan 28 23:09 './spaces in the name.txt'
-rw-r--r-- 1 udesh_linux udesh_linux 0 Jan 28 21:28 ./5.txt
    ```
   
4. Describe what `xargs -I {} ls -l` and `xargs -I {} ls {} -l` actually execute after the pipe.

After the pipe, xargs -I {} runs the ls -l ... command once per line from find, substituting {} with the filename. So it effectively
executes ls -l <file> for each file.
5. `cd` to the parent directory (your cwd should be `a1`). Write a pipeline that produces the list of all files (including hidden) in the repo (including files in subdirectories) sorted by size from smallest to largest, in human-readable format. Ensure your pipeline is able to handle spaces in filenames. You can build from the commands above to use a `find | xargs` pipeline, or explore using `-exec` instead of `| xargs`.
    
    ```bash
$ find . -type f -print0 | xargs -0 ls -lh | sort -k5h
-rw-r--r-- 1 udesh_linux udesh_linux     0 Jan 28 21:28 ./find_test/1.txt
-rw-r--r-- 1 udesh_linux udesh_linux     0 Jan 28 21:28 ./find_test/2.txt
-rw-r--r-- 1 udesh_linux udesh_linux     0 Jan 28 21:28 ./find_test/3.txt
-rw-r--r-- 1 udesh_linux udesh_linux     0 Jan 28 21:28 ./find_test/4.txt
-rw-r--r-- 1 udesh_linux udesh_linux     0 Jan 28 21:28 ./find_test/5.txt
-rwxr-xr-x 1 udesh_linux udesh_linux     2 Jan 28 21:03 ./images/a.txt
-rwxr-xr-x 1 udesh_linux udesh_linux     2 Jan 28 21:03 ./images/b.txt
-rwxr-xr-x 1 udesh_linux udesh_linux     2 Jan 28 21:03 ./images/c.txt
-rw-r--r-- 1 udesh_linux udesh_linux 19 Jan 28 23:09 ./find_test/spaces in the name.txt
-rwxr-xr-x 1 udesh_linux udesh_linux    18 Jan 28 21:03 ./ascii/owl.txt
-rwxr-xr-x 1 udesh_linux udesh_linux    24 Jan 28 21:03 ./.gitignore
-rwxr-xr-x 1 udesh_linux udesh_linux   156 Jan 28 21:03 ./data/climate_data/csv_pattern_match_test.txt
-rwxr-xr-x 1 udesh_linux udesh_linux   531 Jan 28 21:03 ./ascii/ascii_submission.md
-rwxr-xr-x 1 udesh_linux udesh_linux   545 Jan 28 21:03 ./README.md
-rwxr-xr-x 1 udesh_linux udesh_linux   586 Jan 28 21:03 ./archive_submission.md
-rwxr-xr-x 1 udesh_linux udesh_linux   756 Jan 28 21:03 ./books/compute_avg_time.sh
-rwxr-xr-x 1 udesh_linux udesh_linux   945 Jan 28 21:03 ./data/climate_data/ml_pattern_match.html
-rwxr-xr-x 1 udesh_linux udesh_linux  1.3K Jan 28 21:03 ./script_submission.md
-rwxr-xr-x 1 udesh_linux udesh_linux  2.0K Jan 28 21:03 ./books/books_submission.md
-rwxr-xr-x 1 udesh_linux udesh_linux  3.4K Jan 28 21:03 ./data/lorem/loremipsum.txt
-rwxr-xr-x 1 udesh_linux udesh_linux   10K Jan 28 21:46 ./fs_submission.md
-rwxr-xr-x 1 udesh_linux udesh_linux   29K Jan 28 21:03 ./foo/.black-cat.png
-rwxr-xr-x 1 udesh_linux udesh_linux   29K Jan 28 21:03 ./images/black-cat.png
-rwxr-xr-x 1 udesh_linux udesh_linux  294K Jan 28 21:03 ./foo/.secret
-rwxr-xr-x 1 udesh_linux udesh_linux  913K Jan 28 21:03 ./foo/.phone.gif
-rwxr-xr-x 1 udesh_linux udesh_linux  913K Jan 28 21:03 ./images/phone.gif
-rwxr-xr-x 1 udesh_linux udesh_linux 1023K Jan 28 21:03 ./data/climate_data/climate_station_list.csv
-rwxr-xr-x 1 udesh_linux udesh_linux  5.7M Jan 28 21:03 ./data/climate_data/daily_csv_list.html
-rwxr-xr-x 1 udesh_linux udesh_linux  5.7M Jan 28 21:03 ./data/climate_data/ontario_page1.html
    ```

## Part 3. Aliases

1. Create an alias called `findbig` that finds all files larger than 5 MB in the cwd. With `a1` as the cwd, run the alias and paste the 
output in your submission.
    
    ```bash
$ alias findbig='find . -type f -size +5M'
$ findbig
./data/climate_data/daily_csv_list.html
./data/climate_data/ontario_page1.html

    ```
    
2. Create an alias called `oldest` that outputs the name of the oldest item in the current working directory. With `a1` as the cwd, 
run the alias and paste the output in your submission.
    
    ```bash
$ alias oldest='ls -1tr | head -n 1'
$ oldest
script_submission.md
    ```

## Part 4. Observing changes with `stat` (ready)

Do the following activities with `a1` as your cwd.

1. Write a pipeline that outputs the name of the 2nd oldest file in the `images` directory to the file `images/2nd.txt`
    
    ```bash
$ ls -1tr images | sed -n '2p' > images/2nd.txt
    ```
    
2. Use `touch` to create an empty file in the foo directory called `.emptyfile.txt`. Then, write a single command that moves the hidden ‘.emptyfile.txt’ to the `images` directory and renames it `emptyfile.txt` so it is not hidden.
    
    ```bash
$ touch foo/.emptyfile.txt && mv foo/.emptyfile.txt images/emptyfile.txt
    ```
    
3. Complete the following steps, then answer the questions that follow:
    
    ```bash
    Run `stat` on the file and observe the dates
    Append “Hello World” to the `emptyfile.txt`
    Run `stat` to observe the dates.
    Change the name of the file to `hello.txt`
    Run stat and observe the dates.
    ```
    
    1. Which date tells us what time you added hello world to the file? 
        Answer: Modify (mtime)
    2. Which date tells us what time you renamed the file?
        Answer: Change (ctime)
