#!/usr/local/apps/local/bin/gprolog --consult-file

% Author: Hunter Barclay
% Date: Oct. 21st, 2024
% Testing Suite
% This testing suite matches all testing rules, evaluates their second parameter,
% then prints to the console accordingly.

:- include('op.pl').
:- include('util.pl').
:- include('uniq.pl').

slotSpan(slot(time(3, 0, am), time(6, 0, am))).

slotWithin(slot(time(4, 0, am), time(5, 0, am))).
slotOutside(slot(time(2, 0, am), time(7, 0, am))).
slotAfter(slot(time(5, 0, am), time(7, 0, am))).

:- include('tests/lte.pl').
:- include('tests/gte.pl').
:- include('tests/eq.pl').
:- include('tests/lt.pl').
:- include('tests/gt.pl').
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
