#!/usr/local/apps/local/bin/gprolog --consult-file

% Author: James Buffenbarger, Hunter Barclay
% Date: Oct. 21st, 2024

:- include('op.pl').
:- include('uniq.pl').
:- include('util.pl').

% Standard people per the assignment details.
people([ann,bob,carla]).

% Let Slot be a time slot when all people described above can meet.
meet(Slot) :- people(People), meetPeople(People, Slot).

% Find all unique time slots where people described above can meet.
main :- findall(Slot, meet(Slot), Slots),
        uniq(Slots, Uniq), nl,
        writeSlots(Uniq, 1), nl, halt.

:- initialization(main).
