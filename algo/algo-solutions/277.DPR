{$APPTYPE CONSOLE}
var
  a,c,b:array[0..10000] of longint;
  n,i,j,k,s:longint;
begin
  read(n);
  for i:=1 to n do read(a[i]);
  s:=0;
  for i:=1 to n do inc(s,a[i]);
  k:=s div 2;
  b[0]:=0;
  for i:=1 to s do b[i]:=-1;
  for i:=1 to n do
    for j:=0 to s-a[i] do
      if (b[j]<>-1)and(b[j]<>i)and(b[j+a[i]]=-1)then b[j+a[i]]:=i;
  while (b[k]=-1)and(k>0) do dec(k);
  i:=0;
  while (k>0) do  begin
    inc(i);
    c[i]:=b[k];
    k:=k-a[b[k]];
  end;
  write(i);
  for j:=1 to i do write(' ',c[j]);
end.