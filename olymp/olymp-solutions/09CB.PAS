Var
  f,g:text;
  a:array[1..1000] of byte;
  a1,a2,b1,b2,k,i:longint;
begin
  assign(f,'input.txt');
  reset(f);
  read(f,a1,a2,b1,b2);
  close(f);
  for i:=1 to 1000 do a[i]:=0;
  for i:=a1 to a2 do a[i]:=1;
  for i:=a2 to a1 do a[i]:=1;
  for i:=b1 to b2 do a[i]:=1;
  for i:=b2 to b1 do a[i]:=1;
  k:=0;
  for i:=1 to 1000 do
    if a[i]=1 then inc(k);
  assign(g,'output.txt');
  rewrite(g);
  writeln(g,k);
  close(g);
end.