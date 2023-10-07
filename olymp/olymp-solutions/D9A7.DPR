{$APPTYPE CONSOLE}
var
  f:array[0..20] of int64;
  ans:int64;
  i,n:longint;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  f[0]:=1;
  for i:=1 to 20 do f[i]:=f[i-1]*i;
  ans:=0;
  for i:=3 to n do
    ans:=ans+(f[i-1] div 2)*(f[n] div f[i] div f[n-i]);
  write(ans);
end.