# Translation Assignment - 1
- Author: Hunter Barclay
- Date: Oct. 3rd, 2024
- Course: CS 354

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
translator, and the scanner.

