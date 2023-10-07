Var
  f,g:text;
  xa,xb,xc:longint;
begin
  assign(f,'input.txt');
  reset(f);
  read(f,xa,xb);
  close(f);
  if xa<xb then xc:=xa+1;
  if xa>xb then xc:=xa-1;
  assign(g,'output.txt');
  rewrite(g);
  writeln(g,xc);
  close(g);
end.