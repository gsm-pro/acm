{$apptype console}
uses Math;
const
  inf=maxlongint shr 1;
  nmax=160;
  dmax=30;
type
  int=longint;
  tdist=record
    v,p,b:int;
  end;
var
  n,m,ans,kl:int;
  p,b:array[0..nmax,0..nmax] of int;
  d,pr:array[0..nmax] of int;
  ds:array[0..nmax,0..nmax] of tdist;
  u:array[0..nmax] of boolean;
  r:array[0..nmax,0..nmax*dmax] of int;
procedure go(v:int);
var
  i:int;
begin
  if u[v] then exit;
  u[v]:=true;
  for i:=1 to n do
    if p[v,i]<inf then go(i);
  inc(kl);
  pr[kl]:=v;
end;
procedure update(var a:int;b:int);
begin
  if a>b then a:=b;
end;
procedure Solve;
var
  i,j,t,ii,tn,os:int;
begin
  kl:=0;
  fillchar(u,sizeof(u),0);
  go(1);
  for i:=1 to kl shr 1 do
  begin
    t:=pr[i];
    pr[i]:=pr[kl-i+1];
    pr[kl-i+1]:=t;
  end;
  for t:=1 to n do
    for i:=1 to n do
      for j:=1 to n do begin
        if p[i,j]>p[i,t]+p[t,j] then p[i,j]:=p[i,t]+p[t,j];
        if b[i,j]>b[i,t]+b[t,j] then b[i,j]:=b[i,t]+b[t,j];
      end;
  fillchar(d,sizeof(d),0);
  fillchar(ds,sizeof(ds),0);
  for i:=1 to n do
    for j:=1 to n do
      if p[i,j]<inf then begin
        inc(d[i]);
        ds[i,d[i]].v:=j;
        ds[i,d[i]].p:=p[i,j];
        ds[i,d[i]].b:=b[i,j];
      end;
  for i:=1 to n do
    for j:=0 to n*dmax do r[i,j]:=inf;
  for i:=1 to kl do
    if pr[i]=n then begin
      kl:=i;
      break;
    end;
  r[1,0]:=0;
  ans:=inf;
  for ii:=1 to kl do begin
    i:=pr[ii];
    for j:=0 to (i-1)*dmax do
      if r[i,j]<inf then begin
        for t:=1 to d[i] do
          if (j+ds[i,t].b<=ds[i,t].p) then
            update(r[ds[i,t].v,ds[i,t].p-j-ds[i,t].b],r[i,j]+j+ds[i,t].b);
        if ds[i,d[i]].v=n then
          update(ans,r[i,j]+max(j+ds[i,d[i]].b,ds[i,d[i]].p));
      end;
  end;
end;
procedure ReadData;
var
  i,j,x,y,br,pr:int;
begin
  read(n,m);
  for i:=1 to n do
    for j:=1 to n do begin
      p[i,j]:=inf;
      b[i,j]:=inf;
    end;
  for i:=1 to m do begin
    read(x,y,br,pr);
    p[x,y]:=pr;
    b[x,y]:=br;
  end;
end;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  ReadData;
  Solve;
  write(ans);
end.