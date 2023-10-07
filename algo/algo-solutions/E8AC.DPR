{$APPTYPE CONSOLE}
uses Math;
const
  N='.000000 ';
type
  pt=record
    x,y:int64;
  end;
Var
  i:longint;
  z:array[1..4] of pt;
  a,b,c:array[1..3] of int64;
  q:boolean;
Function OnOtr(num:int64;p:pt):boolean;
var
  n1,n2:int64;
begin
  if num=1 then begin n1:=1;n2:=2;end else begin n1:=3;n2:=4;end;
  OnOtr:=(a[num]*p.x+b[num]*p.y+c[num]=0)and
         (p.x>=min(z[n1].x,z[n2].x))and(p.x<=max(z[n1].x,z[n2].x))and
         (p.y>=min(z[n1].y,z[n2].y))and(p.y<=max(z[n1].y,z[n2].y));
end;
Function EqPts(p1,p2:pt):boolean;
begin
  EqPts:=(p1.x=p2.x)and(p1.y=p2.y);
end;
Procedure Print(p1,p2:pt);
begin
  q:=True;
  if EqPts(p1,p2) then write(p1.x,N,p1.y,N) else write(p1.x,N,p1.y,N,p2.x,N,p2.y,N);
end;
Function InIn:boolean;
begin
  if (OnOtr(1,z[3]))and(OnOtr(1,z[4])) then Print(z[3],z[4]) else
  if (OnOtr(2,z[1]))and(OnOtr(2,z[2])) then Print(z[1],z[2]) else
  if (OnOtr(2,z[2]))and(OnOtr(1,z[3])) then Print(z[3],z[2]) else
  if (OnOtr(2,z[1]))and(OnOtr(1,z[3])) then Print(z[3],z[1]) else
  if (OnOtr(1,z[4]))and(OnOtr(2,z[1])) then Print(z[4],z[1]) else
  if (OnOtr(1,z[4]))and(OnOtr(2,z[2])) then Print(z[2],z[4]);
  InIn:=q;
end;
Function IsPt(num:int64):boolean;
var
  n1,n2:int64;
begin
  if num=1 then begin n1:=1;n2:=2;end else begin n1:=3;n2:=4;end;
  IsPt:=(z[n1].x=z[n2].x)and(z[n1].y=z[n2].y);
end;
Function InterS:boolean;
var
  v1,v2,v3,v4:int64;
begin
  v1:=(z[4].x-z[3].x)*(z[1].y-z[3].y)-(z[4].y-z[3].y)*(z[1].x-z[3].x);
  v2:=(z[4].x-z[3].x)*(z[2].y-z[3].y)-(z[4].y-z[3].y)*(z[2].x-z[3].x);
  v3:=(z[2].x-z[1].x)*(z[3].y-z[1].y)-(z[2].y-z[1].y)*(z[3].x-z[1].x);
  v4:=(z[2].x-z[1].x)*(z[4].y-z[1].y)-(z[2].y-z[1].y)*(z[4].x-z[1].x);
  InterS:=(v1*v2<0)and(v3*v4<0);
end;
begin
  q:=False;
  for i:=1 to 4 do with z[i] do read(x,y);
  a[1]:=z[2].y-z[1].y;
  b[1]:=z[1].x-z[2].x;
  c[1]:=z[1].y*z[2].x-z[1].x*z[2].y;
  a[2]:=z[4].y-z[3].y;
  b[2]:=z[3].x-z[4].x;
  c[2]:=z[3].y*z[4].x-z[3].x*z[4].y;
  if (IsPt(1))and(IsPt(2))and(EqPts(z[1],z[3])) then write(z[1].x,N,z[1].y,N) else
    if InIn then else
      if (OnOtr(2,z[1]))and(not IsPt(2)) then write(z[1].x,N,z[1].y,N) else
        if (OnOtr(2,z[2]))and(not IsPt(2)) then write(z[2].x,N,z[2].y,N) else
          if (OnOtr(1,z[3]))and(not IsPt(1)) then write(z[3].x,N,z[3].y,N) else
            if (OnOtr(1,z[4]))and(not IsPt(1)) then write(z[4].x,N,z[4].y,N) else
              if InterS then write((c[2]*b[1]-c[1]*b[2])/(a[1]*b[2]-a[2]*b[1]):0:6,' ',
                                   (c[2]*a[1]-c[1]*a[2])/(b[1]*a[2]-a[1]*b[2]):0:6) else
                write('Empty');
end.