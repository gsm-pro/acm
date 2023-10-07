Var
  f,g:text;
  a,p,sh,ft,ost:integer;
begin
  assign(f,'input.txt');
  reset(f);
  read(f,a);
  close(f);
  assign(g,'output.txt');
  rewrite(g);
  ft:=a div 240;
  ost:=a-240*ft;
  sh:=ost div 12;
  p:=ost-sh*12;
  writeln(g,ft,' ',sh,' ',p);
  close(g);
end.