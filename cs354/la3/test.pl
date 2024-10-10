#!/usr/local/apps/local/bin/gprolog --consult-file

% This program shows how to "unit test" a predicate, named foo.
% The first foo fact prevents an "existence_error".
% The second foo fact models the predicate under test,
% which might evaluate to true or false, 

% :- include('meet.pl').
:- include('comp.pl').
:- include('util.pl').

% foo :- false.
% foo :- true.

% foo :- gte(time(11,30,am), time(11,0,am)).
% foo :- lte(time(11,30,am), time(8,30,pm)).

% foo :- gte(time(9,0,am), time(8,45,am)).

% bobFree(StartTime, EndTime) :- free(bob, slot(StartTime, EndTime)).
% foo :- bobFree(S, E), write(S), nl, write(E), nl.

% personAvail(Person, MinTime, MaxTime) :- free(Person, slot(StartTime, EndTime)),
% 									lte(StartTime, MinTime), gte(EndTime, MaxTime).
% foo :- startTime(S), endTime(E), findall(Person, personAvail(Person, S, E), People), write(People), nl.

% val(0).

% decr(A, B) :- B is A - 1.
% foo :- val(A), decr(A, ADecr), write(A), nl, write(ADecr), nl.

% pass(A, B) :- B is A.
% foo :- timeA(A), pass(A, B), write(B), nl.

% foo :- max(time(8,30,am), time(8,45,am), Min), print(Min), nl.

% slotSpan(slot(time(3, 0, am), time(6, 0, am))).

% slotBefore(slot(time(2, 0, am), time(4, 0, am))).
% slotWithin(slot(time(4, 0, am), time(5, 0, am))).
% slotOutside(slot(time(2, 0, am), time(7, 0, am))).
% slotAfter(slot(time(5, 0, am), time(7, 0, am))).

% testBefore :- write('Before: '), slotBefore(A), slotSpan(B), overlap(A, B, Out), writeSlot(Out), nl.
% testWithin :- write('Within: '), slotWithin(A), slotSpan(B), overlap(A, B, Out), writeSlot(Out), nl.
% testOutside  :- write('Outside: '), slotOutside(A), slotSpan(B), overlap(A, B, Out), writeSlot(Out), nl.
% testAfter :- write('After: '), slotAfter(A), slotSpan(B), overlap(A, B, Out), writeSlot(Out), nl.

% foo :- lt(time(8, 35, am), time(8, 36, am)).
% foo :- testBefore, testWithin, testOutside, testAfter.

foo :- overlap(
		slot(time(11,30,am), time(9,0,pm)),
		slot(time(11,0,am), time(8,30,pm)),
		Out
	), writeSlot(Out), nl.

main :- (foo,
	write('foo is true');
	write('foo is not true')),
	nl, halt.

:- initialization(main).
