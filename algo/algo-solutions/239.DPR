{$APPTYPE CONSOLE}
var
  a,b:array[1..3000] of longint;
  z:array[0..3000,0..3000] of longint;
  i,j,n,m:longint;
begin
  readln(n,m);
  for i:=1 to n do read(a[i]);
  for j:=1 to m do read(b[j]);
  z[0,0]:=0;
  for i:=1 to n do z[i,0]:=0;
  for j:=1 to m do z[0,j]:=0;
  for i:=1 to n do
    for j:=1 to m do
      if a[i]=b[j] then z[i,j]:=z[i-1,j-1]+1
                   else
        if z[i-1,j]>=z[i,j-1] then z[i,j]:=z[i-1,j]
                              else z[i,j]:=z[i,j-1];
  write(z[n,m]);
end.