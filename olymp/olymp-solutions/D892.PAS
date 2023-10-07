Var
  g1,g2:text;
  a:array[1..1000] of integer;
  i,k,n:longint;
begin
  assign(g1,'input.txt');
  reset(g1);
  readln(g1,n);
  for i:=1 to n do read(g1,a[i]);
  close(g1);
  k:=a[1];
  for i:=2 to n do if a[i]<=k then inc(k) else break;
  assign(g2,'output.txt');
  rewrite(g2);
  writeln(g2,k);
  close(g2);
end.