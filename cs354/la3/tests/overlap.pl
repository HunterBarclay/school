test('Overlap Before', A) :- A = overlap(
	slot(time(2, 0, am), time(4, 0, am)),
	slot(time(3, 0, am), time(6, 0, am)),
	slot(time(3, 0, am), time(4, 0, am))
).
test('Overlap Within', A) :- A = overlap(
	slot(time(4, 0, am), time(5, 0, am)),
	slot(time(3, 0, am), time(6, 0, am)),
	slot(time(4, 0, am), time(5, 0, am))
).
test('Overlap Outside', A) :- A = overlap(
	slot(time(2, 0, am), time(7, 0, am)),
	slot(time(3, 0, am), time(6, 0, am)),
	slot(time(3, 0, am), time(6, 0, am))
).
test('Overlap After', A) :- A = overlap(
	slot(time(5, 0, am), time(7, 0, am)),
	slot(time(3, 0, am), time(6, 0, am)),
	slot(time(5, 0, am), time(6, 0, am))
).

test('Overlap After INV', A) :- A = (\+ overlap(
	slot(time(5, 0, am), time(7, 0, am)),
	slot(time(3, 0, am), time(6, 0, am)),
	slot(time(5, 0, am), time(7, 0, am))
)).
test('Overlap Within INV', A) :- A = (\+ overlap(
	slot(time(4, 0, am), time(4, 0, am)),
	slot(time(3, 0, am), time(6, 0, am)),
	slot(time(4, 0, am), time(4, 0, am))
)).