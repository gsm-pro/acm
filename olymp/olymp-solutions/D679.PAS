Var
  f,g:text;
  a,b,k:integer;
begin
  assign(f,'input.txt');
  reset(f);
  read(f,a,b);
  close(f);
  if ((a<>0)and(b<>0))or((a<>0)and(b=0)) then k:=1;
  if (a=0)and(b=0)then k:=-1;
  if (a=0)and(b<>0) then k:=0;
  assign(g,'output.txt');
  rewrite(g);
  writeln(g,k);
  close(g);
end.