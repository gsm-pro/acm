Var
  f,g:text;
  i,j,k,n,s,d,y:longint;
begin
  assign(f,'input.txt');
  reset(f);
  read(f,k);
  close(f);
  s:=0;
  i:=5;
  n:=0;
  repeat
    inc(i);
    d:=2;
    y:=(i div 2)+1;
    for j:=2 to y do
      if (i mod j)=0 then inc(d);
    if d=4 then begin
      inc(n);
      inc(s,i);
    end;
  until n=k;
  assign(g,'output.txt');
  rewrite(g);
  writeln(g,s);
  close(g);
end.