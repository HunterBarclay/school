# Homework 4: Wack-a-mole
- Hunter Barclay
- March 31st, 2025
- CS 452

## Deliverables
The follow excludes any unmodified files provided by the professor for this
assignment:

- `deq/` -> Homework 1, with modifications from Homework 3 to work better as a
  dependency.
- `GNUmakefile` -> My own modified version of the makefile to include everything
  in a single makefile.
- `mtq.[c|h]` -> Multithreaded queue module. Simple MT wrapper for dequeue.
- `main.c` -> Modified main file to create threads for produce and consume, and
  force each to use the same MTQ.
- `vg` -> Copied from Homework 3.
- `rl.supp` -> Modified from Homework 3 to instead block out valgrind checks for
  FLTK and X11.
- `valgrind_report.txt` -> Required valgrind report. It still shows reachable
  blocks, but they are being allocated by dlopen and I'm not exactly going to
  suppress libc.

## How to Run
Run the follow commands to compile and run the project.

```bash
# Compiles Deq and the rest of the assignment.
make

# Runs the program.
./wam
```

Current produces and wacks 10 moles, with a maximum Mtq capacity of 4.
