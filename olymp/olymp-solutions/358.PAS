Var
  f,g:text;
  a,s:integer;
begin
  assign(f,'input.txt');
  reset(f);
  read(f,a);
  close(f);
  assign(g,'output.txt');
  rewrite(g);
  writeln(g,a div 100+a mod 10+a div 10 mod 10);
  close(g);
end.