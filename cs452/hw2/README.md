# Homework 2: Buddy Allocator
- Hunter Barclay
- CS 452
- Feb. 16th, 2025

## Deliverables
- `balloc.[c|h]` -> Buddy allocator module. This has the core allocator functionality.
- `bbm.[c|h]` -> Buddy Bit Map module. This is the bitmap used for tracking if a buddy
    pair is allocated or not.
- `bm.[c|h]` -> Bit Map module. Handles generic n-length bitmap.
- `error.h` -> Macros useful for logging errors to the console.
- `freelist.[c|h]` -> FreeList module. Tracks freelists for the buddy allocator.
- `GNUmakefile` -> Core makefile used for compiling Homework 2.
- `ParentMakefile` -> Parent makefile provided by Buff for easy compiling.
- `README.md` -> This file.
- `test.c` -> Unit testing file.
- `utils.[c|h]` -> Utility module. Has useful functions for implementing the assignment ()
- `wrapper.c` -> Wrapper code for making malloc and free use the buddy allocator.
- `hw1/` -> Homework 1. Tests are run using the wrapper to show the use of the buddy allocator.
    Slightly modified due to compiling issues with original submission.

## How to Grade
### Compile and Test Buddy Allocator
To compile and test the buddy allocator, you can use the default make target:

```bash
make
```

Then, run the `buddy` executable:

```bash
./buddy
```

See output to verify all tests pass.

### Wrapper and Homework 1
To use the buddy allocator for homework 1, go into the homework 1 directory,
then compile it using the following commands:

```bash
cd hw1
make
```

Next, make sure homework 2 is compiled, then compile the `try` executable, which
will run the homework 1 unit tests with the buddy allocator.

```bash
# Ensure you are in homework 2
cd ..
# Compile homework 2 (again)
make
# Compile homework 1 with wrapper
make try
# Run the homework 1 unit tests
./try
```