{$APPTYPE CONSOLE}
Var
  z:array[1..100] of string;
  i,n,j:longint;
  b:boolean;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(n);
  for i:=1 to n do readln(z[i]);
  for j:=1 to length(z[1]) do begin
    b:=true;
    for i:=1 to n do
      if z[i,j]<>z[1,j] then b:=False;
    if b then write(z[1,j]) else write('?');
  end;
end.