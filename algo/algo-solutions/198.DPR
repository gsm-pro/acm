{$apptype console}
const
  INF=maxlongint div 2;
  NMAX=100002;
type
  int=longint;
  TRect=record
    x1,y1,x2,y2,w:int;
  end;
  Point=record
    x,y,num,ok:int;
  end;
  Answer=record
    x:int64;
    p:int;
  end;
var
  a:array[1..NMAX] of TRect;
  b,c,invc:array [0..NMAX] of int;
  p:array[1..2*NMAX] of Point;
  d:array[1..4*NMAX] of Answer;
  res:array[0..NMAX] of Answer;
  prev:array[1..NMAX] of int;
  n,shift,ansi,i:int;
  ans:Answer;

Procedure WrAns(i:int);
begin
  if i=0 then exit;
  WrAns(res[i].p);
  write(i,' ');
end;

Procedure Swap(var q,w:int);
var
  tmp:int;
begin
  tmp:=q;
  q:=w;
  w:=tmp;
end;

Procedure SortB(l,r:int);
var
  i,j,x:int;
begin
  i:=l;
  j:=r;
  x:=a[b[(l+r) div 2]].x1;
  repeat
    while a[b[i]].x1<x do inc(i);
    while x<a[b[j]].x1 do dec(j);
    if i<=j then begin
      Swap(b[i],b[j]);
      inc(i);
      dec(j);
    end;
  until i>j;
  if l<j then SortB(l,j);
  if i<r then SortB(i,r);
end;

Procedure SortC(l,r:int);
var
  i,j,x,y:int;
begin
  i:=l;
  j:=r;
  y:=a[c[(l+r) div 2]].y2;
  x:=a[c[(l+r) div 2]].x2;
  repeat
    while (a[c[i]].y2>y)or((a[c[i]].y2=y)and(a[c[i]].x2<x)) do inc(i);
    while (y>a[c[j]].y2)or((a[c[j]].y2=y)and(x<a[c[j]].x2)) do dec(j);
    if i<=j then begin
      Swap(c[i],c[j]);
      inc(i);
      dec(j);
    end;
  until i>j;
  if l<j then SortC(l,j);
  if i<r then SortC(i,r);
end;

Procedure SwapP(var q,w:Point);
var
  tmp:Point;
begin
  tmp:=q;
  q:=w;
  w:=tmp;
end;

Procedure SortP1(l,r:int);
var
  i,j,x,y,ok:int;
begin
  i:=l;
  j:=r;
  x:=p[(l+r) div 2].x;
  y:=p[(l+r) div 2].y;
  ok:=p[(l+r) div 2].ok;
  repeat
    while (p[i].y>y)or((p[i].y=y)and((p[i].ok<ok)or((p[i].ok=ok) and (p[i].x<x)))) do inc(i);
    while (y>p[j].y)or((y=p[j].y)and((ok<p[j].ok)or((ok=p[j].ok) and (x<p[j].x)))) do dec(j);
    if i<=j then begin
      SwapP(p[i],p[j]);
      inc(i);
      dec(j);
    end;
  until i>j;
  if l<j then SortP1(l,j);
  if i<r then SortP1(i,r);
end;

Procedure SortP2(l,r:int);
var
  i,j,x,ok:int;
begin
  i:=l;
  j:=r;
  x:=p[(l+r) div 2].x;
  ok:=p[(l+r) div 2].ok;
  repeat
    while (p[i].x<x)or((p[i].x=x)and(p[i].ok<ok)) do inc(i);
    while (x<p[j].x)or((x=p[j].x)and(ok<p[j].ok)) do dec(j);
    if i<=j then begin
      SwapP(p[i],p[j]);
      inc(i);
      dec(j);
    end;
  until i>j;
  if l<j then SortP2(l,j);
  if i<r then SortP2(i,r);
end;

Procedure Update(x:int);
begin
  x:=x+shift;
  while x>1 do begin
    x:=x div 2;
    if d[2*x].x>d[2*x+1].x then d[x]:=d[2*x]
                           else d[x]:=d[2*x+1];
  end;
end;

Function Rmq(l,r:int):Answer;
var
  lval,rval:Answer;
begin
  if r=0 then begin
    lval.x:=0;
    lval.p:=0;
    Rmq:=lval;
    exit;
  end;
  inc(l,shift);
  inc(r,shift);
  lval:=d[l];
  rval:=d[r];
  while r<>l+1 do begin
    if not odd(l)and(d[l+1].x>lval.x) then lval:=d[l+1];
    if odd(r) and (d[r-1].x>rval.x) then rval:=d[r-1];
    l:=l div 2;
    r:=r div 2;
  end;
  if lval.x>rval.x then Rmq:=lval
                   else Rmq:=rval;
end;

Procedure Solve;
var
  i,up,ptr:int;
begin
  for i:=1 to n do begin
    b[i]:=i;
    c[i]:=i;
  end;
  SortB(1,n);
  SortC(1,n);
  for i:=1 to n do invc[c[i]]:=i;
  for i:=1 to n do begin
    p[i].num:=i;
    p[i].x:=a[i].x1;
    p[i].y:=a[i].y1;
    p[i].ok:=1;
    p[i+n].num:=i;
    p[i+n].x:=a[i].x2;
    p[i+n].y:=a[i].y2;
    p[i+n].ok:=2;
  end;
  SortP1(1,2*n);
  up:=0;
  for i:=1 to 2*n do
    if p[i].ok=2 then up:=p[i].num
                 else prev[p[i].num]:=up;
  SortP2(1,2*n);
  shift:=1;
  while shift<n+1 do shift:=2*shift;
  ptr:=1;
  p[2*n+1].x:=INF;
  for i:=1 to n do begin
    while p[ptr].x<a[b[i]].x1 do begin
      if p[ptr].ok=2 then begin
        d[invc[p[ptr].num]+shift]:=res[p[ptr].num];
        d[invc[p[ptr].num]+shift].p:=p[ptr].num;
        Update(invc[p[ptr].num]);
      end;
      inc(ptr);
    end;
    res[b[i]]:=Rmq(0,invc[prev[b[i]]]);
    inc(res[b[i]].x,a[b[i]].w);
  end;
  ans.x:=0;
  for i:=1 to n do
    if res[i].x>ans.x then begin
      ans:=res[i];
      ansi:=i;
    end;
end;

begin
  read(n);
  for i:=1 to n do read(a[i].x1,a[i].y2,a[i].x2,a[i].y1,a[i].w);
  Solve;
  writeln(ans.x);
  WrAns(ansi);
end.