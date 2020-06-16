{$APPTYPE CONSOLE}
uses math;
Var
  x,k1,k2,n,i,ans:longint;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  k1:=0;
  k2:=0;
  for i:=1 to n do begin
    read(x);
    if x=50 then inc(k1);
    if x=100 then inc(k2);
  end;
  ans:=min(k1,k2);
  dec(k1,ans);
  dec(k2,ans);
  ans:=ans+k2+k1 div 3;
  if k1 mod 3<>0 then inc(ans);
  write(ans);
end.