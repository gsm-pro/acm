Var
  f,g:text;
  n,i,a,b,c,d:longint;
begin
  assign(f,'input.txt');
  reset(f);
  assign(g,'output.txt');
  rewrite(g);
  readln(f,n);
  for i:=1 to n do begin
    readln(f,a,b,c,d);
    if ((a=d)and(b+c=a))or
       ((b=d)and(a+c=b))or
       ((b=c)and(a+d=b))or
       ((a=c)and(b+d=a))then writeln(g,'YES')
                        else writeln(g,'NO');
  end;
  close(f);
  close(g);
end.