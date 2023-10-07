{$APPTYPE CONSOLE}
var
  ans,n,i:double;
const
  eps=1e-9;
begin
  read(n);
  ans:=n;
  i:=2;
  while i<=trunc(sqrt(n)) do begin
    if frac(n/i)<eps then begin
      ans:=ans*(i-1)/i;
      while frac(n/i)<eps do n:=n/i;
    end;
    i:=i+1;
  end;
  if n>1 then ans:=ans*(n-1)/n;
  write(ans:0:0);
end.