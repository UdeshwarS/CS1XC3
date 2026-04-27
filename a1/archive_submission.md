# IV. Compression

1. Create a directory called `project`. Use redirection to write the last 50 lines of your shell command history to a file in `project` called `history.txt`.
    
    ```bash
$ mkdir -p project
$ history | tail -n 50 > project/history.txt
    ```
    
2. Then, using the `tar` command, create a compressed archive of the `project` directory called `project.tar.gz` such that it can be decompressed using `gzip -d`.
    
    ```bash
$ tar -czf project.tar.gz project
$ cp project.tar.gz project_copy.tar.gz
$ gzip -d project_copy.tar.gz
    ```
