{$APPTYPE CONSOLE}
var
  n,i,k:longint;
  a:array[0..200,0..200] of longint;
begin
  readln(n);
  a[1,0]:=1;
  for i:=2 to 200 do a[1,i]:=0;
  for i:=1 to 200 do a[i,i]:=1;
  for i:=2 to n do
    for k:=i downto 1 do begin
      if i=k then continue;
      a[i,k]:=a[i-k,k+1]+a[i,k+1];
    end;
  write(a[n,1]);
end.