## Reflection Questions
1: Explain how the incorrect loop condition (`<= n`) led to an out-of-bounds memory access and ultimately a segmentation fault in `SelectionSort.c`

The loop condition <= n let the code access index n, but valid array indexes only go from 0 to n - 1, so it read or wrote past the end of the array. That out-of-bounds access corrupted memory, which is why the program could print garbage values, trigger stack smashing, or crash with a segmentation fault.


2: What specifically causes a merge conflict to occur? Why can't Git just figure out what you want it to do automatically?
    - What are ways to reduce the chances of a merge conflict occurring

A merge conflict happens when two branches change the same file in the same area and Git cannot safely decide which version should stay. Git cannot automatically guess the programmer’s intent, so a person has to choose whether to keep one version, the other, or combine both; conflicts can be reduced by pulling often, using separate branches, and avoiding editing the same lines at the same time.


3: Why is it safer to merge code through a Merge Request on GitLab rather than just running `git merge` locally and pushing straight to the `main` branch?

Merging through a Merge Request is safer because it gives the team a place to review the code, catch mistakes, and see conflicts before changes reach main. It also makes the process more controlled and visible than merging locally and pushing directly, which lowers the chance of bad code or accidental conflicts going straight into the main branch.

4: When resolving the conflict in `main.c`, what would happen if you accidentally left one of the Git conflict markers (like `=======`) in your code and tried to compile it using `gcc`?

If you left a conflict marker like ======= in main.c, gcc would treat it as invalid C code and the file would fail to compile. That is why the lab tells you to remove the conflict markers and edit the file into one correct final version before committing the resolved merge.