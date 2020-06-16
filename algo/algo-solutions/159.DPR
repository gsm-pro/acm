{$APPTYPE CONSOLE}
Const
  eps=0.0001;
Var
  x1,y1,z1,x2,y2,z2,x,y,z:longint;
  d,p1,p2,p3,s,p:double;
Function Min(a,b:double):double;
begin
  if a<b then Min:=a else Min:=b;
end;
begin
  readln(x1,y1,z1,x2,y2,z2,x,y,z);
  p1:=sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2));
  p2:=sqrt((x1-x)*(x1-x)+(y1-y)*(y1-y)+(z1-z)*(z1-z));
  p3:=sqrt((x2-x)*(x2-x)+(y2-y)*(y2-y)+(z2-z)*(z2-z));
  p:=(p1+p2+p3)/2;
  s:=sqrt(p*(p-p1)*(p-p2)*(p-p3));
  d:=(2*s)/p1;
  if (abs(sqrt(abs(p2*p2-d*d))+sqrt(abs(p3*p3-d*d))-p1)>eps) then d:=min(p2,p3);
  write(d:0:6);
end.