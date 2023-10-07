Var
  f,g:text;
  n,q,i,j,x,k:longint;
  p:array[1..50] of longint;
  a:array[0..5000] of extended;
  z:array[1..100] of longint;
begin
  assign(f,'input.txt');
  reset(f);
  read(f,n,q);
  for i:=1 to n do read(f,p[i]);
  close(f);
  for i:=1 to 100 do inc(z[p[i]]);
  a[0]:=1;
  for k:=1 to 100 do
    for j:=q downto 1 do
      for i:=1 to z[k] do
         if j>=i*k then a[j]:=a[j]+a[j-i*k] else break;
  assign(g,'output.txt');
  rewrite(g);
  write(g,a[q]:0:0);
  close(g);
end.