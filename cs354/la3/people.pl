% This is a utility class for operations on People data. The data
% can be found in the data.pl file, detailing free time slots for
% each person.

:- include('data.pl').
:- include('comp.pl').

% True when given a person Person and a time slot with times
% MinTime and MaxTime, Person has a freetime slot that contains,
% the time slot from MinTime to MaxTime in it's entirety.
meetone(Person, slot(MinTime, MaxTime)) :-
    free(Person,slot(StartTime, EndTime)),
    lte(StartTime, MinTime), gte(EndTime, MaxTime).

% True when given a list of people, there exists time slot Slot
% when all individuals are available at the same time.
meetPeople([], Slot) :- Slot = slot(time(1,0,am), time(11,59,pm)).
meetPeople([Person|Rest], Slot) :- meetPeople(Rest, RestSlot),
    free(Person, PersonSlot), overlap(RestSlot, PersonSlot, Slot).
