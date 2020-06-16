Var
  f,g:text;
  m,n:longint;
begin
  assign(f,'input.txt');
  reset(f);
  read(f,n,m);
  close(f);
  assign(g,'output.txt');
  rewrite(g);
  if (m mod n)=0 then writeln(g,'Party is coming')
                 else writeln(g,'It is a boring day');
  close(g);
end.