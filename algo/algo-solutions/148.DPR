{$APPTYPE CONSOLE}
var
  z:array[1..100000] of array of longint;
  n,i,j,i1,j1,i2,j2,i3,j3:longint;
  k:array[1..100000] of longint;
begin
  read(n);
  for i:=1 to n do begin
    read(k[i]);
    Setlength(z[i],k[i]+1);
    for j:=1 to k[i] do read(z[i,j]);
  end;
  read(j);
  for i:=1 to j do begin
    read(i1,j1,i2,j2,i3,j3);
    z[i1,j1]:=(z[i2,j2]+z[i3,j3]) mod 1000000;
  end;
  for i:=1 to n do begin
    for j:=1 to k[i] do write(z[i,j],' ');
    writeln;
  end;
end.