# codio-lab2

## Lab 2 Part 1: Intro to Processes

This repository contains the completed process lab using the Unix `fork()`, `wait()`, `getpid()`, `getppid()`, `random()`, `srandom()`, and `sleep()` functions.

### Files

- `main3.c` - creates one parent process and exactly two child processes
- `Makefile` - compiles the program into an executable named `my3proc`

### Program behavior

Each child process:

- Runs for a random number of iterations from 1 through 30
- Prints its PID before sleeping
- Sleeps for a random amount of time from 1 through 10 seconds
- Prints its PID and parent PID after waking
- Calls `exit(0)` after its loop finishes

The parent process:

- Creates exactly two child processes
- Calls `wait(&status)` twice
- Prints `Child Pid: <pid> has completed` as each child finishes

### Build

```bash
make
```

This creates:

```text
my3proc
```

### Run

```bash
./my3proc
```

Because the two children run concurrently, the order of their output will vary from run to run.

### View the processes

While the program is running, open another terminal and run:

```bash
ps -ef
```

You should be able to identify the parent and its two children by comparing the PID and PPID columns.

### Clean

```bash
make clean
```
