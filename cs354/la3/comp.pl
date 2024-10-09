lteSect(X, Y) :- \+ (X == pm, Y == am).
gteSect(X, Y) :- \+ (X == am, Y == pm).

lte(time(HrA, MinA, X), time(HrB, MinB, Y)) :- lteSect(X, Y),
    (
        (HrA < HrB);
        (HrA == HrB, MinA =< MinB)    
    ).

gte(time(HrA, MinA, X), time(HrB, MinB, Y)) :- gteSect(X, Y),
    (
        (HrA > HrB);
        (HrA == HrB, MinA >= MinB)    
    ).
