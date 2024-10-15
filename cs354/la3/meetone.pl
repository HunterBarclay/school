#!/usr/local/apps/local/bin/gprolog --consult-file

:- include('people.pl').
:- include('util.pl').

% Find all Persons such that Person can meet within 8:30am and 8:45am.
main :- findall(
		Person,
		meetone(Person,slot(time(8,30,am),time(8,45,am))),
		People
	), writePeople(People, 1), nl, halt.

:- initialization(main).
