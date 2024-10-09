#!/usr/local/apps/local/bin/gprolog --consult-file

% This program shows how to "unit test" a predicate, named foo.
% The first foo fact prevents an "existence_error".
% The second foo fact models the predicate under test,
% which might evaluate to true or false, 

:- include('meet.pl').

% foo :- false.
% foo :- true.

% foo :- lte(time(8,0,am), time(8,30,am)).
% foo :- gte(time(9,0,am), time(8,45,am)).

% bobFree(StartTime, EndTime) :- free(bob, slot(StartTime, EndTime)).
% foo :- bobFree(S, E), write(S), nl, write(E), nl.

% personAvail(Person, MinTime, MaxTime) :- free(Person, slot(StartTime, EndTime)),
% 									lte(StartTime, MinTime), gte(EndTime, MaxTime).
% foo :- startTime(S), endTime(E), findall(Person, personAvail(Person, S, E), People), write(People), nl.

main :- (foo,
	 write('foo is true');
	 write('foo is not true')),
	nl, halt.

:- initialization(main).
