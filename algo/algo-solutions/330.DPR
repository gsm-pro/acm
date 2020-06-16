{$APPTYPE CONSOLE}
uses math;
const
  eps=1e-5;
type
  point=record
    x,y:double;
  end;
  circle=record
    c:point;
    r:double;
  end;
Function Eq(x,y:double):boolean;
begin
  Eq:=abs(x-y)<eps;
end;
Function EqPoints(p1,p2:point):boolean;
begin
  EqPoints:=(Eq(p1.x,p2.x))and(Eq(p1.y,p2.y));
end;
Function PolarAngle(p:point):double;
var
  x:double;
begin
  x:=arctan2(p.y,p.x)*180/pi;
  x:=x+360*ord(x<0);
  PolarAngle:=x*pi/180;
end;
Function RotateCcw(p:point;alf:double):point;
var
  t:point;
begin
  t.x:=p.x*cos(alf)-p.y*sin(alf);
  t.y:=p.x*sin(alf)+p.y*cos(alf);
  RotateCcw:=t;
end;
Function Dist(p1,p2:point):double;
begin
  Dist:=hypot(p1.x-p2.x,p1.y-p2.y);
end;
Function CrossCircle(a1,a2:circle;var res1:point;var res2:point):longint;
var
  d,alf:double;
  shift:point;
begin
  d:=Dist(a1.c,a2.c);
  if (d-eps>a1.r+a2.r) then begin
    CrossCircle:=0;exit;
  end;
  if max(a1.r,a2.r)-eps>min(a1.r,a2.r)+d then begin
    CrossCircle:=0;exit;
  end;
  if Eq(d,0) then begin
    CrossCircle:=-1;exit;
  end;
  shift:=a1.c;
  a1.c.x:=a1.c.x-shift.x;
  a1.c.y:=a1.c.y-shift.y;
  a2.c.x:=a2.c.x-shift.x;
  a2.c.y:=a2.c.y-shift.y;
  alf:=PolarAngle(a2.c);
  res1.x:=(a1.r*a1.r-a2.r*a2.r+d*d)/2/d;
  res2.x:=(a1.r*a1.r-a2.r*a2.r+d*d)/2/d;
  res1.y:=-sqrt(a1.r*a1.r-res1.x*res1.x);
  res2.y:=sqrt(a1.r*a1.r-res2.x*res2.x);
  res1:=RotateCcw(res1,alf);
  res2:=RotateCcw(res2,alf);
  res1.x:=res1.x+shift.x;
  res1.y:=res1.y+shift.y;
  res2.x:=res2.x+shift.x;
  res2.y:=res2.y+shift.y;
  if EqPoints(res1,res2) then CrossCircle:=1
                         else CrossCircle:=2;
end;
var
  c1,c2:circle;
  a1,a2:point;
  d,rr:double;
  k:longint;
begin
  read(c1.c.x,c1.c.y,c1.r,c2.c.x,c2.c.y);
  d:=Dist(c1.c,c2.c);
  rr:=sqr(d)-sqr(c1.r);
  if rr<0 then begin
    write(0);
    halt(0);
  end;
  c2.r:=sqrt(rr);
  k:=CrossCircle(c1,c2,a1,a2);
  writeln(k);
  writeln(a1.x:0:5,' ',a1.y:0:5);
  if k>1 then writeln(a2.x:0:5,' ',a2.y:0:5);
end.