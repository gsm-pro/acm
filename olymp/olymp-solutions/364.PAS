Var
  f,g:text;
  k,i,n:longint;
begin
  assign(f,'input.txt');
  reset(f);
  read(f,k);
  close(f);
  i:=0;
  repeat
    inc(i);
    if ((i mod 2)<>0)and((i mod 5)<>0) then inc(n);
  until n=k;
  assign(g,'output.txt');
  rewrite(g);
  writeln(g,i);
  close(g);
end.