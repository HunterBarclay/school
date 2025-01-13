#!/bin/awk -f

BEGIN {
    print "<head><title>TITLE</title></head><body><h1>Housing Data</h1><table>"
    print "<tr>"
    print "<th>Date</th>"
    print "<th>Subdivison Name</th>"
    print "<th>Lot</th>"
    print "<th>Block</th>"
    print "<th>Value ($)</th>"
    print "</tr>"
}

NR > 1 {
    patsplit($0, entries, "([^,]|(\"[^\"]+\"))*")

    row[1] = entries[1]
    row[2] = entries[5]
    row[3] = entries[6]
    row[4] = entries[7]
    row[5] = entries[8]

    print "<tr>"
    for (i in row) {
        print "<td>"
        print gensub(/\"/, "", "g", row[i])
        print "</td>"
    }
    print "</tr>"
}

END {
    print "</table></body></html>"
}
