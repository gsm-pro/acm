{$APPTYPE CONSOLE}
const
  a:array[1..8] of longint=(1,21,267,1718,5250,7980,5880,1680);
var
  i,n,res,min:longint;
Function Coh(n,m:longint):longint;
var
  c,r,i:longint;
begin
  c:=1;
  if n-m>m then r:=n-m else r:=m;
  for i:=1 to n-r do c:=c*(i+r)div i;
  Coh:=c;
end;
begin
  res:=0;
  read(n);
  if n<8 then min:=n else min:=8;
  for i:=1 to min do inc(res,Coh(n,i)*a[i]);
  write(res);
end.