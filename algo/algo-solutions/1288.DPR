{$APPTYPE CONSOLE}
var
  a:array[1..1000] of longint;
  i,j,n,d,max:longint;
begin
  read(n,d);
  for i:=1 to n do read(a[i]);
  for i:=d+1 to n do begin
    max:=0;
    for j:=1 to i-d do if a[j]>max then max:=a[j];
    inc(a[i],max);
  end;
  max:=0;
  for i:=1 to n do if a[i]>max then max:=a[i];
  write(max);
end.