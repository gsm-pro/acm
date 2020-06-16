Var
  f,g:text;
  n,k,h:integer;
begin
  assign(f,'input.txt');
  reset(f);
  read(f,n,k);
  close(f);
  h:=n div k;
  if (n mod k)<>0 then inc(h);
  assign(g,'output.txt');
  rewrite(g);
  writeln(g,h);
  close(g);
end.