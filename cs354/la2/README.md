# Language Assignment 2: Verilog - Fibonacci Module
Author: Hunter Barclay

Course: CS 354 (M/W 1:30-2:45pm MT)

## Instructions

To run the project, ensure you currently have access to `iverilog` and `vvp`.
I've found that some nodes don't actually have them for some reason. Generally,
you can enter any module directory within this submission and execute the module
testbench with `make`:

```bash
cd [module you want to test]
make sim
```

See each custom module for specific details on testing them, though they
essentially say the same thing.

## Deliverables
Fibonacci and Adder modules can be found in their respective directories. The
drawings of the Fibonacci module can be found inside it's directory.

## Contents
The following are modules and files at the top level. Custom made modules will be documented further below.

- `add/`: The Adder module (see below).
- `ctr/`: The Counter module. Provided by Professor, counts up or down to target
  value, given initial value. Provides inputs and outputs to tell state of the
  counter.
- `fib/`: The Fibonacci module, the top level module (see below).
- `GNUmakefile`: Make file containing build commands, shared by each of the
  modules. Provided by Professor.
- `README.md`: This file.
- `sto/`: The Store module. Provided by Professor, stores a given value
  inside of it. Provides inputs and outputs to control and access stored value.

## Custom Modules

### Fibonacci Module (fib/)
The Fibonacci module is the top level module for the assignment. It takes in a
value (INP) that determines which index in the Fibonacci sequence you want, then
outputs it. See `fib/Fib.v` for details on the sequence.

To test the module, run the following commands:

```bash
cd fib/
make sim
```

Uncomment line 36 to enable the monitor.

#### Files
- `fib/Fib.v`: Fibonacci module file.
- `fib/test.v`: Test module. Runs the Fibonacci module against input values 0
  through 16. Uncomment line 36 to enable the monitor.
- `fib/monitor`: Monitor for the test module. Will update and print out relevant
  information as it's updated.
- `LA2-Design.png`: Drawing of the Fibonacci module.
- `LA2-Design.svg`: Drawing of the Fibonacci module (svg form).
- `LA2-Design.excalidraw`: Drawing of the Fibonacci module (in original form,
  see [excalidraw](https://excalidraw.com)).
- `fib/Add.v -> add/Add.v`: Adder module file.
- `fib/Ctr.v -> ctr/Ctr.v`: Counter module file.
- `fib/GNUMakefile -> GNUMakefile`: Make file containing build commands.
- `fib/Sto.v -> sto/Sto.v`: Store module file.

### Adder Module (add/)
The Adder module is a submodule for this project. It is a near exact copy of the
Professors Multipler Module (mlt/), with the obvious modification to change the
arithmetic orperation from multiplication to addition.

To test the module, run the following commands:

```bash
cd add/
make sim
```

#### Files
- `add/Add.v`: Adder module file.
- `add/test.v`: Test module. Runs the Adder module against input values `i` and `i * 2` with `i` ranging from 0 to 6 inclusive. Outputs the result.
- `add/monitor`: Monitor file. Needed for the build command; however, is unused.
- `add/GNUMakefile -> GNUMakefile`: Make file containing build commands.

