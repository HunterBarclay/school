incr(A, B) :- B is A + 1.
decr(A, B) :- B is A - 1.

writeTime(time(Hr, Min, T)) :-
    write(Hr), write(':'), write(Min), write(T).

writeSlot(slot(From, To)) :-
    writeTime(From), write(' - '), writeTime(To).

writeSlots([], _).
writeSlots([H|T], Index) :- write(Index), write(': '), writeSlot(H), nl, incr(Index, NextIndex), writeSlots(T, NextIndex).
