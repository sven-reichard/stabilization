# Strassen algorithm for matrix products

product := function(a, b)
    local  M1, M2, M3, M4, M5, M6, M7, c;
    M1 := (a[1][1] + a[2][2]) * (b[1][1] + b[2][2]);
    M2 := (a[2][1] + a[2][2]) * b[1][1];
    M3 := a[1][1] * (b[1][2] - b[2][2]);
    M4 := a[2][2] * (b[2][1] - b[1][1]);
    M5 := (a[1][1] + a[1][2]) * b[2][2];
    M6 := (a[2][1] - a[1][1]) * (b[1][1] + b[1][2] );
    M7 := (a[1][2] - a[2][2]) * (b[2][1] + b[2][2] );
    
    c := [[],[]];
    c[1][1] := M1 + M4 - M5 + M7 ;
    c[1][2] := M3 + M5;
    c[2][1] := M2 + M4;
    c[2][2] := M1-M2 + M3 + M6;
    return c;
end;
