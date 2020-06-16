{$APPTYPE CONSOLE}
Var
  f,g:text;
  i,n,p,pr:longint;
  a:array[1..1000] of longint;
begin
  assign(f,'input.txt');
  reset(f);
  read(f,n);
  close(f);
  i:=1;
  a[2*i]:=4;
  pr:=6;
  repeat
    inc(i);
    a[2*i]:=a[2*(i-1)]+pr;
    inc(pr,4);
  until i=500;
  p:=a[n];
  assign(g,'output.txt');
  rewrite(g);
  write(g,p);
  close(g);
end.