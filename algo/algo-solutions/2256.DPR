{$APPTYPE CONSOLE}
var                                                                        
  n,k:int64;
  f:array[0..90] of int64;
  i:longint;
  s:string;
begin
  readln(n,k);
  f[0]:=1;
  f[1]:=2;
  f[2]:=3;
  for i:=3 to 90 do f[i]:=f[i-1]+f[i-2];
  repeat
    if k=0 then k:=f[n];
    if k<=f[n-1] then s:=s+'a'; 
    if k> f[n-1] then s:=s+'b';
    k:=k mod f[n-1];
    dec(n);
  until n=0;
  write(s);
end.