
Const m = 7, n = 85;
Var x, y, z, q, r;

Procedure multiply;
Var a, b;
Begin
  a := x;
  b := y;
  z := 0;
  While b > 0 Do
    Begin
      If Odd b Then z := z + a;
      a := 2*a ;
      b := b/2 ;
    End
End;

Procedure divide;
Var w;
Begin
  r := x;
  q := 0;
  w := y;
  While w <= r Do
    w := 2*w ;
  While w > y Do
    Begin
      q := 2*q;
      w := w/2;
      If w <= r Then
        Begin
          r := r-w;
          q := q+1
        End
    End
End;

Procedure gcd;
Var f, g;
Begin
  f := x;
  g := y;
  While f <> g Do
    Begin
      If f < g Then g := g-f;
      If g < f Then f := f-g;
    End;
  z := f
End;

Begin
  x := m;
  y := n;
  Call multiply;
  x := 25;
  y := 3;
  Call divide;
  x := 84;
  y := 36;
  Call gcd;
End.
