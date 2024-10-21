% Author: Hunter Barclay
% Date: Oct. 21st, 2024
% Meet People Tests
% Test to ensure the unique overlaps in peoples schedules are found.

test('Meet People [ann, bob, carla]', A) :- A = findall(
    Slot,
    meetPeople([ann,bob,carla], Slot),
    [
        slot(time(8,0,am), time(8,30,am)),
        slot(time(8,0,am), time(8,30,am)),
        slot(time(10,0,am), time(10,15,am)),
        slot(time(10,0,am), time(10,15,am)),
        slot(time(8,0,pm), time(8,30,pm))
    ]
).

test('Meet People [ann, bob]', A) :- A = (findall(
    Slot,
    meetPeople([ann,bob], Slot),
    Slots
), uniq(Slots, [
    slot(time(8,0,am), time(8,30,am)),
    slot(time(10,0,am), time(11,0,am)),
    slot(time(8,0,pm), time(9,0,pm))
])).

test('Meet People [ann, carla]', A) :- A = (findall(
    Slot,
    meetPeople([ann,carla], Slot),
    Slots
), uniq(Slots, [
    slot(time(8,0,am), time(9,0,am)),
    slot(time(10,0,am), time(10,15,am)),
    slot(time(8,0,pm), time(8,30,pm))
])).

test('Meet People [ann, dave]', A) :- A = (findall(
    Slot,
    meetPeople([ann,dave], Slot),
    Slots
), uniq(Slots, [
    slot(time(8,0,am), time(9,0,am)),
    slot(time(10,0,am), time(11,0,am))
])).

test('Meet People [ann, ed]', A) :- A = (findall(
    Slot,
    meetPeople([ann,ed], Slot),
    Slots
), uniq(Slots, [])).

test('Meet People [bob, carla]', A) :- A = (findall(
    Slot,
    meetPeople([bob,carla], Slot),
    Slots
), uniq(Slots, [
    slot(time(8,0,am), time(8,30,am)),
    slot(time(10,0,am), time(10,15,am)),
    slot(time(11,30,am), time(8,30,pm))
])).

test('Meet People [bob, dave]', A) :- A = (findall(
    Slot,
    meetPeople([bob,dave], Slot),
    Slots
), uniq(Slots, [
    slot(time(8,0,am), time(8,30,am)),
    slot(time(10,0,am), time(11,0,am))
])).

test('Meet People [bob, ed]', A) :- A = (findall(
    Slot,
    meetPeople([bob,ed], Slot),
    Slots
), uniq(Slots, [])).

test('Meet People [carla, dave]', A) :- A = (findall(
    Slot,
    meetPeople([carla,dave], Slot),
    Slots
), uniq(Slots, [
    slot(time(8,0,am), time(9,0,am)),
    slot(time(10,0,am), time(10,15,am))
])).

test('Meet People [carla, ed]', A) :- A = (findall(
    Slot,
    meetPeople([carla,ed], Slot),
    Slots
), uniq(Slots, [])).

test('Meet People [dave, ed]', A) :- A = (findall(
    Slot,
    meetPeople([dave,ed], Slot),
    Slots
), uniq(Slots, [])).
