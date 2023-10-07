{$APPTYPE CONSOLE}
Var
  c:array[1..100] of longint;
  n,k,x,i:longint;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  for i:=1 to n do read(c[i]);
  read(k);
  for i:=1 to k do begin
    read(x);
    dec(c[x]);
  end;
  for i:=1 to n do
    if c[i]<0 then writeln('yes')
              else writeln('no');
end.