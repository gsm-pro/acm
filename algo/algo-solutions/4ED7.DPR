{$APPTYPE CONSOLE}
uses math;
Const
  eps=0.00001;
Var
  x1,y1,x2,y2,x,y:longint;
  d,p1,p2,p3,s:double;
begin
  readln(x,y,x1,y1,x2,y2);
  p1:=sqrt(Sqr(x1-x2)+Sqr(y1-y2));
  p2:=sqrt(Sqr(x1-x)+Sqr(y1-y));
  p3:=sqrt(Sqr(x2-x)+Sqr(y2-y));
  if p1=0 then write(p2:0:9) else begin
    s:=0.5*abs((x1-x)*(y2-y)-(x2-x)*(y1-y));
    d:=(2*s)/p1;
    if (abs(sqrt(abs(p2*p2-d*d))+sqrt(abs(p3*p3-d*d))-p1)>eps) then d:=min(p2,p3);
    write(d:0:10);
  end;
end.