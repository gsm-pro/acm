{$APPTYPE CONSOLE}
Var
  n,k1,k2,ans:int64;
Function GCD(a,b:int64):int64;
begin
  if a mod b=0 then GCD:=b else GCD:=GCD(b,a mod b);
end;
begin
  read(n,k1,k2);
  ans:=n;
  dec(ans,n div k1);
  dec(ans,n div k2);
  inc(ans,n div (k1*k2 div GCD(k1,k2)));
  write(ans);
end.