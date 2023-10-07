{$APPTYPE CONSOLE}
var
  a:array[1..1000] of longint;
  i,s,n:longint;
begin
  read(n);
  s:=0;
  for i:=1 to n do begin
    read(a[i]);
    if a[i]>0 then inc(s,a[i]);
  end;
  write(s);
end.