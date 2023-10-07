Var
  f,g:text;
  a,b,x1,x2:longint;
begin
  assign(f,'input.txt');
  reset(f);
  read(f,a,b,x1,x2);
  close(f);
  assign(g,'output.txt');
  rewrite(g);
  if (x1+x2<=a)or(x1+x2<=b)or((x1<=a)and(x2<=b))or((x1<=b)and(x2<=a))
    then writeln(g,'YES')
    else writeln(g,'NO');
  close(g);
end.