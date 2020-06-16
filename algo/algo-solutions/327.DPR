{$APPTYPE CONSOLE}
uses math;
var
  x,y,x0,y0,r:longint;
  q,d:double;
begin
  read(x0,y0,r,x,y);
  q:=sqrt((x-x0)*(x-x0)+(y-y0)*(y-y0));
  if r=q then write(0) else
    if r>q then write(r-q)
      else write(q-r);
end.