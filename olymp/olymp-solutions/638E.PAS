Var
  f,g:text;
  i,j,k,n,p,d,s,t:longint;
  a:array[1..1000]of integer;
begin
  assign(f,'input.txt');
  reset(f);
  readln(f,n);
  for i:=1 to n do read(f,a[i]);
  close(f);
  p:=0;
  d:=0;
  t:=0;
  for i:=1 to n do begin
    s:=0;
    for j:=i to n do begin
      inc(s,a[j]);
      t:=j-i+1;
      if (s=0)and(t>d) then begin
        p:=i;
        d:=t;
      end;
    end;
  end;
  assign(g,'output.txt');
  rewrite(g);
  writeln(g,d,' ',p);
  close(g);
end.