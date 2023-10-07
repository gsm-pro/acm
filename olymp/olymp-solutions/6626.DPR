{$APPTYPE CONSOLE}
Var
  f,g:text;
  i,n,p:integer;
begin
  assign(f,'input.txt');
  reset(f);
  readln(f,n);
  close(f);
  i:=1;
  if (n<>24)and(n<>57)and(n<>79) then
    repeat
      p:=n;
      inc(i);
      n:=n*n;
      if (n<10) then n:=0;
      if (n<100)  and(n>=10)   then n:=n div 10;
      if (n<1000) and(n>=100)  then n:=n div 10;
      if (n>=1000) then n:=(n mod 1000)div 10;
    until p=n;
  if (n=24)or(n=57) then i:=2;
  if (n=79) then i:=3;
  assign(g,'output.txt');
  rewrite(g);
  write(g,i-2);
  close(g);
end.