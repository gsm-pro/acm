{$APPTYPE CONSOLE}
uses math;
var
  x,y:array[1..1000] of longint;
  i,j,n,m,time,mx,t:longint;
Function InterSect(a,b,c,d:longint):boolean;
var
  z:boolean;
begin
  z:=True;
  if max(a,b)<min(c,d) then z:=False;
  if max(c,d)<min(a,b) then z:=False;
  InterSect:=z;
end;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(n,m);
  for i:=1 to n do begin
    read(x[i],y[i]);
    y[i]:=x[i]+y[i];
  end;
  time:=1;
  mx:=0;
  for i:=1 to n do begin
    t:=0;
    for j:=1 to n do if InterSect(x[i],x[i]+m,x[j],y[j]) then inc(t);
    if t>mx then begin mx:=t;time:=x[i];end;
  end;
  for i:=1 to n do begin
    t:=0;
    for j:=1 to n do if InterSect(y[i],y[i]+m,x[j],y[j]) then inc(t);
    if t>mx then begin mx:=t;time:=y[i];end;
  end;
  write(time);
end.