# Homework 3: Shell
- Hunter Barclay
- March 5th, 2025
- CS 452

## Deliverables
- `deq/` -> Copy of my deq from homework 1, with slight modifications for compilation purposes.
- `tests/` -> Directory of all the tests.
- `Command.[c|h]` -> Command module. Create an execute commands interpreted by the shell.
- `error.h` -> Error header file. Copied from Deq.
- `GNUMakefile` -> Compilation file. See below for details on how to compile and run.
- `grammar.txt` -> Provided grammar for shell language.
- `Interpreter.[c|h]` -> Interpreter module. Take in parsed AST and execute sequences.
- `Jobs.[c|h]` -> Jobs module. Wrapper for Deq to store, wait on, and free pipelines (jobs).
- `Parser.[c|h]` -> Provided, and slighly modified, parser module for parsing shell language.
- `Pipeline.[c|h]` -> Pipeline module. Used to execute interpreted pipelines.
- `README.md` -> This file.
- `rl.supp` -> Provided valgrind suppressions.
- `run-tests` -> Originally name `run`, this shell script runs the regression tests.
- `Scanner.[c|h]` -> Scanner module. Provided by prof, used to tokenize input.
- `Sequence.[c|h]` -> Sequence module. Used to execute interpreted sequences.
- `Shell.c` -> Main executable file. This creates the core loop of the application.
- `Tree.[c|h]` -> Tree module. Used to store AST from parser and for use in the interpreter.
- `Utils.[c|h]` -> Utils module. Added this to place the code to wait on a process in a module for generic reuse in Pipelines and Commands.
- `vg` -> Provided script for running shell with valgrind.

## Building and using the Shell
To build the shell, you can simply run the default make target, then run the `shell` output executable:

```bash
make
./shell
```

## Testing the Shell
To test the shell, you can run the `test` make target, which will compile the shell and run the regression tests. Alternatively, you can just use `run-tests` to skip the compilation step:

```bash
# Compile and run tests
make test

# Just run tests
./run-tests
```

## Implementation Details

### Background Jobs
When a background job is created (specifically an entire pipeline running in a children process), the process ID is printed along with a plus character
to indicate a background job. Likewise, when the background task is waited on and reaped by the parent process, the process ID is printed out with
a dash character. These print outs are done to STDERR to avoid issues with testing.