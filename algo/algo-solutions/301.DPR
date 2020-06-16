{$APPTYPE CONSOLE}
uses math;
type
  pt=record
    x,y:longint;
  end;
Var
  i,n,u,ans:longint;
  z:array[1..12] of pt;
  st:array[1..12] of longint;
Function InterS(p1,p2,p3,p4:pt):boolean;
  Function Intersection(p1,p2,p3,p4:pt):boolean;
  var
    v1,v2,v3,v4,ax1,ay1,ax2,ay2,bx1,by1,bx2,by2:double;
  begin
    ax1:=p1.x;ay1:=p1.y;
    ax2:=p2.x;ay2:=p2.y;
    bx1:=p3.x;by1:=p3.y;
    bx2:=p4.x;by2:=p4.y;
    v1:=(bx2-bx1)*(ay1-by1)-(by2-by1)*(ax1-bx1);
    v2:=(bx2-bx1)*(ay2-by1)-(by2-by1)*(ax2-bx1);
    v3:=(ax2-ax1)*(by1-ay1)-(ay2-ay1)*(bx1-ax1);
    v4:=(ax2-ax1)*(by2-ay1)-(ay2-ay1)*(bx2-ax1);
    if (v1*v2<0)and(v3*v4<0) then Intersection:=True
                             else Intersection:=False;
  end;
  Function OnOtr(p,pp1,pp2:pt):boolean;
  var
    a,b,c:longint;
  begin
    a:=pp2.y-pp1.y;
    b:=pp1.x-pp2.x;
    c:=pp1.y*pp2.x-pp1.x*pp2.y;
    OnOtr:=(a*p.x+b*p.y+c=0)and
           (p.x>=min(pp1.x,pp2.x))and(p.x<=max(pp1.x,pp2.x))and
           (p.y>=min(pp1.y,pp2.y))and(p.y<=max(pp1.y,pp2.y));
  end;
begin
  if (p2.x=p3.x)and(p2.y=p3.y) then InterS:=False else
    InterS:=(InterSection(p1,p2,p3,p4))or
            (OnOtr(p1,p3,p4))or(OnOtr(p2,p3,p4))or
            (OnOtr(p3,p1,p2))or(OnOtr(p4,p1,p2));
end;
Function Mozhno(s,f:longint):boolean;
var
  i,start:longint;
begin
  if (f=1)and(u=n) then start:=2 else start:=1;
  for i:=start to u do
    if st[i]=f then begin
      Mozhno:=False;
      exit;
    end;
  for i:=start to u-2 do
    if InterS(z[st[i]],z[st[i+1]],z[s],z[f]) then begin
      Mozhno:=False;
      exit;
    end;
  Mozhno:=True;
end;
Procedure Rec(x:longint);
var
  i:longint;
begin
  if (u=n)and(Mozhno(x,1)) then begin
    inc(ans);
    exit;
  end;
  for i:=1 to n do begin
    if Mozhno(x,i) then begin
      inc(u);
      st[u]:=i;
      Rec(i);
      dec(u);
      st[u+1]:=0;
    end;
  end;
end;
begin
  read(n);
  for i:=1 to n do with z[i] do read(x,y);
  ans:=0;
  u:=1;
  st[u]:=1;
  Rec(1);
  write(ans div 2);
end.