Var
  f,g:text;
  a:array[1..3] of longint;
  r,i,j,m:longint;
begin
  assign(f,'input.txt');
  reset(f);
  for i:=1 to 3 do read(f,a[i]);
  close(f);
  m:=(a[1]+a[2]+a[3]) div 3;
  assign(g,'output.txt');
  rewrite(g);
  if (a[1]+a[2]+a[3])mod 3<>0 then writeln(g,'IMPOSSIBLE')
                              else begin
    r:=0;
    for i:=1 to 3 do if a[i]<m then inc(r,abs(m-a[i]));
    writeln(g,r);
  end;
  close(g);
end.