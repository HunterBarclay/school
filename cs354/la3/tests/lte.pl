% Less than or Equal to Tests
% Ensure LTE is determined correctly.

test('LTE 1', A) :- A = lte(time(12,30,am), time(1,15,am)).
test('LTE 2', A) :- A = lte(time(8,0,am), time(1,0,pm)).
test('LTE 3', A) :- A = lte(time(3,30,pm), time(3,31,pm)).
test('LTE 4', A) :- A = lte(time(12,30,am), time(12,30,am)).
test('LTE 5', A) :- A = (\+ lte(time(12,31,am), time(12,30,am))).
test('LTE 6', A) :- A = (\+ lte(time(12,31,pm), time(12,30,am))).
test('LTE 7', A) :- A = (\+ lte(time(1,31,am), time(12,30,am))).
