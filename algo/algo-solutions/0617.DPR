{$APPTYPE CONSOLE}
uses math;
var
  a,b,x,y,ug,x0,y0,r,x1,y1,x2,y2,l,q:extended;
begin
  read(r,x0,y0,x1,y1,x2,y2);
  x:=x1-x0;
  y:=y1-y0;
  a:=ArcTan2(y,x);
  if a<0 then a:=2*pi+a;
  x:=x2-x0;
  y:=y2-y0;
  b:=ArcTan2(y,x);
  if b<0 then b:=2*pi+b;
  ug:=0;
  if a<=b then begin
    if b-a>pi then ug:=2*pi-b+a;
    if b-a<=pi then ug:=b-a;
  end else begin
    if a-b>pi then ug:=2*pi-a+b;
    if a-b<=pi then ug:=a-b;
  end;
  ug:=180*ug/pi;
  q:=ug/360;
  l:=2*pi*r*q;
  write(l:0:5);
end.