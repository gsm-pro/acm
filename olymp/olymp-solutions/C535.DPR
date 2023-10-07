{$apptype console}
const
  MAXN=20002;
type
  ttown=record
    x,y,i,nx,ny,c:longint;
  end;
var
  i,n,v,cx,cy:longint;
  x,y,ccx,ccy:array [1..MAXN] of longint;
  t:array[1..MAXN] of ttown;
procedure qsort(l,r,tp:longint);
var
  i,j,x:longint;
  z:ttown;
begin
  i:=l;
  j:=r;
  x:=0;
  if tp=1 then x:=t[l+random(r-l)].x;
  if tp=2 then x:=t[l+random(r-l)].y;
  if tp=3 then x:=t[l+random(r-l)].i;
  while (i<=j) do begin
    if tp=1 then begin
      while (x>t[i].x) do inc(i);
      while (x<t[j].x) do dec(j);
    end;
    if tp=2 then begin
      while (x>t[i].y) do inc(i);
      while (x<t[j].y) do dec(j);
    end;
    if tp=3 then begin
      while (x>t[i].i) do inc(i);
      while (x<t[j].i) do dec(j);
    end;
    if (i<=j) then begin
      z:=t[i];
      t[i]:=t[j];
      t[j]:=z;
      inc(i);
      dec(j);
    end;
  end;
  if (l<j) then qsort(l,j,tp);
  if (r>i) then qsort(i,r,tp);
end;
procedure findy(v:longint);forward;
procedure findx(v:longint);
begin
  while (x[v]<>0)and(t[x[v]].c<>0) do x[v]:=t[x[v]].nx;
  if x[v]<>0 then begin
    t[x[v]].c:=1;
    dec(ccx[v]);
    dec(ccy[t[x[v]].y]);
    findy(t[x[v]].y);
  end;
end;
procedure findy(v:longint);
begin    
  while (y[v]<>0)and(t[y[v]].c<>0) do y[v]:=t[y[v]].ny;
  if y[v]<>0 then begin
    t[y[v]].c:=2;
    dec(ccy[v]);
    dec(ccx[t[y[v]].x]);
    findx(t[y[v]].x);
  end;
end;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(n);
  for i:=1 to n do begin
    read(t[i].x,t[i].y);
    t[i].i:=i;
    t[i].c:=0;
  end;
  qsort(1,n,1);
  cx:=0;
  v:=-maxlongint;
  for i:=1 to n do begin
    if v<>t[i].x then begin
      v:=t[i].x;
      inc(cx);
      x[cx]:=0;
    end;
    t[i].x:=cx;
    t[i].nx:=x[cx];
    x[cx]:=t[i].i;
    inc(ccx[cx]);
  end;
  qsort(1,n,2);
  v:=-maxlongint;
  cy:=0;
  for i:=1 to n do begin
    if v<>t[i].y then begin
      v:=t[i].y;
      inc(cy);
      y[cy]:=0;
    end;
    t[i].y:=cy;
    t[i].ny:=y[cy];
    y[cy]:=t[i].i;
    inc(ccy[cy]);
  end;
  qsort(1,n,3);
  for i:=1 to cx do
    if ccx[i] mod 2=1 then findx(i);
  for i:=1 to cy do
    if ccy[i] mod 2=1 then findy(i);
  for i:=1 to cx do
    while (x[i]<>0) do findx(i);
  for i:=1 to cy do
    if y[i]<>0 then findy(i);
  for i:=1 to n do
    writeln(t[i].c-1,' ');
end.