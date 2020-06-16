{$APPTYPE CONSOLE}
uses Math;
var
  n,x,i,r:longint;
  a:array[1..1001] of longint;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n,x);
  for i:=1 to n do read(a[i]);
  r:=0;
  i:=0;
  a[n+1]:=20000000;
  while r<=x do begin
    inc(r,a[i+1]);
    inc(i);
  end;
  write(i-1);
end.