{$APPTYPE CONSOLE}
type
  pt=record
    x,y:longint;
  end;
Var
  z:array[1..1000] of pt;
  i,n,p,f,maxl,j:longint;
  b:array[1..1000] of longint;
Function Dost(z1,z2:pt):boolean;
begin
  Dost:=(z1.x<z2.x)and(z1.y>z2.y);
end;
Procedure Sort(l,r,k:longint);
var
  i,j:longint;
  t:pt;
begin
  if k=1 then
    for i:=l to r-1 do
      for j:=l to r-1 do
        if z[j].y<z[j+1].y then begin
          t:=z[j];
          z[j]:=z[j+1];
          z[j+1]:=t;
        end;
  if k=2 then
    for i:=l to r-1 do
      for j:=l to r-1 do
        if z[j].x>z[j+1].x then begin
          t:=z[j];
          z[j]:=z[j+1];
          z[j+1]:=t;
        end;
end;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  for i:=1 to n do read(z[i].x,z[i].y);
  Sort(2,n-1,1);
  f:=2;
  p:=2;
  repeat
    while z[f].y=z[p].y do inc(p);
    dec(p);
    if p>f then Sort(f,p,2);
    inc(p);
    f:=p;
  until p>=n;
  for i:=2 to n do begin
    if not Dost(z[1],z[i]) then continue;
    maxl:=0;
    for j:=2 to i-1 do
      if (Dost(z[j],z[i]))and(b[j]>=maxl) then maxl:=b[j];
    b[i]:=maxl+1;
  end;
  if b[n]<1 then write('No way') else write(b[n]-1);
end.