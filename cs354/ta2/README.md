# Translation Assignment - 1
- Author: Hunter Barclay
- Date: Oct. 19th, 2024
- Course: CS 354

## Files
- `util` -> See (Usage)[#usage].
- `test/run` -> Provided test script. Modified a bit. See file for documentation.
- `*.java` -> Java source files that make up the interpreter and compiler. See files for further details.
- `test/test-*/` -> Test directories that contain tests focused on a specific aspect. Each of these directories
	include out files will dumps from the program, scanner, etc. as well as err files that contain dumps from
	the error stream of the program for debugging.

### Unit Testing Files
Each file name is suffixed with the program number it is referring to.

- `prg[num]` -> Test program to compile.
- `inp[num]` -> File to feed into the input stream the translated program and interpreter when running them.
- `scan[num]` -> Expected output of the scanner when scanning the `prg` file.
- `exp[num]` -> Expected output of the both the translated program and the interpreter.
- `gen[num].c` -> Translated program.
- `gen[num]` -> Compiled translated program.
- `out[num].s` -> Standard output of the scanner.
- `out[num].i` -> Standard output of the interpreter.
- `out[num].c` -> Standard output of the compiled translated program (`gen[num]`).
- `scanerrs[num]` -> Error output of the scanner. This is where relevant debugging information
	is dumped, regardless of the outcome of the scanner.
- `generrs[num]` -> Error output of the translator. This is where relevant debugging information
	is dumped, regardless of the outcome of the translator.
- `gccerrs[num]` -> Compilation erros from compiling the generated C file.

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
translator, and the scanner. By default, if a `scan[n]` file isn't specified for
the program to test against, the test will be skipped.

I've also added this feature for `exp[n]` files, in the event that I haven't updated a
given test program to the new language grammar.

I've left out a handful of tests to show this, as well as the fact that I found those particular
tests redundant at the time.

### Helpful note
Before taking a look through the tests themselves, I'd definitely recommend running clean prior.
It generates a lot of files, and it can be a mess looking through them.
