% Equals Tests
% Ensure eq can determine if two times are the same.

test('EQ 1', A) :- A = eq(time(10,0,am),time(10,0,am)).
test('EQ 2', A) :- A = eq(time(6,0,pm),time(6,0,pm)).
test('EQ 3', A) :- A = (\+ eq(time(12,0,pm),time(12,0,am))).
test('EQ 4', A) :- A = (\+ eq(time(4,15,am),time(4,16,am))).
test('EQ 5', A) :- A = (\+ eq(time(3,20,pm),time(2,20,pm))).
