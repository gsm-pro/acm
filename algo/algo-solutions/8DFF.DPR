{$APPTYPE CONSOLE}
uses Math;
type
  pt=record
    x,y:int64;
  end;
Var
  i:longint;
  z:array[1..4] of pt;
  d1,d2,d3,d4,d:double;
Function InterS:boolean;
var
  v1,v2,v3,v4:int64;
begin
  v1:=(z[4].x-z[3].x)*(z[1].y-z[3].y)-(z[4].y-z[3].y)*(z[1].x-z[3].x);
  v2:=(z[4].x-z[3].x)*(z[2].y-z[3].y)-(z[4].y-z[3].y)*(z[2].x-z[3].x);
  v3:=(z[2].x-z[1].x)*(z[3].y-z[1].y)-(z[2].y-z[1].y)*(z[3].x-z[1].x);
  v4:=(z[2].x-z[1].x)*(z[4].y-z[1].y)-(z[2].y-z[1].y)*(z[4].x-z[1].x);
  InterS:=(v1*v2<0)and(v3*v4<0);
end;
Function Dist(x1,y1,x2,y2,x,y:double):double;
var
  p1,p2,p3,d,s:double;
begin
  p1:=sqrt(Sqr(x1-x2)+Sqr(y1-y2));
  p2:=sqrt(Sqr(x1-x)+Sqr(y1-y));
  p3:=sqrt(Sqr(x2-x)+Sqr(y2-y));
  if p1=0 then Dist:=p2 else begin
    s:=0.5*abs((x1-x)*(y2-y)-(x2-x)*(y1-y));
    d:=(2*s)/p1;
    if (abs(sqrt(abs(p2*p2-d*d))+sqrt(abs(p3*p3-d*d))-p1)>1e-6) then d:=min(p2,p3);
    Dist:=d;
  end;
end;
begin
  for i:=1 to 4 do with z[i] do read(x,y);
  if InterS then write(0) else begin
    d1:=Dist(z[1].x,z[1].y,z[2].x,z[2].y,z[3].x,z[3].y);
    d2:=Dist(z[1].x,z[1].y,z[2].x,z[2].y,z[4].x,z[4].y);
    d3:=Dist(z[3].x,z[3].y,z[4].x,z[4].y,z[1].x,z[1].y);
    d4:=Dist(z[3].x,z[3].y,z[4].x,z[4].y,z[2].x,z[2].y);
    d:=min(min(d1,d2),min(d3,d4));
    write(d:0:12);
  end;
end.