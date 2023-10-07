Var
  f,g:text;
  h:array[1..1000]of byte;
  p,i,n,r:longint;
begin
  assign(f,'input.txt');
  reset(f);
  readln(f,n);
  for i:=1 to n do read(f,h[i]);
  close(f);
  for i:=1 to n-1 do begin
    r:=abs(h[i+1]-h[i]);
    inc(p,r+2);
  end;
  p:=p+h[1]+h[n]+2;
  assign(g,'output.txt');
  rewrite(g);
  writeln(g,p);
  close(g);
end.