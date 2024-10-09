#!/usr/local/apps/local/bin/gprolog --consult-file

:- include('data.pl').
:- include('comp.pl').

meetone(Person, slot(MinTime, MaxTime)) :- free(Person,slot(StartTime, EndTime)),
                                    lte(StartTime, MinTime), gte(EndTime, MaxTime).

main :- findall(Person,
		meetone(Person,slot(time(8,30,am),time(8,45,am))),
		People),
	write(People), nl, halt.

:- initialization(main).
