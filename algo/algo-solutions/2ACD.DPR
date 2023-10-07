{$D-,I-,Q-,R-}
{$APPTYPE CONSOLE}
var
  r,x,n,i:longint;
begin
  r:=0;
  readln(n);
  for i:=1 to n do begin
    read(x);
    r:=r xor x;
  end;
  write(r);
end.