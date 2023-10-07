{$APPTYPE CONSOLE}
uses Math;
var
  n,i:longint;
  x,y:array[1..50] of double;
  ans_x,ans_y,h:double;
Function R(xx,yy:double):double;
var
  i:longint;
  res:double;
begin
  res:=0;
  for i:=1 to n do res:=res+sqrt((x[i]-xx)*(x[i]-xx)+(y[i]-yy)*(y[i]-yy));
  R:=res;
end;
Procedure F(h:double);
var
  xx,yy,v,v1,v2,v3,v4,v0:double;
begin
  xx:=ans_x;
  yy:=ans_y;
  repeat
    v1:=R(xx+h,yy);
    v2:=R(xx-h,yy);
    v3:=R(xx,yy+h);
    v4:=R(xx,yy-h);
    v0:=R(xx,yy);
    v:=min(min(v1,v2),min(min(v3,v4),v0));
    if v=v0 then break;
    if v=v1 then xx:=xx+h else
    if v=v2 then xx:=xx-h else
    if v=v3 then yy:=yy+h else
    if v=v4 then yy:=yy-h;
  until false;
  ans_x:=xx;
  ans_y:=yy;
end;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(n);
  for i:=1 to n do read(x[i],y[i]);
  ans_x:=0;
  ans_y:=0;
  h:=2048;
  while h>1e-4 do begin
    h:=h/2;
    F(h);
  end;
  writeln(ans_x:0:3,' ',ans_y:0:3);
end.