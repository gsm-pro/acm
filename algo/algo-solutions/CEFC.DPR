{$APPTYPE CONSOLE}
Var
  xp,yp,xx,yy,a1,b1,c1,a2,b2,c2,x1,y1,x2,y2,x,y:extended;
begin
  read(x1,y1,x2,y2,x,y);
  a1:=y2-y1;
  b1:=x1-x2;
  c1:=y1*x2-x1*y2;
  if a1*x+b1*y+c1=0 then begin
    write('Oil field is on the frontier');
    halt(0);
  end;
  a2:=b1;
  b2:=-a1;
  c2:=-a2*x-b2*y;
  xp:=(b1*c2-b2*c1)/(a1*b2-a2*b1);
  yp:=(a1*c2-a2*c1)/(a2*b1-a1*b2);
  xx:=2*xp-x;
  yy:=2*yp-y;
  write(xx:0:8,' ',yy:0:8);
end.