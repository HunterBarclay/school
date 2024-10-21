% Author: Hunter Barclay
% Date: Oct. 21st, 2024
% Less Than Tests
% Ensures that lt can determine a given time A is less
% than a given time b. The definition is combination of
% lte and eq so this doesn't really need to be tested much.

test('LT 1', A) :- A = lt(time(3,0,am),time(3,1,am)).
test('LT 2', A) :- A = (\+ lt(time(3,0,am),time(3,0,am))).
