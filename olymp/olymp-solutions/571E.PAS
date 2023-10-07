Var
  f,g:text;
  i,n,x11,x12,x21,x22:longint;
begin
  assign(f,'input.txt');
  reset(f);
  assign(g,'output.txt');
  rewrite(g);
  readln(f,n);
  for i:=1 to n do begin
    readln(f,x11,x12,x21,x22);
    if ((x11<x21)and(x12<x22)and(x12<x21))or
       ((x11>x21)and(x12>x22)and(x11>x22))then writeln(g,'NO')
                                          else writeln(g,'YES');
  end;
  close(f);
  close(g);
end.