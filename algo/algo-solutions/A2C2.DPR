{$APPTYPE CONSOLE}
uses math;
var
  a:array[1..1001] of longint;
  i,n,k,mid,l,r,x,maxd:longint;
Function FindKol(s:longint):longint;
var
  i,kol:longint;
begin
  kol:=0;
  for i:=1 to n do inc(kol,a[i] div s);
  FindKol:=kol;
end;
begin
  readln(n,k);
  r:=0;
  for i:=1 to n do begin
    read(a[i]);
    r:=max(r,a[i]);
  end;
  l:=1;
  maxd:=0;
  while l<=r do begin
    mid:=(l+r) shr 1;
    x:=FindKol(mid);
    if x<k then r:=mid-1;
    if x>k then l:=mid+1;
    if x=k then inc(l);
    if (x>=k)and(mid>maxd) then maxd:=mid;
  end;
  writeln(maxd);
end.