Var
  f,g:text;
  a,b,c,n:longint;
begin
  assign(f,'input.txt');
  reset(f);
  read(f,n);
  close(f);
  assign(g,'output.txt');
  rewrite(g);
  if (n mod 3)=0 then writeln(g,n div 3-1,' ', n div 3,' ',n div 3+1)
                 else writeln(g,'-1');
  close(g);
end.