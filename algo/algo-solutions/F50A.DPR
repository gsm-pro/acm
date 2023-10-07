{$APPTYPE CONSOLE}
var
  n,k,l,r,i,m:longint;
  a,x,v:array[1..2000] of longint;
begin
  readln(n);
  for i:=1 to n do begin
    read(a[i]);
    x[i+n]:=a[i];
  end;
  readln(k,l,r);
  k:=k mod n;
  for i:=1 to n do x[i]:=x[i+n];
  m:=0;
  for i:=n-k+1 to 2*n-k do begin
    inc(m);
    v[m]:=x[i];
  end;
  for i:=1 to l-1 do write(v[i],' ');
  for i:=r downto l do write(v[i],' ');
  for i:=r+1 to n do write(v[i],' ');
end.