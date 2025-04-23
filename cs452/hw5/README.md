# Homework 5: Scanner Kernel Module (Driversity)
- Hunter Barclay
- CS 452
- April 23rd, 2025

## Deliverables
- `README.md` -> This file.
- `start.sh` -> Alias for Buff's `hw5boot` script for starting the VM.
- `stop.sh` -> Stops the running VM.
- `node.sh` -> Alias for Buff's `sshnode` script for connecting to an onyx node.
- `copy.sh` -> Copies the `Scanner/` directory to the VM.
- `Scanner/` -> Scanner kernel module source.
- `Scanner/Makefile` -> Makefile for compiling, installing, trying, and testing the Scanner.
- `Scanner/Scanner.c` -> Main source file for the Scanner kernel module.
- `Scanner/TestScanner.c` -> Both the source for the test suite for the Scanner and the "try" interface.
- `getmaj` -> I have no clue what this is, but it's used for the kernel module installation process. Something along the lines of looking for the module in devices?

## How to compile/setup
### VM Setup
To prepare the project for use, you'll first need the VM. I've included a command that works on Onyx for copying the image into this directory. I'm not including it in the submission because why? This is also the same command as provided in homework description:

```bash
cp ~jbuffenb/classes/452/pub/hw5/fedora.img .
```

Next, you'll need to first ensure you're on an onyx node, then start the VM with the following utility scripts:

```bash
./node.sh
./start.sh
```

### Copy Files and Compile/Install
Once you have the VM started and working, you can use the `copy` script to put the Scanner in the VM. Be ready with the VM's password. Once copied over, you can SSH into the VM:

```bash
./copy.sh
ssh -p 2222 cs452@localhost
```

Once in the VM, you can navigate to the Scanner directory, use the default make target to compile the module, then use the `install` make target to prepare it for use in the OS:

```bash
cd Scanner
make
make install
```

### Testing/Trying
Finally, you can test or try the module with the following make targets:

```bash
# Try out the Scanner with a CLI
make try

# Run the tests
make test
```

You can also compile the `TestScanner` program yourself and run the previous options manually:

```bash
# Try Scanner
./TestScanner

# Test Scanner
./TestScanner test
```
