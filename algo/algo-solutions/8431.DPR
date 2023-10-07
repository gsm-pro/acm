{$APPTYPE CONSOLE}
var
  t:array[-1..110,-1..110] of longint;
  i,j,n:longint;
  a,b:array[1..110] of longint;
Function Min(x,y:longint):longint;
begin
  if x<=y then Min:=x else Min:=y;
end;  
begin
  readln(n);
  for i:=1 to n do begin
    read(a[i]);
    read(b[i]);
  end;
  for i:=-1 to 110 do
    for j:=-1 to 110 do t[i,j]:=2000000000;
  t[1,1]:=a[1];
  for i:=2 to n do
    for j:=0 to n div 2 do
      t[i,j]:=Min(t[i-1,j-1]+a[i],t[i-1,j+1]+b[i]);
  write(t[n,0]);
end.