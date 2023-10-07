{$APPTYPE CONSOLE}
uses Math;
type
  pt=record
    x,y:double;
  end;
Var
  t:double;
  i,j,k,l,kol,ans:byte;
  h:array[0..50] of double;
  w:array[1..50] of pt;
  z:array[1..6] of pt;
Procedure CalcCommon(x1,x2,x3,x4:pt);
  var
    q:boolean;
    a,b,c:array[1..2] of double;
  Procedure AddToW(c1,c2:double);
  begin
    inc(kol);
    w[kol].x:=c1;
    w[kol].y:=c2;
  end;
  Function OnOtr(num:byte;p:pt):boolean;
  var
    n1,n2:pt;
  begin
    if num=1 then begin n1:=x1;n2:=x2;end else begin n1:=x3;n2:=x4;end;
    OnOtr:=(a[num]*p.x+b[num]*p.y+c[num]=0)and
           (p.x>=min(n1.x,n2.x))and(p.x<=max(n1.x,n2.x))and
           (p.y>=min(n1.y,n2.y))and(p.y<=max(n1.y,n2.y));
  end;
  Procedure Decide(p1,p2:pt);
  begin
    q:=True;
    if (p1.x=p2.x)and(p1.y=p2.y) then AddToW(p1.x,p1.y) else begin
      write(-1);
      halt(0);
    end;
  end;
  Function InIn:boolean;
  begin
    q:=False;
    if (OnOtr(1,x3))and(OnOtr(1,x4)) then Decide(x3,x4) else
    if (OnOtr(2,x1))and(OnOtr(2,x2)) then Decide(x1,x2) else
    if (OnOtr(2,x2))and(OnOtr(1,x3)) then Decide(x3,x2) else
    if (OnOtr(2,x1))and(OnOtr(1,x3)) then Decide(x3,x1) else
    if (OnOtr(1,x4))and(OnOtr(2,x1)) then Decide(x4,x1) else
    if (OnOtr(1,x4))and(OnOtr(2,x2)) then Decide(x2,x4);
    InIn:=q;
  end;
  Function InterS:boolean;
  var
    v1,v2,v3,v4:double;
  begin
    v1:=(x4.x-x3.x)*(x1.y-x3.y)-(x4.y-x3.y)*(x1.x-x3.x);
    v2:=(x4.x-x3.x)*(x2.y-x3.y)-(x4.y-x3.y)*(x2.x-x3.x);
    v3:=(x2.x-x1.x)*(x3.y-x1.y)-(x2.y-x1.y)*(x3.x-x1.x);
    v4:=(x2.x-x1.x)*(x4.y-x1.y)-(x2.y-x1.y)*(x4.x-x1.x);
    InterS:=(v1*v2<0)and(v3*v4<0);
  end;
  begin
  a[1]:=x2.y-x1.y;
  b[1]:=x1.x-x2.x;
  c[1]:=x1.y*x2.x-x1.x*x2.y;
  a[2]:=x4.y-x3.y;
  b[2]:=x3.x-x4.x;
  c[2]:=x3.y*x4.x-x3.x*x4.y;
  if InIn then else
    if InterS then AddToW((c[2]*b[1]-c[1]*b[2])/(a[1]*b[2]-a[2]*b[1]),
                          (c[2]*a[1]-c[1]*a[2])/(b[1]*a[2]-a[1]*b[2])) else
      if OnOtr(2,x1) then AddToW(x1.x,x1.y) else
        if OnOtr(2,x2) then AddToW(x2.x,x2.y) else
          if OnOtr(1,x3) then AddToW(x3.x,x3.y) else
            if OnOtr(1,x4) then AddToW(x4.x,x4.y);
end;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  kol:=0;
  for i:=1 to 6 do with z[i] do read(x,y);
  for i:=1 to 2 do
    for j:=i+1 to 3 do
      for k:=4 to 5 do
        for l:=k+1 to 6 do CalcCommon(z[i],z[j],z[k],z[l]);
  for i:=1 to kol do h[i]:=15259*w[i].x+w[i].y;
  for i:=1 to kol-1 do
    for j:=1 to kol-1 do
      if h[j]>h[j+1] then begin
        t:=h[j];
        h[j]:=h[j+1];
        h[j+1]:=t;
      end;
  ans:=0;
  h[0]:=sqrt(13);
  for i:=1 to kol do if abs(h[i-1]-h[i])>0.001 then inc(ans);
  write(ans);
end.