{$APPTYPE CONSOLE}
uses math;
const
  INF=1000000;
var
  a:array[1..21] of longint = (1,2,3,4,5,6,7,8,9,16,25,36,49,64,81,27,125,216,343,512,729);
  l:array[1..21] of longint = (1,1,1,1,1,1,1,1,1, 3, 3, 3, 3, 3, 3, 3,  3,  3,  3,  3,  3);
  z:array[1..20000] of longint;
  n,i,j:longint;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  for i:=1 to 20000 do z[i]:=INF;
  for i:=1 to 21 do begin
    z[a[i]]:=l[i];
    for j:=1 to 15000 do
      if z[j]<INF then z[j+a[i]]:=min(z[j+a[i]],z[j]+l[i]+1);
  end;
  write(z[n]);
end.