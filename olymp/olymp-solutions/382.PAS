Var
  f,g:text;
  h:array[1..1000]of integer;
  k1,k2,n,v,i:longint;
begin
  assign(f,'input.txt');
  reset(f);
  readln(f,n);
  for i:=1 to n do read(f,h[i]);
  close(f);
  v:=0;
  k2:=0;
  for i:=1 to n do
    if h[i]>v then begin
      inc(k2);
      v:=h[i];
    end;
  v:=0;
  k1:=0;
  for i:=n downto 1 do
    if h[i]>v then begin
      inc(k1);
      v:=h[i];
    end;
  assign(g,'output.txt');
  rewrite(g);
  if k1>=k2 then begin
    writeln(g,'1');
    writeln(g,k1);
  end;
  if k1<k2 then begin
    writeln(g,'2');
    writeln(g,k2);
  end;
  close(g);
end.