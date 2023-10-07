{$APPTYPE CONSOLE}
uses Math;
var
  n,m,i,j,kol:longint;
  a:array[0..101,0..101] of longint;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n,m);
  for i:=1 to n do
    for j:=1 to m do read(a[i,j]);
  for i:=1 to n do
    for j:=1 to m do
      if a[i,j]=1 then begin
        if (a[i-1,j]=1)and(a[i,j+1]=1) then inc(kol);
        if (a[i-1,j]=1)and(a[i,j-1]=1) then inc(kol);
        if (a[i,j+1]=1)and(a[i+1,j]=1) then inc(kol);
        if (a[i,j-1]=1)and(a[i+1,j]=1) then inc(kol);
      end;
  write(kol);
end.