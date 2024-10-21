#!/usr/local/apps/local/bin/gprolog --consult-file

% This program shows how to "unit test" a predicate, named foo.
% The first foo fact prevents an "existence_error".
% The second foo fact models the predicate under test,
% which might evaluate to true or false, 

% :- include('people.pl').
% :- include('util.pl').



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

:- include('op.pl').
:- include('util.pl').
:- include('uniq.pl').

slotSpan(slot(time(3, 0, am), time(6, 0, am))).

slotWithin(slot(time(4, 0, am), time(5, 0, am))).
slotOutside(slot(time(2, 0, am), time(7, 0, am))).
slotAfter(slot(time(5, 0, am), time(7, 0, am))).

:- include('tests/lte.pl').
:- include('tests/gte.pl').
:- include('tests/overlap.pl').
:- include('tests/meetone.pl').
:- include('tests/meetpeople.pl').

evaluate_all([]).
evaluate_all([[Name, Result]|Rest]) :- 
	(Result, write('Pass - '), write(Name), nl, evaluate_all(Rest));
	(write('Fail - '), write(Name), nl, evaluate_all(Rest)).

main :- findall([Name, Result], test(Name, Result), Tests),
	evaluate_all(Tests), halt.

:- initialization(main).
