#!/usr/local/apps/local/bin/gprolog --consult-file

:- include('data.pl').
:- include('uniq.pl').

% Code goes here apparently.

people([ann,bob,carla]).

main :- findall(Slot, meet(Slot), Slots),
        uniq(Slots, Uniq),
        write(Uniq), nl, halt.

:- initialization(main).
