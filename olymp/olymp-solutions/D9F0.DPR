{$APPTYPE CONSOLE}
uses Math;
var
  x,y:array[1..600] of longint;
  a,b,c,h:array[0..200000] of int64;
  i,j,k,n,d,maxd,t:longint;
Function GCD(a,b:longint):longint;
begin
  if a mod b=0 then GCD:=b else GCD:=GCD(b,a mod b);
end;
Procedure QSort(l,r:longint);
var
  m,i,j,t:longint;
begin
  m:=h[(l+r) div 2];
  i:=l;
  j:=r;
  repeat
    while h[i]<m do inc(i);
    while h[j]>m do dec(j);
    if i<=j then begin
      t:=h[i];h[i]:=h[j];h[j]:=t;
      inc(i);dec(j);
    end;
  until i>j;
  if j>l then QSort(l,j);
  if i<r then QSort(i,r);
end;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  if n<3 then begin
    write(n);
    halt(0);
  end;
  for i:=1 to n do read(x[i],y[i]);
  k:=0;
  for i:=1 to n-1 do
    for j:=i+1 to n do begin
      inc(k);
      a[k]:=y[j]-y[i];
      b[k]:=x[i]-x[j];
      if b[k]<>0 then d:=GCD(a[k],b[k]) else d:=a[k];
      a[k]:=a[k] div d;
      b[k]:=b[k] div d;
      c[k]:=-a[k]*x[i]-b[k]*y[i];
      h[k]:=1023*a[k]+501*b[k]+97*c[k];
    end;
  QSort(1,k);
  maxd:=1;
  t:=0;
  for i:=1 to k do
    if h[i-1]=h[i] then begin
      inc(t);
      maxd:=max(maxd,t);
    end else t:=1;
  write(trunc(sqrt(2*maxd))+1);
end.