# Tick Demo



First, try the basic demo:
```bash
make basic && ./tick_demo
```

Consider this line in in basic_demo.c: `#define SECONDS_PER_TICK 0.3` 
- 0.3 is the time of the delay in seconds. 
- Try different values to see how it affects the speed of M.


There is also a demo that uses the `input` module we provide. The makefile provides a few rules to build the program so that the game loop progresses at different speeds:

```bash
make        # default (0.3s)
make fast   # 0.1s
make medium # 0.5s
make slow   # 1.0s
```

Each build produces `tick_demo` that you can run with 

```bash
./tick_demo
```

Make and run on one line like

```bash
make slow && ./tick_demo
make fast && ./tick_demo
# etc...
```
