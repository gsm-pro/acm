Var
  f,g:text;
  a,x,y,z:longint;
begin
  assign(f,'input.txt');
  reset(f);
  read(f,a,x,y);
  close(f);
  if (x<a)and(x>0)and(y<a)and(y>0)then z:=0;
  if ((x=0)and(y<=a)and(y>=0))or
     ((x=a)and(y<=a)and(y>=0))or
     ((y=0)and(x<=a)and(x>=0))or
     ((y=a)and(x<=a)and(x>=0))then z:=1;
  if (x<0)or(y<0)or(x>a)or(y>a) then z:=2;
  assign(g,'output.txt');
  rewrite(g);
  writeln(g,z);
  close(g);
end.