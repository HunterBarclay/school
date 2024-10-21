% Author: Hunter Barclay
% Date: Oct. 21st, 2024
% Operations for Data.
% This file was created separately incase the grader would like to hotswap the provided
% `data.pl` file for a different one.

:- include('data.pl').

% == Less than or Equal (lte) ==
% True when given TimeA and TimeB, TimeA is before or at the same
% time as TimeB. Only accounts for Hours, Minutes, and midday specifications.
% Integers only.

% Check for midday differences.
lte(time(_, _, X), time(_, _, Y)) :- X == am, Y == pm.
% Check for hour differences.
lte(time(HrA, _, X), time(HrB, _, Y)) :- \+ (X == pm, Y == am), (HrA mod 12) < (HrB mod 12).
% Check for minute differences.
lte(time(HrA, MinA, X), time(HrB, MinB, Y)) :- \+ (X == pm, Y == am), HrA == HrB, MinA =< MinB.

% == Greater than or Equal (gte) ==
% True when given TimeA and TimeB, TimeA is before or at the same
% time as TimeB. Only accounts for Hours, Minutes, and midday specifications.
% Integers only.

% Check for midday differences.
gte(time(_, _, X), time(_, _, Y)) :- X == pm, Y == am.
% Check for hour differences.
gte(time(HrA, _, X), time(HrB, _, Y)) :- \+ (X == am, Y == pm), (HrA mod 12) > (HrB mod 12).
% Check for minute differences.
gte(time(HrA, MinA, X), time(HrB, MinB, Y)) :- \+ (X == am, Y == pm), HrA == HrB, MinA >= MinB.

% == Equals (eq) ==
% True if given two times with Hr and Min A and B, and middays X and Y,
% X and Y are the same, A and B's Hr and Min are the same.
eq(time(HrA, MinA, X), time(HrB, MinB, Y)) :- X == Y, HrA == HrB, MinA == MinB.

% == Less than (lt) ==
% True if lte(TimeA, TimeB) is true, but eq(TimeA, TimeB) is not.
lt(TimeA, TimeB) :- lte(TimeA, TimeB), \+ eq(TimeA, TimeB).

% == Greater than (lt) ==
% True if gte(TimeA, TimeB) is true, but eq(TimeA, TimeB) is not.
gt(TimeA, TimeB) :- gte(TimeA, TimeB), \+ eq(TimeA, TimeB).

% == Overlap (overlap) ==
% True if given time slots A, B, and Out, each with Min and Max times,
% Out is the longest time slot that can overlap both A and B. See comments
% about each rule below and which case they cover.

% Type: Before
% B |   *------*   |
% A | *------*     |
overlap(slot(MinA, MaxA), slot(MinB, MaxB), slot(MinOut, MaxOut)) :- (\+ eq(MinA, MaxA)), (\+ eq(MinB, MaxB)),
	lt(MinA, MinB), gt(MaxA, MinB), lte(MaxA, MaxB), MinOut = MinB, MaxOut = MaxA.

% Type: Within
% B |   *------*   |
% A |     *--*     |
overlap(slot(MinA, MaxA), slot(MinB, MaxB), slot(MinOut, MaxOut)) :- (\+ eq(MinA, MaxA)), (\+ eq(MinB, MaxB)),
	gte(MinA, MinB), lte(MaxA, MaxB), MinOut = MinA, MaxOut = MaxA.

% Type: Outside
% B |   *------*   |
% A | *----------* |
overlap(slot(MinA, MaxA), slot(MinB, MaxB), slot(MinOut, MaxOut)) :- (\+ eq(MinA, MaxA)), (\+ eq(MinB, MaxB)),
	lte(MinA, MinB), gte(MaxA, MaxB), MinOut = MinB, MaxOut = MaxB.

% Type: After
% B |   *------*   |
% A |     *------* |
overlap(slot(MinA, MaxA), slot(MinB, MaxB), slot(MinOut, MaxOut)) :- (\+ eq(MinA, MaxA)), (\+ eq(MinB, MaxB)),
	gte(MinA, MinB), lt(MinA, MaxB), gte(MaxA, MaxB), MinOut = MinA, MaxOut = MaxB.

% True when given a person Person and a time slot with times
% MinTime and MaxTime, Person has a freetime slot that contains,
% the time slot from MinTime to MaxTime in it's entirety.
meetone(Person, slot(MinTime, MaxTime)) :-
    free(Person,slot(StartTime, EndTime)),
    lte(StartTime, MinTime), gte(EndTime, MaxTime).

% True when given a list of people, there exists time slot Slot
% when all individuals are available at the same time.
meetPeople([], Slot) :- Slot = slot(time(12,0,am), time(11,59,pm)).
meetPeople([Person|Rest], Slot) :- meetPeople(Rest, RestSlot),
    free(Person, PersonSlot), overlap(RestSlot, PersonSlot, Slot).
