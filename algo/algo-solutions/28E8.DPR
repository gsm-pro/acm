{$APPTYPE CONSOLE}
uses math;
Var
  x1,y1,x2,y2,x,y,a,b,c:int64;
begin
  read(x,y,x1,y1,x2,y2);
  a:=y2-y1;
  b:=x1-x2;
  c:=y1*x2-x1*y2;
  if (a*x+b*y+c=0)and
     (x>=min(x1,x2))and(x<=max(x1,x2))and
     (y>=min(y1,y2))and(y<=max(y1,y2))
      then write('YES') else write('NO');
end.