#!/usr/local/apps/local/bin/gprolog --consult-file

% Author: James Buffenbarger, Hunter Barclay
% Date: Oct. 21st, 2024

:- include('op.pl').
:- include('uniq.pl').
:- include('util.pl').

people([ann,bob,carla]).

meet(Slot) :- people(People), meetPeople(People, Slot).

main :- findall(Slot, meet(Slot), Slots),
        uniq(Slots, Uniq), nl,
        writeSlots(Uniq, 1), nl, halt.

:- initialization(main).
