Var
  f,g:text;
  a,b,s,k,i:longint;
begin
  assign(f,'input.txt');
  reset(f);
  read(f,a,b);
  close(f);
  s:=a;
  k:=a;
  for i:=2 to b do begin
    if (i mod 5)=0 then dec(k,2) else inc(k);
    inc(s,k);
  end;
  assign(g,'output.txt');
  rewrite(g);
  writeln(g,s);
  close(g);
end.