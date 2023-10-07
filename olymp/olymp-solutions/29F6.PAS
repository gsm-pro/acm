Var
  f,g:text;
  a1,a2,a3,k,s:longint;
Function Fac(x:longint):longint;
var
  f,i:longint;
begin
  f:=1;
  for i:=1 to x do f:=f*i;
  Fac:=f;
end;
begin
  assign(f,'input.txt');
  reset(f);
  readln(f,k);
  close(f);
  if s>8 then s:=0
         else s:=((fac(8)*fac(8))div((fac(8-k)*fac(8-k)*fac(k))));
  assign(g,'output.txt');
  rewrite(g);
  writeln(g,s);
  close(g);
end.