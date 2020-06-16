{$APPTYPE CONSOLE}
Var
  f,g:text;
  x,a:array[1..6] of longint;
  i:longint;
begin
  assign(f,'input.txt');
  reset(f);
  for i:=1 to 6 do read(f,a[i]);
  close(f);
  x[1]:=1-a[1];
  x[2]:=1-a[2];
  x[3]:=2-a[3];
  x[4]:=2-a[4];
  x[5]:=2-a[5];
  x[6]:=8-a[6];
  assign(g,'output.txt');
  rewrite(g);
  for i:=1 to 6 do write(g,x[i],' ');
  close(g);
end.