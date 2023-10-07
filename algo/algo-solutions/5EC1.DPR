{$APPTYPE CONSOLE}
var
  a,b:array[1..1001] of longint;
  i,j,n:longint;
begin
  n:=0;
  while not eoln do begin
    inc(n);
    read(a[n]);
  end;
  for i:=1 to n do begin
    j:=i+1;
    b[i]:=a[i];
    while (b[i]>=a[j])and(j<n+1) do inc(j);
    if j=n+1 then b[i]:=-1 else b[i]:=a[j];
  end;
  for i:=1 to n do write(b[i],' ');
end.