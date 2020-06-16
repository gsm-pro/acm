{$APPTYPE CONSOLE}
uses Math;
var
  a:array[1..1000] of longint;
  i,n,mx:longint;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  mx:=0;
  for i:=1 to n do begin
    read(a[i]);
    mx:=max(mx,a[i]);
  end;
  for i:=1 to n do write(mx-a[i],' ');
end.