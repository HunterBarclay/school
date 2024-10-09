lte(time(HrA, MinA, X), time(HrB, MinB, Y)) :- \+ (X == pm, Y == am), HrA < HrB.
lte(time(HrA, MinA, X), time(HrB, MinB, Y)) :- \+ (X == pm, Y == am), HrA == HrB, MinA =< MinB.

gte(time(HrA, MinA, X), time(HrB, MinB, Y)) :- \+ (X == am, Y == pm), HrA > HrB.
gte(time(HrA, MinA, X), time(HrB, MinB, Y)) :- \+ (X == am, Y == pm), HrA == HrB, MinA >= MinB.
