{$APPTYPE CONSOLE}
uses math;
const
  eps=0.00001;
type
  pt=record
    x,y:extended;
  end;
Var
  i:longint;
  z,h:array[1..4] of pt;
  d1,d2,d3,d4,d,dx,dy:extended;
Function InterS:boolean;
var
  v1,v2,v3,v4:extended;
begin
  v1:=(z[4].x-z[3].x)*(z[1].y-z[3].y)-(z[4].y-z[3].y)*(z[1].x-z[3].x);
  v2:=(z[4].x-z[3].x)*(z[2].y-z[3].y)-(z[4].y-z[3].y)*(z[2].x-z[3].x);
  v3:=(z[2].x-z[1].x)*(z[3].y-z[1].y)-(z[2].y-z[1].y)*(z[3].x-z[1].x);
  v4:=(z[2].x-z[1].x)*(z[4].y-z[1].y)-(z[2].y-z[1].y)*(z[4].x-z[1].x);
  InterS:=(v1*v2<0)and(v3*v4<0);
end;
Function Dist(x1,y1,x2,y2,x,y:extended):extended;
var
  p1,p2,p3,d,s:extended;
begin
  p1:=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
  p2:=sqrt((x1-x)*(x1-x)+(y1-y)*(y1-y));
  p3:=sqrt((x2-x)*(x2-x)+(y2-y)*(y2-y));
  s:=0.5*abs((x1-x)*(y2-y)-(x2-x)*(y1-y));
  d:=(2*s)/p1;
  if (abs(sqrt(abs(p2*p2-d*d))+sqrt(abs(p3*p3-d*d))-p1)>eps) then d:=min(p2,p3);
  result:=d;
end;
begin
  for i:=1 to 4 do with h[i] do read(x,y);
  dx:=h[2].x-h[1].x;
  dy:=h[2].y-h[1].y;
  h[2].x:=h[1].x+100000*dx;
  h[2].y:=h[1].y+100000*dy;
  dx:=h[4].x-h[3].x;
  dy:=h[4].y-h[3].y;
  h[4].x:=h[3].x+100000*dx;
  h[4].y:=h[3].y+100000*dy;
  z:=h;
  if InterS then write(0) else begin
    d1:=Dist(z[1].x,z[1].y,z[2].x,z[2].y,z[3].x,z[3].y);
    d2:=Dist(z[1].x,z[1].y,z[2].x,z[2].y,z[4].x,z[4].y);
    d3:=Dist(z[3].x,z[3].y,z[4].x,z[4].y,z[1].x,z[1].y);
    d4:=Dist(z[3].x,z[3].y,z[4].x,z[4].y,z[2].x,z[2].y);
    d:=min(min(d1,d2),min(d3,d4));
    write(d:0:6);
  end;
end.