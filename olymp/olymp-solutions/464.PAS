Var
  g1,g2:text;
  m,n,t,k,s,start,finish:longint;
begin
  assign(g1,'input.txt');
  reset(g1);
  read(g1,m,n,t,k);
  close(g1);
  start:=m*60+n+5;
  finish:=720;
  s:=0;
  while start<=finish do begin
    inc(start,t);
    if start<=finish then inc(s);
    inc(start,k);
  end;
  assign(g2,'output.txt');
  rewrite(g2);
  writeln(g2,s);
  close(g2);
end.