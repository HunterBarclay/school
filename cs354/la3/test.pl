#!/usr/local/apps/local/bin/gprolog --consult-file

% Author: Hunter Barclay
% Date: Oct. 21st, 2024
% Testing Suite
% This testing suite matches all testing rules, evaluates their second parameter,
% then prints to the console accordingly.

:- include('op.pl').
:- include('util.pl').
:- include('uniq.pl').

:- include('tests/lte.pl').
:- include('tests/gte.pl').
:- include('tests/eq.pl').
:- include('tests/lt.pl').
:- include('tests/gt.pl').
:- include('tests/overlap.pl').
:- include('tests/meetone.pl').
:- include('tests/meetpeople.pl').

% Evaluate all test rules.
evaluate_all([]).
evaluate_all([[Name, Result]|Rest]) :- 
	(Result, write('Pass - '), write(Name), nl, evaluate_all(Rest));
	(write('Fail - '), write(Name), nl, evaluate_all(Rest)).

% Find all test rules and evalute them.
main :- findall([Name, Result], test(Name, Result), Tests),
	evaluate_all(Tests), halt.

:- initialization(main).
