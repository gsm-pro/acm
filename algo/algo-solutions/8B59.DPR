{$APPTYPE CONSOLE}
var
  b:array[1..40] of longint;
  i,n:longint;
begin
  readln(n);
  b[1]:=2;
  b[2]:=4;
  b[3]:=7;
  for i:=4 to 35 do b[i]:=b[i-3]+b[i-2]+b[i-1];
  write(b[n]);
end.