
# III. ASCII Art

Provide the pipeline or series of commands you used to fix owl.txt 
```bash
sed -i '1s@/\\_\\@/\\_/\\@' owl.txt
sed -i '2c\((ovo))' owl.txt
sed -i '3c\():::()' owl.txt
sed -i '3a\ VV-VV' owl.txt

```

Make sure your solution follows these requirements:
1. You must modify the file in place using `sed -i` rather than writing output to a new file and concatenating/appending with `echo` or `cat`.
2. Do not manually edit the file in a text editor. The goal is to use command-line text manipulation.
3. Using `echo`, `printf`, `cat`, or manually editing the file will not receive credit.

