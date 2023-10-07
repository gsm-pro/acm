Var
  f,g:text;
  a,n,i,s:longint;
  b:double;
begin
  assign(f,'input.txt');
  reset(f);
  assign(g,'output.txt');
  rewrite(g);
  readln(f,n);
  s:=0;
  for i:=1 to n do begin
    read(f,a);
    inc(s,a);
    b:=s/i;
    write(g,b:0:2,' ');
  end;
  close(f);
  close(g);
end.