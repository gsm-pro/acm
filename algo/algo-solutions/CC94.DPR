{$APPTYPE CONSOLE}
Var
  a1,b1,c1,a2,b2,c2,a3,b3,c3:longint;
  d1,d2,d3,x1,y1,x2,y2,x3,y3:double;
begin
  read(a1,b1,c1,a2,b2,c2,a3,b3,c3);
  x1:=(b1*c2-b2*c1)/(a1*b2-a2*b1);
  y1:=(a1*c2-a2*c1)/(a2*b1-a1*b2);
  x2:=(b2*c3-b3*c2)/(a2*b3-a3*b2);
  y2:=(a2*c3-a3*c2)/(a3*b2-a2*b3);
  x3:=(b1*c3-b3*c1)/(a1*b3-a3*b1);
  y3:=(a1*c3-a3*c1)/(a3*b1-a1*b3);
  d1:=sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
  d2:=sqrt((x3-x1)*(x3-x1)+(y3-y1)*(y3-y1));
  d3:=sqrt((x3-x2)*(x3-x2)+(y3-y2)*(y3-y2));
  write((d1+d2+d3):0:3);
end.