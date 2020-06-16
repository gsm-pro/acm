Var
  f,g:text;
  a,b:array[1..1000]of longint;
  n,i,j,m:longint;
begin
  assign(f,'input.txt');
  reset(f);
  readln(f,n);
  for i:=1 to n do read(f,b[i]);
  close(f);
  for j:=1 to n-1 do
    for i:=1 to n-1 do
      if b[i]>b[i+1] then begin
        m:=b[i];
        b[i]:=b[i+1];
        b[i+1]:=m;
      end;
  for i:=2 to n do a[i]:=b[i]-b[i-1];
  a[1]:=b[1];
  assign(g,'output.txt');
  rewrite(g);
  write(g,a[1]);
  for i:=2 to n do write(g,' ',a[i]);
  close(g);
end.