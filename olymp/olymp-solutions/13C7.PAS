Var
  f,g:text;
  a,b:integer;
begin
  assign(f,'input.txt');
  reset(f);
  read(f,a,b);
  close(f);
  assign(g,'output.txt');
  rewrite(g);
  if ((a=0)and(b=8))or
     ((a=4)and(b=8))or
     ((a=5)and(b=8))then writeln(g,'YES')
                    else writeln(g,'NO');
  close(g);
end.