Vap
  f,g:text;
  a1,a2,a3:longint;
  k:integer;
begin
  assign(f,'input.txt');
  reset(f);
  read(f,a1,a2,a3);
  close(f);
  if (a1<>a2)and(a2<>a3)and(a1<>a3) then k:=3 else
    if (a1=a2)and(a2=a3)then k:=1 else k:=2;
  assign(g,'output.txt');
  rewrite(g);
  writeln(g,k);
  close(g);
end.