{$APPTYPE CONSOLE}
const
  z=0.001;
Var
  d1,d2,d3,x1,y1,x2,y2,x3,y3,a,b,c:real;
begin
  read(x1,y1,x2,y2,x3,y3);
  d1:=sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
  d2:=sqrt((x3-x1)*(x3-x1)+(y3-y1)*(y3-y1));
  d3:=sqrt((x3-x2)*(x3-x2)+(y3-y2)*(y3-y2));
  a:=(d1*d1-d2*d2-d3*d3)/(-2*d2*d3);
  b:=(d2*d2-d1*d1-d3*d3)/(-2*d1*d3);
  c:=(d3*d3-d1*d1-d2*d2)/(-2*d1*d2);
  if (abs(a)<z)or(abs(b)<z)or(abs(c)<z) then write('RIGHT') else
    if (a<0)or(b<0)or(c<0) then write('OBTUSE') else write('ACUTE');
end.