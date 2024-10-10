#!/usr/local/apps/local/bin/gprolog --consult-file

:- include('data.pl').
:- include('comp.pl').

% Person can meet within MinTime and MaxTime inclusive iff
% 	Person has a free time with StartTime and EndTime such that,
%   StartTime is less than or equal to MinTime and
%	EndTime is greater than or equal to MaxTime.
meetone(Person, slot(MinTime, MaxTime)) :- free(Person,slot(StartTime, EndTime)),
                                    lte(StartTime, MinTime), gte(EndTime, MaxTime).

% Find all Persons such that Person can meet within 8:30am and 8:45am.
main :- findall(Person,
		meetone(Person,slot(time(8,30,am),time(8,45,am))),
		People),
	write(People), nl, halt.

:- initialization(main).
