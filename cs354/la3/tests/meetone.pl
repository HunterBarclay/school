% Meet One Tests
% Ensure that you can find everyone that is available within given time slots.

test('Meetone 8:30am - 8:45am', A) :- A = findall(
    Person,
    meetone(Person,slot(time(8,30,am),time(8,45,am))),
    [ann,carla,dave]
).

test('Meetone 6:00pm - 6:15pm', A) :- A = findall(
    Person,
    meetone(Person,slot(time(6,0,pm),time(6,15,pm))),
    [bob,carla]
).
