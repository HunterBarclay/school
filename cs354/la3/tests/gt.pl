% Greater Than Tests
% Ensures that gt can determine a given time A is greater
% than a given time b. The definition is combination of
% gte and eq so this doesn't really need to be tested much.

test('GT 1', A) :- A = gt(time(3,1,am),time(3,0,am)).
test('GT 2', A) :- A = (\+ gt(time(3,0,am),time(3,0,am))).
