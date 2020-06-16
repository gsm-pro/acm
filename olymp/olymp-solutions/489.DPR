{$APPTYPE CONSOLE}
Var
  f,g:text;
  n,n1,n2:longint;
begin
  assign(f,'input.txt');
  reset(f);
  readln(f,n);
  close(f);
  n1:=n div 2;
  n2:=n-n1;
  assign(g,'output.txt');
  rewrite(g);
  writeln(g,(n1+1)*(n2+1));
  close(g);
end.