#!/usr/local/apps/local/bin/gprolog --consult-file

:- include('people.pl').
:- include('uniq.pl').
:- include('util.pl').

people([ann,bob,carla]).

meet(Slot) :- people(People), meetPeople(People, Slot).

main :- findall(Slot, meet(Slot), Slots),
        uniq(Slots, Uniq), nl,
        writeSlots(Uniq, 1), nl, halt.

:- initialization(main).
