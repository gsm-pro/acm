{$APPTYPE CONSOLE}
var
  a:array[1..3] of longint;
  i,j,t:longint;
begin
  read(a[1],a[2],a[3]);
  for i:=1 to 2 do
    for j:=1 to 2 do
      if a[j]>a[j+1] then begin
        t:=a[j];
        a[j]:=a[j+1];
        a[j+1]:=t;
      end;
  writeln(a[2]);
end.