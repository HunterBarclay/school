test('GTE 1', A) :- A = gte(time(1,15,am), time(12,30,am)).
test('GTE 2', A) :- A = gte(time(1,0,pm), time(8,0,am)).
test('GTE 3', A) :- A = gte(time(3,31,pm), time(3,30,pm)).
test('GTE 4', A) :- A = gte(time(12,30,am), time(12,30,am)).
test('GTE 5', A) :- A = (\+ gte(time(12,30,am), time(12,31,am))).
test('GTE 6', A) :- A = (\+ gte(time(12,30,am), time(12,31,pm))).
test('GTE 7', A) :- A = (\+ gte(time(12,30,am), time(1,31,am))).
