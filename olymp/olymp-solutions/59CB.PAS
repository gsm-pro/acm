Var
  f,g:text;
  a1,a2,b1,b2,k:longint;
begin
  assign(f,'input.txt');
  reset(f);
  read(f,a1,a2,b1,b2);
  close(f);
  if ((a1=b1)and(a2=b2))or((a1=b2)and(a2=b1)) then k:=0 else
    if ((a1<>b1)and(a2<>b2))and((a1<>b2)and(a2<>b1)) then k:=2 else k:=1;
  assign(g,'output.txt');
  rewrite(g);
  writeln(g,k);
  close(g);
end.