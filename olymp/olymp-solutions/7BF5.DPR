{$APPTYPE CONSOLE}
uses math;
const
  INF=1000000001;
var
  n,i,k,kk,r,minv,mink,gr:longint;
  a,ans,p:array[1..20000] of longint;
Procedure QSort(l,r:longint);
var
  m,i,j,t:longint;
begin
  m:=a[(l+r) div 2];
  i:=l;
  j:=r;
  repeat
    while a[i]<m do inc(i);
    while a[j]>m do dec(j);
    if i<=j then begin
      t:=a[i];a[i]:=a[j];a[j]:=t;
      t:=p[i];p[i]:=p[j];p[j]:=t;
      inc(i);dec(j);
    end;
  until i>j;
  if j>l then QSort(l,j);
  if i<r then QSort(i,r);
end;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n,k);
  for i:=1 to 20000 do a[i]:=INF;
  for i:=1 to n do read(a[i]);
  for i:=1 to n do p[i]:=i;
  kk:=0;
  r:=0;
  repeat
    minv:=INF;
    mink:=1;
    gr:=min(2*r+2,n);
    if gr=n then break;
    for i:=1 to gr do if a[i]<=minv then begin minv:=a[i];mink:=i;end;
    a[mink]:=INF;
    if kk+minv<=k then begin
      inc(kk,minv);
      inc(r);
      ans[r]:=mink;
    end else break;
  until False;
  if 2*r+2>=n then begin
    QSort(1,n);
    for i:=1 to n do
      if kk+a[i]<=k then begin
        inc(r);
        ans[r]:=p[i];
        inc(kk,a[i]);
      end;
  end;
  writeln(r);
  for i:=1 to r do write(ans[i],' ');
end.