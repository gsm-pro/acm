Var
  f,g:text;
  h1,m1,h2,m2,s:longint;
Begin
  assign(f,'input.txt');
  reset(f);
  read(f,h1,m1,h2,m2);
  close(f);
  if m2<m1 then inc(m2,60);
  if h2<h1 then inc(h2,24);
  s:=h2-h1;
  m1:=m1+s;
  if m2<m1 then m2:=m2+60;
  s:=s+(m2-m1);
  assign(g,'output.txt');
  rewrite(g);
  writeln(g,s);
  close(g);
End.