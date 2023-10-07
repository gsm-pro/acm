{$APPTYPE CONSOLE}
var
  n,k,i,kol:longint;
begin
  readln(k);
  kol:=0;
  for i:=1 to k do begin
    readln(n);
    if (n<0)and(odd(abs(n))=True) then inc(kol);
  end;
  write(kol);
end.