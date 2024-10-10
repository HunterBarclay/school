lte(time(_, _, X), time(_, _, Y)) :- X == am, Y == pm.
lte(time(HrA, _, X), time(HrB, _, Y)) :- \+ (X == pm, Y == am), HrA < HrB.
lte(time(HrA, MinA, X), time(HrB, MinB, Y)) :- \+ (X == pm, Y == am), HrA == HrB, MinA =< MinB.

gte(time(_, _, X), time(_, _, Y)) :- X == pm, Y == am.
gte(time(HrA, _, X), time(HrB, _, Y)) :- \+ (X == am, Y == pm), HrA > HrB.
gte(time(HrA, MinA, X), time(HrB, MinB, Y)) :- \+ (X == am, Y == pm), HrA == HrB, MinA >= MinB.

eq(time(HrA, MinA, X), time(HrB, MinB, Y)) :- X == Y, HrA == HrB, MinA == MinB.

lt(TimeA, TimeB) :- lte(TimeA, TimeB), \+ eq(TimeA, TimeB).
gt(TimeA, TimeB) :- gte(TimeA, TimeB), \+ eq(TimeA, TimeB).

min(A, B, Min) :- lte(A, B), Min = A; Min = B.
max(A, B, Max) :- gte(A, B), Max = A; Max = B.

% Type: Before
% B |   *------*   |
% A | *------*     |
overlap(slot(MinA, MaxA), slot(MinB, MaxB), slot(MinOut, MaxOut)) :-
	lt(MinA, MinB), gt(MaxA, MinB), lte(MaxA, MaxB), MinOut = MinB, MaxOut = MaxA.

% Type: Within
% B |   *------*   |
% A |     *--*     |
overlap(slot(MinA, MaxA), slot(MinB, MaxB), slot(MinOut, MaxOut)) :-
	gte(MinA, MinB), lte(MaxA, MaxB), MinOut = MinA, MaxOut = MaxA.

% Type: Outside
% B |   *------*   |
% A | *----------* |
overlap(slot(MinA, MaxA), slot(MinB, MaxB), slot(MinOut, MaxOut)) :-
	lte(MinA, MinB), gte(MaxA, MaxB), MinOut = MinB, MaxOut = MaxB.

% Type: After
% B |   *------*   |
% A |     *------* |
overlap(slot(MinA, MaxA), slot(MinB, MaxB), slot(MinOut, MaxOut)) :-
	gte(MinA, MinB), lt(MinA, MaxB), gte(MaxA, MaxB), MinOut = MinA, MaxOut = MaxB.
