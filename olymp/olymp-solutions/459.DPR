{$APPTYPE CONSOLE}
uses Math;
const
  INF=2000000000;
var
  a,b,q:array[0..100001] of longint;
  n,m,i,p1,p2,ans:longint;
  maxst,st:int64;
Procedure QSort(l,r:longint);
var
  m,i,j,t:longint;
begin
  m:=q[(l+r) div 2];
  i:=l;
  j:=r;
  repeat
    while q[i]<m do inc(i);
    while q[j]>m do dec(j);
    if i<=j then begin
      t:=q[i];q[i]:=q[j];q[j]:=t;
      inc(i);dec(j);
    end;
  until i>j;
  if j>l then QSort(l,j);
  if i<r then QSort(i,r);
end;
begin
  reset(input,'input.txt');
  read(n);
  for i:=1 to n do read(a[i]);
  q:=a;QSort(1,n);a:=q;
  read(m);
  for i:=1 to m do read(b[i]);
  q:=b;QSort(1,m);b:=q;
  a[0]:=-INF;
  a[n+1]:=INF;
  b[0]:=-INF;
  b[m+1]:=INF;
  ans:=0;
  maxst:=0;
  p1:=0;p2:=0;
  for i:=a[1] to b[m] do begin
    while a[p1+1]<=i do inc(p1);
    while b[p2+1]<i do inc(p2);
    st:=i*min(p1,m-p2);
    if st>maxst then begin
      maxst:=st;
      ans:=i;
    end;
  end;
  rewrite(output,'output.txt');
  write(ans);
end.