Var
  f,g:text;
  a,b,f1,f2,ss:real;
begin
  assign(f,'input.txt');
  reset(f);
  read(f,a,b);
  close(f);
  f1:=(a+b)/2;
  f2:=sqrt(a*b);
  ss:=sqrt(f1*f2);
  assign(g,'output.txt');
  rewrite(g);
  writeln(g,ss:0:2);
  close(g);
end.