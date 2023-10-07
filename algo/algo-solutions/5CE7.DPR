{$APPTYPE CONSOLE}
uses math;
var
  i,n,kol:longint;
  x,y:array[1..100001] of double;
  tx,ty:array[1..2] of double;
  q:boolean;
function InterS(x1,y1,x2,y2,x3,y3,x4,y4:double):boolean;
var
  v1,v2,v3,v4:double;
begin
  v1:=(x4-x3)*(y1-y3)-(y4-y3)*(x1-x3);
  v2:=(x4-x3)*(y2-y3)-(y4-y3)*(x2-x3);
  v3:=(x2-x1)*(y3-y1)-(y2-y1)*(x3-x1);
  v4:=(x2-x1)*(y4-y1)-(y2-y1)*(x4-x1);
  InterS:=(v1*v2<0)and(v3*v4<0);
end;
function OnOtr(x1,y1,x2,y2,x,y:double):boolean;
var
  a,b,c:double;
begin
  a:=y2-y1;
  b:=x1-x2;
  c:=y1*x2-x1*y2;
  OnOtr:=(a*x+b*y+c=0)and
         (x>=min(x1,x2))and(x<=max(x1,x2))and
         (y>=min(y1,y2))and(y<=max(y1,y2));
end;
begin
  read(n);
  for i:=1 to n do read(x[i],y[i]);
  x[n+1]:=x[1];
  y[n+1]:=y[1];
  read(tx[1],ty[1]);
  randomize;
  tx[2]:=100013+random(1000013);
  randomize;
  ty[2]:=100013+random(1000013);
  q:=False;
  for i:=1 to n do if OnOtr(x[i],y[i],x[i+1],y[i+1],tx[1],ty[1]) then q:=q or True;
  if q then begin
    write('YES');
    halt(0);
  end;
  kol:=0;
  for i:=1 to n do
    if InterS(x[i],y[i],x[i+1],y[i+1],tx[1],ty[1],tx[2],ty[2]) then inc(kol);
  if odd(kol) then write('YES') else write('NO');
end.