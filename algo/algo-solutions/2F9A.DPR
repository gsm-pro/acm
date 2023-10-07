{$APPTYPE CONSOLE}
var
  a,b:array[1..100,1..100] of longint;
  i,j,n,m:longint;
begin
  read(n);
  for i:=1 to n do
    for j:=1 to n do read(a[i,j]);
  b:=a;
  for m:=1 to n do
    for i:=1 to n do
      for j:=1 to n do
        if ((b[i,j]>b[i,m]+b[m,j])or(b[i,j]=0))
        and(b[i,m]>0)and(b[m,j]>0) then b[i,j]:=b[i,m]+b[m,j];
  for i:=1 to n do begin
    for j:=1 to n do write(b[i,j],' ');
    writeln;
  end;
end.