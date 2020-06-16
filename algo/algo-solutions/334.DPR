{$APPTYPE CONSOLE}
Var
  i,n:longint;
  s:double;
  x,y:array[1..100001] of longint;
begin
  read(n);
  s:=0;
  for i:=1 to n do read(x[i],y[i]);
  x[n+1]:=x[1];y[n+1]:=y[1];
  for i:=1 to n do s:=s+(x[i+1]-x[i])*(y[i+1]+y[i])/2;
  write(abs(s):0:9);
end.