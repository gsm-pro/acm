{$APPTYPE CONSOLE}
type
  arr=array[0..10000] of longint;
var
  a,t,ans:arr;
  i,n,m,x,q,r:longint;
Procedure QSort(left,right:longint;var w:arr);
var
  m,i,j,t:longint;
begin
  m:=w[(left+right) div 2];
  i:=left;
  j:=right;
  repeat
    while w[i]<m do inc(i);
    while w[j]>m do dec(j);
    if i<=j then begin
      t:=w[i];
      w[i]:=w[j];
      w[j]:=t;
      inc(i);
      dec(j);
    end;
  until i>j;
  if j>left then QSort(left,j,w);
  if i<right then QSort(i,right,w);
end;
Function BinSearch(l,r,x:longint):longint;
var
  mid:longint;
begin
  mid:=(l+r) shr 1;
  while (l<=r)and(a[mid]<>x) do begin
    mid:=(l+r) shr 1;
    if x<a[mid] then r:=mid-1;
    if x>a[mid] then l:=mid+1;
  end;
  if a[mid]=x then BinSearch:=mid else BinSearch:=-1;
end;    
begin
  readln(n,m);
  for i:=1 to n do read(a[i]);
  QSort(1,n,a);
  q:=0;
  for i:=1 to m do begin
    read(x);
    if (x<a[1])or(x>a[n]) then continue;
    if BinSearch(1,n,x)<>-1 then begin
      inc(q);
      t[q]:=x;
    end;
  end;
  QSort(1,q,t);
  r:=0;
  t[0]:=1000000000;
  for i:=1 to q do
    if t[i-1]<>t[i] then begin
      inc(r);
      ans[r]:=t[i];
    end;
  writeln(r);
  for i:=1 to r do write(ans[i],' ');
end.