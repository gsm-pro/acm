{$APPTYPE CONSOLE}
Var
  n,i:byte;
  r:array[1..7] of real;
  q,ans:real;
Procedure Rec;
var
  i,j:byte;
  t1,t2:real;
begin
  for i:=1 to n do
    for j:=i+1 to n do
      if (r[i]<>-1)and(r[j]<>-1) then begin
        t1:=r[i];
        t2:=r[j];
        r[i]:=r[i]+r[j];
        r[j]:=-1;
        if abs(q-r[i])<abs(q-ans) then ans:=r[i];
        Rec;
        r[i]:=t1;
        r[j]:=t2;
        r[i]:=r[i]*r[j]/(r[i]+r[j]);
        r[j]:=-1;
        if abs(q-r[i])<abs(q-ans) then ans:=r[i];
        Rec;
        r[i]:=t1;
        r[j]:=t2;
      end;
end;
begin
  read(n,q);
  for i:=1 to n do read(r[i]);
  ans:=r[1];
  Rec;
  write(ans:0:8);
end.