# Language Assignment 5: Awk
- Hunter Barclay
- CS 354
- Dec. 2nd, 2024

## Files
- `README.md` -> This file.
- `BldgPrmtsPublic10-01-2017To10-15-2017.xlsx` -> Original Excel spread sheet.
- `BldgPrmtsPublic10-01-2017To10-15-2017.csv` -> CSV format of the housing data.
- `gen.awk` -> Executable awk file that will generate an html file from a csv file.

## How to use
To generate the html file, execute the following command:
```bash
$ ./gen.awk BldgPrmtsPublic10-01-2017To10-15-2017.csv > out.html
```

Alternatively, you can manually execute awk from wherever it is on your system:
```bash
$ /bin/awk -f gen.awk BldgPrmtsPublic10-01-2017To10-15-2017.csv > out.html
```

The file `out.html` will contain a web page with a table containing the csv data.
