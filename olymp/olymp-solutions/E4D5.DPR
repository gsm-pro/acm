{$APPTYPE CONSOLE}
Var
  a,b,n,d:int64;
  i:byte;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(a,b,n);
  d:=1;
  for i:=31 downto 0 do begin
     d:=(d*d)mod n;
     if b and (1 shl i)<>0 then d:=(d*a) mod n;
  end;
  write(d);
end.