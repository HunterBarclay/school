#!/usr/local/apps/local/bin/gprolog --consult-file

:- include('data.pl').
:- include('uniq.pl').
:- include('comp.pl').
:- include('util.pl').

people([ann,bob,carla]).
% people([dave,carla,bob]).
% people([carla,bob]).

% stepone -> Determine if two time slots overlap, then output a slot showing the overlap.
% meetPeople([Person|Rest], Slot) :- 

meetPeople([], Slot) :- Slot = slot(time(1,0,am), time(11,59,pm)).
meetPeople([Person|Rest], Slot) :- meetPeople(Rest, RestSlot), free(Person, PersonSlot), overlap(RestSlot, PersonSlot, Slot).

meet(Slot) :- people(People), meetPeople(People, Slot).

% meet(Slot) :- free(ann, AnnSlot), free(bob, BobSlot), free(carla, CarlaSlot),
%     overlap(AnnSlot, BobSlot, AnnBobSlot), overlap(CarlaSlot, AnnBobSlot, Slot).

% meet(Slot) :- free(bob, BobSlot), free(carla, CarlaSlot),
%     write('Bob: '), writeSlot(BobSlot), nl,
%     write('Carla: '), writeSlot(CarlaSlot), nl,
%     overlap(BobSlot, CarlaSlot, Slot), write('Found!'), nl.

main :- findall(Slot, meet(Slot), Slots),
        uniq(Slots, Uniq), nl,
        writeSlots(Uniq, 1), nl, halt.

:- initialization(main).
