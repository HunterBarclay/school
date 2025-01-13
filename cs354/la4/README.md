# Language Assignment 4: Golang
- Hunter Barclay
- CS354: LA4
- Nov. 13th, 2024

## Deliverables
Using the util command, you can build and run both the go and java project. The go project
was originally made to match it's java counterpart one for one, but now has a modified accrue
method that makes use of go routines and prints out the amount that has accrued.

To run the java project, use the following commands:
```bash
$ ./util java build
$ ./util java run
```

To run the go project, use the following commands:
```bash
$ ./util go build
$ ./util go run
```

## Files
- `README.md`: This file
- `util`: Executable bash script for compiling and running the different projects.
- `bin/`: Directory to store compiled files. Makes cleaning way easier.
- `java/`: Directory for java project files.
- `java/*.java`: Java source files provided by the professor.
- `go/`: Directory for the go project files.
- `go/go.mod`: Go module file for connecting the main executable file with the accompanying source files.
- `go/main/`: Main go executable directory.
- `go/main/main.go`: Go executable source.
- `go/lib/`: Go library directory. Contains all the source utilized by the executable.
- `go/lib/*.go`: Go library source files.

## Cleanup
You can delete the bin directory, or run `$ ./util clean`, which does the same thing.