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


:- include('people.pl').
:- include('util.pl').

slotSpan(slot(time(3, 0, am), time(6, 0, am))).
slotBefore(slot(time(2, 0, am), time(4, 0, am))).
slotWithin(slot(time(4, 0, am), time(5, 0, am))).
slotOutside(slot(time(2, 0, am), time(7, 0, am))).
slotAfter(slot(time(5, 0, am), time(7, 0, am))).

% test('LTE 1', A) :- A = lte(time(12,30,am), time(1,15,am)).
% test('LTE 2', A) :- A = lte(time(8,0,am), time(1,0,pm)).
% test('LTE 3', A) :- A = lte(time(3,30,pm), time(3,31,pm)).
% test('LTE 4', A) :- A = lte(time(12,30,am), time(12,30,am)).
% test('LTE 5', A) :- A = (\+ lte(time(12,31,am), time(12,30,am))).
% test('LTE 6', A) :- A = (\+ lte(time(12,31,pm), time(12,30,am))).
% test('LTE 7', A) :- A = (\+ lte(time(1,31,am), time(12,30,am))).

% test('GTE 1', A) :- A = gte(time(1,15,am), time(12,30,am)).
% test('GTE 2', A) :- A = gte(time(1,0,pm), time(8,0,am)).
% test('GTE 3', A) :- A = gte(time(3,31,pm), time(3,30,pm)).
% test('GTE 4', A) :- A = gte(time(12,30,am), time(12,30,am)).
% test('GTE 5', A) :- A = (\+ gte(time(12,30,am), time(12,31,am))).
% test('GTE 6', A) :- A = (\+ gte(time(12,30,am), time(12,31,pm))).
test('GTE 7', A) :- A = eval(\+ gte(time(12,30,am), time(1,31,am))).

% testMin1 :- min(time(8,0,am), time(10,0,am), Min), Min = time(8,0,am).

% test('Min 1', A) :- A = testMin1.

testBefore :- slotBefore(A), slotSpan(B), overlap(A, B, Out), Out = slot(time(3,0,am),time(4,0,am)).
testWithin :- slotWithin(A), slotSpan(B), overlap(A, B, Out), Out = slot(time(4,0,am),time(5,0,am)).
testOutside :- slotOutside(A), slotSpan(B), overlap(A, B, Out), Out = slot(time(3,0,am),time(6,0,am)).
testAfter :- slotAfter(A), slotSpan(B), overlap(A, B, Out), Out = slot(time(5,0,am),time(6,0,am)).

% I'm going to find Alain Colmerauer and make him explain this utter nonsense. If
% I just write out the rule for testBefore inline, prolog segfaults, but if I
% make it it's own rule, then it works perfect. What in the actual --------.
test('Overlap Before', A) :- A = eval(testBefore).
test('Overlap Within', A) :- A = eval(testWithin).
% test('Overlap Outside', A) :- A = testOutside.
% test('Overlap After', A) :- A = testAfter.

evaluate_all([]).
evaluate_all([[Name, Result]|Rest]) :- 
	(Result, write('Pass - '), write(Name), nl, evaluate_all(Rest));
	(write('Fail - '), write(Name), nl, evaluate_all(Rest)).

main :- findall([Name, Result], test(Name, Result), Tests),
	evaluate_all(Tests), halt.

:- initialization(main).
