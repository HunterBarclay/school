# Translation Assignment - 1
- Author: Hunter Barclay
- Date: Oct. 3rd, 2024
- Course: CS 354

## Files
- util -> See (Usage)[#usage].
- test/run -> Provided test script. Modified a bit. See file for documentation.
- *.java -> Java source files that make up the interpreter and compiler. See files for further details.
- test/test-*/ -> Test directories that contain tests focused on a specific aspect. Each of these directories
	include out files will dumps from the program, scanner, etc. as well as err files that contain dumps from
	the error stream of the program for debugging.
- test/test-*/prg[n] -> Program to test.
- test/test-*/scan[n] -> Expected scanner out from the program.
- test/test-*/gen -> Expected output of the interpreter/program from all programs.
- test/test-*/inp -> Optional input parameters to compilation.

## Usage
In addition to the `test/run` script working as it did when provided, I've also
included `util` to provided control beyond just running unit tests. `util` has
the following usage:

```
./util <build|test|clean>

	COMMAND		DESCRIPTION
	build		Build the java program.
	test		Runs the unit tests for the translator/interpreter/scanner.
				This is simply an alias for `test/run`, with additional checks
				to ensure the program is compiled beforehand.
	clean		Removes all compiled and generated files. Will only remove
				generated C code if it was stored in a file with the following
				pattern: "gen.*".
```

## Testing
To run the unit tests, use the following commands:

```bash
# This first command is optional.
./util build

./util test
```

As stated in [usage](#usage), this will run unit tests for the interpreter,
translator, and the scanner. By default, if a scan[n] file isn't specified for
the program to test against, the test will be skipped. I intentionally left
out multiplier scanner tests to show this, but added scan tests for everything else.

