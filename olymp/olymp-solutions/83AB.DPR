{$APPTYPE CONSOLE}
uses Math;
const
  INF=1000000000;
var
  a:array[1..100] of byte;
  z:array[0..21000] of longint;
  i,n,l,j:longint;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n,l);
  for i:=1 to n do read(a[i]);
  for i:=1 to 21000 do z[i]:=INF;
  for i:=1 to n do begin
    for j:=200 downto 1 do
      if z[j]<INF then z[j+a[i]]:=min(z[j+a[i]],z[j]+1);
    z[a[i]]:=1;
  end;
  while z[l]=INF do dec(l);
  write(l,#13,#10,z[l]);
end.