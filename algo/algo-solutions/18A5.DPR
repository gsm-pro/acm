{$APPTYPE CONSOLE}
uses Math;
Var
  x3,y3,x1,y1,x2,y2:longint;
  d,s,r:double;
begin
  read(x3,y3,x1,y1,x2,y2);
  s:=0.5*abs((x2-x1)*(y3-y1)-(x3-x1)*(y2-y1));
  r:=sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
  d:=2*s/r;
  write(d:0:10);
end.