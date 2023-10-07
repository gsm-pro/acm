{$APPTYPE CONSOLE}
var
  m:array[1..100] of longint;
  t:array[0..100,-10100..10100] of boolean;
  n,i,j,x:longint;
begin
  read(n,x);
  for i:=1 to n do read(m[i]);
  for j:=-10100 to 10100 do t[0,j]:=false;
  t[0,0]:=true;
  for i:=1 to n do
    for j:=-10000 to 10000 do
      t[i,j]:=(t[i-1,j-m[i]])or(t[i-1,j+m[i]]);
  if t[n,x] then writeln('YES') else writeln('NO');
end.