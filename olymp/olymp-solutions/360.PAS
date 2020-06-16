Var
  f,g:text;
  a:array[1..50,1..50] of longint;
  c:array[1..50] of longint;
  i,j,max,min,n,m,x:longint;
Begin
  assign(f,'input.txt');
  reset(f);
  readln(f,n,m);
  for i:=1 to n do
    for j:=1 to m do read(f,a[i,j]);
  close(f);
  for i:=1 to n do begin
    x:=2000;
    for j:=1 to m do
      if a[i,j]<x then x:=a[i,j];
    c[i]:=x;
  end;
  max:=0;
  for i:=1 to n do if c[i]>max then max:=c[i];
  for i:=1 to 50 do c[i]:=0;
  for i:=1 to m do begin
    x:=0;
    for j:=1 to n do
      if a[j,i]>x then x:=a[j,i];
    c[i]:=x;
  end;
  min:=2000;
  for i:=1 to m do if c[i]<min then min:=c[i];
  assign(g,'output.txt');
  rewrite(g);
  if min<=max then write(g,min,' ',max)
              else write(g,max,' ',min);
  close(g);
End.