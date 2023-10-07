{$APPTYPE CONSOLE}
var
  a:array[1..100] of int64;
  i,n:byte;
  ans:int64;
Function GCD(a,b:int64):int64;
begin
  if a mod b=0 then GCD:=b else GCD:=GCD(b,a mod b);
end;
Function NOK(x,y:int64):int64;
begin
  NOK:=x*y div GCD(x,y);
end;
begin
  readln(n);
  for i:=1 to n do read(a[i]);
  ans:=1;
  for i:=1 to n do ans:=NOK(ans,a[i]+1);
  write(ans-1);
end.