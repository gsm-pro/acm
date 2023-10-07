Var
  f,g:text;
  x1,y1,x2,y2,t,u,v:longint;
begin
  assign(f,'input.txt');
  reset(f);
  readln(f,x1,y1,x2,y2);
  u:=abs(x2-x1);
  v:=abs(y2-y1);
  if u>=v then t:=u;
  if u<v then t:=v;
  assign(g,'output.txt');
  rewrite(g);
  writeln(g,t);
  close(g);
end.