Var
  f,g:text;
  p,n,a,i:longint;
begin
  assign(f,'input.txt');
  reset(f);
  readln(f,n,p);
  close(f);
  a:=0;
  i:=0;
  repeat
    inc(i);
    inc(a);
    if a=n+1 then a:=1;
  until i=p;
  assign(g,'output.txt');
  rewrite(g);
  writeln(g,a);
  close(g);
end.