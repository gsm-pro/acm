{$APPTYPE CONSOLE}
uses math;
type
  pt=record
    x,y:extended;
  end;
var
  n,i,k,m,min,j:longint;
  x,y,zx,zy:array[1..51] of extended;
  a_,b_:array[1..51] of pt;
  z1x,z1y,z2x,z2y,s,ss,s1,s2,a,b,c,a1,b1,c1,dx,dy:extended;
Function Vect(a1,a2,b1,b2:pt):extended;
begin
  Vect:=(a2.x-a1.x)*(b2.y-b1.y)-(b2.x-b1.x)*(a2.y-a1.y);
end;
Function Dist2(a1,a2:pt):extended;
begin
  Dist2:=sqr(a2.x-a1.x)+sqr(a2.y-a1.y);
end;
function InterS(x1,y1,x2,y2,x3,y3,x4,y4:extended):boolean;
var
  v1,v2,v3,v4:extended;
begin
  v1:=(x4-x3)*(y1-y3)-(y4-y3)*(x1-x3);
  v2:=(x4-x3)*(y2-y3)-(y4-y3)*(x2-x3);
  v3:=(x2-x1)*(y3-y1)-(y2-y1)*(x3-x1);
  v4:=(x2-x1)*(y4-y1)-(y2-y1)*(x4-x1);
  InterS:=(v1*v2<0)and(v3*v4<0);
end;
begin
  read(n);
  for i:=1 to n do read(x[i],y[i]);
  read(z1x,z1y,z2x,z2y);
  a:=z2y-z1y;
  b:=z1x-z2x;
  c:=-a*z1x-b*z1y;
  if b=0 then begin
    z1y:=-100000;
    z2y:=100000;
  end else begin
    z1x:=-100000;
    z1y:=(-a*z1x-c)/b;
    z2x:=100000;
    z2y:=(-a*z2x-c)/b;
  end;
  s:=0;
  x[n+1]:=x[1];
  y[n+1]:=y[1];
  for i:=1 to n do s:=s+(x[i+1]-x[i])*(y[i+1]+y[i])/2;
  s:=abs(s);
  k:=0;
  for i:=1 to n do
    if InterS(x[i],y[i],x[i+1],y[i+1],z1x,z1y,z2x,z2y) then begin
      inc(k);
      a1:=y[i+1]-y[i];
      b1:=x[i]-x[i+1];
      c1:=-a1*x[i]-b1*y[i];
      zx[k]:=(c1*b-c*b1)/(a*b1-a1*b);
      zy[k]:=(c1*a-c*a1)/(b*a1-a*b1);
    end;
  for i:=1 to n do
    if a*x[i]+b*y[i]+c>=0 then begin
      inc(k);
      zx[k]:=x[i];
      zy[k]:=y[i];
    end;
  for i:=1 to k do begin a_[i].x:=zx[i];a_[i].y:=zy[i];end;
  n:=k;
  m:=1;
  for i:=2 to n do
    if a_[i].y<a_[m].y then m:=i else
      if (a_[i].y=a_[m].y)and(a_[i].x>a_[m].x) then m:=i;
  b_[1]:=a_[m];
  a_[m]:=a_[1];
  a_[1]:=b_[1];
  k:=1;
  min:=2;
  repeat
    for j:=2 to n do
      if (vect(b_[k],a_[min],b_[k],a_[j])<0)or
        ((vect(b_[k],a_[min],b_[k],a_[j])=0)and
        (dist2(b_[k],a_[min])<dist2(b_[k],a_[j])))
        then min:=j;
    inc(k);
    b_[k]:=a_[min];
    min:=1;
  until (b_[k].x=b_[1].x)and(b_[k].y=b_[1].y);
  ss:=0;
  for i:=1 to k-1 do ss:=ss+(b_[i+1].x-b_[i].x)*(b_[i+1].y+b_[i].y)/2;
  ss:=abs(ss);
  s1:=ss;
  s2:=s-ss;
  if s1<s2 then write(s2:0:7,' ',s1:0:7)
           else write(s1:0:7,' ',s2:0:7);
end.