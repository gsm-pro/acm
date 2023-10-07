{$APPTYPE CONSOLE}
Var
  a,p,r:array[1..15000] of longint;
  z:array[1..125] of longint;
  n,i,j,q,s,ps:longint;
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
      inc(i);dec(j);
    end;
  until i>j;
  if j>l then QSort(l,j);
  if i<r then QSort(i,r);
end;
Begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  for i:=1 to n do read(p[i]);
  for i:=1 to n do read(a[i]);
  for i:=1 to n do r[i]:=1;
  QSort(1,n);
  q:=trunc(sqrt(n));
  if q*q<>n then inc(q);
  for i:=1 to q do z[i]:=q;
  for i:=1 to n do begin
    s:=0;
    ps:=0;
    while s<p[i] do begin
      inc(ps);
      inc(s,z[ps]);
    end;
    dec(s,z[ps]);
    j:=(ps-1)*q;
    while s<p[i] do begin
      inc(j);
      inc(s,r[j]);
    end;
    write(a[j],' ');
    r[j]:=0;
    dec(z[ps]);
  end;
end.