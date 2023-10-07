Var
  f,g:text;
  a:array[1..7500]of integer;
  i,n,p,q,k,r:longint;
begin
  assign(f,'input.txt');
  reset(f);
  readln(f,n);
  for i:=1 to n do read(f,a[i]);
  readln(f,q);
  close(f);
  k:=1;
  while (a[q]<>0)and(a[q]<>q) do begin
    inc(k);
    for i:=1 to n do
      if a[i]=q then begin
        r:=i;
        break;
       end;
    p:=a[q];
    a[q]:=q;
    q:=p;
    a[r]:=q;
  end;
  assign(g,'output.txt');
  rewrite(g);
  writeln(g,k);
  close(g);
end.