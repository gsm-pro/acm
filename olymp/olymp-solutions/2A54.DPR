{$APPTYPE CONSOLE}
Var
  f,g:text;
  n,x0,min,max,i,p:longint;
  x:array[1..200] of longint;
Begin
  assign(f,'input.txt');
  reset(f);
  read(f,n,x0);
  max:=0;
  min:=200000;
  for i:=1 to n do begin
    read(f,x[i]);
    if (x[i]<min) then min:=x[i];
    if (x[i]>max) then max:=x[i];
  end;
  close(f);
  if x0>=max then p:=x0-min;
  if x0<=min then p:=max-x0;
  if (x0<max)and(x0>min) then
    if x0-min<=max-x0 then p:=x0-min+max-min
                      else p:=max-x0+max-min;
  assign(g,'output.txt');
  rewrite(g);
  writeln(g,p);
  close(g);
end.