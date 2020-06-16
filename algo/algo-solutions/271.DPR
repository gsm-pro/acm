{$APPTYPE CONSOLE}
var
  a:array[0..101,0..101] of longint;
  i,j,n,s:longint;
begin
  readln(n);
  for i:=0 to 101 do
    for j:=0 to 101 do a[i,j]:=-20000;
  for i:=1 to n do
    for j:=1 to i do read(a[i,j]);
  for i:=2 to n do
    for j:=1 to i do
      if a[i-1,j]>=a[i-1,j-1] then inc(a[i,j],a[i-1,j])
                              else inc(a[i,j],a[i-1,j-1]);
  s:=a[n,1];
  for i:=2 to n do if a[n,i]>s then s:=a[n,i];
  write(s);
end.