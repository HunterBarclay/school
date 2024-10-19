% Utility for Data.
% This file provides printing functionality for testing/presentation purposes.

% True given A, B, where B is A + 1.
incr(A, B) :- B is A + 1.
% True given A, B, where B is A - 1.
decr(A, B) :- B is A - 1.

% Print a time clause out in a more readable way.
writeTime(time(Hr, Min, T)) :-
    write(Hr), write(':'), write(Min), write(T).

% Print a time slot clause out in a more readable way.
writeSlot(slot(From, To)) :-
    writeTime(From), write(' - '), writeTime(To).

% Print a list of slots, with a starting index that will increment
% and be prefixed to each line.
writeSlots([], _).
writeSlots([H|T], Index) :- write(Index), write(': '), writeSlot(H), nl, incr(Index, NextIndex), writeSlots(T, NextIndex).

% Print a list of people, with a starting index that will increment
% and be prefixed to each line.
writePeople([], _).
writePeople([H|T], Index) :- write(Index), write(': '), write(H), nl, incr(Index, NextIndex), writePeople(T, NextIndex).
