Var
  f,g:text;
  i,k,n:longint;
  s:string;
begin
  assign(f,'input.txt');
  reset(f);
  readln(f,n);
  close(f);
  k:=0;
  for i:=1 to n do
    if (i mod 3)=0 then inc(k) else
      begin
        str(i,s);
        if pos('3',s)<>0 then inc(k);
      end;
  assign(g,'output.txt');
  rewrite(g);
  writeln(g,k);
  close(g);
end.