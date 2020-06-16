{$apptype console}
uses math;
var
  x,y:array[1..50] of extended;
  i,j,n:longint;
  mx,ang,r,xxx,yyy,xx,yy:extended;
Function Dist(x,y:extended):extended;
begin
  Dist:=Sqrt(x*x+y*y);
end;
Function Angle(x,y,x1,y1:double):extended;
var
  u1,u2,u:extended;
begin
  u1:=arctan2(y,x);
  u2:=arctan2(y1,x1);
  u1:=abs(u1-u2);
  u2:=2*pi-u1;
  if u1<u2 then u:=u1 else u:=u2;
  Angle:=u*180/PI;
end;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  for i:=1 to n do read(x[i],y[i]);
  mx:=0;
  for i:=0 to 359 do begin
    xx:=0;
    yy:=0;
    r:=100000;
    ang:=(i/180)*PI;
    xxx:=r*cos(ang);
    yyy:=r*sin(ang);
    for j:=1 to n do
      if angle(x[j],y[j],xxx,yyy)<90 then begin
        xx:=xx+x[j];
        yy:=yy+y[j];
      end;
    mx:=max(mx,dist(xx,yy));
  end;
  write(mx:0:20);
end.