# Language Assignment 3: Prolog
- Hunter Barclay
- Oct. 21st, 2024

## Files
There are three executable files in this submission:

- `meetone.pl`: Determines everyone who can meet from 8:30am to 8:45am.
- `meet.pl`: Determines all the times Ann, Bob, and Carla can meet throughout the day.
- `test.pl`: Test suite for this assignment. See [Testing](#testing) section.

The remaining files are meant to be exclusively included into an executing file:

- `data.pl`: Provided by the professor, includes the free time slots each person has.
- `op.pl`: A number of comparison and utility rules for working with the data. This includes the core rules that the `meet` and `meetone` executables use to work. They were moved here for ease of includability to the testing suite.
- `README.md`: This file.
- `uniq.pl`: Provided by the professor, filters a list to only contain unique elements.
- `util.pl`: Helpful for debugging, contains a number of print and supporting rules for getting a view of the data when I was writing this submission.
- `test/*.pl`: Tests. See [Testing](#testing) section.

## Testing
The test suite works by evaluating a number of `test` rules. A test is defined given the following format:
```prolog
test(<Test Name>, A) :- A = <Evaluable to Test>.
```

Each test is then found, evaluated, and a `Pass` or `Fail` message is printed to the console depending on the evaluation of `A`, along with the name of the test. The `test.pl` file includes any and all dependencies the tests may need, then each category of test is defined into it's unique file--located in the `tests/` directory--then subsequently included in the `test.pl` as well.
