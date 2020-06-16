{$APPTYPE CONSOLE}
var
  a:array[0..1000] of longint;
  i,j,k,n:longint;
begin
  readln(n);
  for i:=1 to n do readln(a[i]);
  k:=0;
  for i:=1 to n do
    for j:=1 to n do
      if a[j]=2*a[i] then begin
        inc(k);
        break;
      end;  
  write(k);
end.