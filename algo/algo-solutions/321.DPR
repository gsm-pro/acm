{$APPTYPE CONSOLE}
uses math;
Var
  x1,y1,x2,y2,x,y,a,b,c:int64;
  q:boolean;
begin
  read(x,y,x1,y1,x2,y2);
  a:=y2-y1;
  b:=x1-x2;
  c:=y1*x2-x1*y2;
  q:=False;
  if (x2>=x1)and(y2>=y1)and(x>=x1)and(y>=y1) then q:=True;
  if (x2<=x1)and(y2>=y1)and(x<=x1)and(y>=y1) then q:=True;
  if (x2>=x1)and(y2<=y1)and(x>=x1)and(y<=y1) then q:=True;
  if (x2<=x1)and(y2<=y1)and(x<=x1)and(y<=y1) then q:=True;
  if (a*x+b*y+c=0)and(q) then write('YES') else write('NO');
end.