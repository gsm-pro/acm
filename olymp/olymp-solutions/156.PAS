Var
  f,g:text;
  i,j,n:integer;
  a:array[1..20,1..20]of integer;
begin
  assign(f,'input.txt');
  reset(f);
  read(f,n);
  close(f);
  for i:=1 to n do
    for j:=1 to i do begin
      a[i,j]:=j-1;
      a[j,i]:=a[i,j];
    end;
  for i:=1 to n do
    for j:=1 to n do
      a[i,2*n-j+1]:=a[i,j];
  for i:=1 to n do
    for j:=1 to 2*n do
      a[2*n-i+1,j]:=a[i,j];
  assign(g,'output.txt');
  rewrite(g);
  for i:=1 to 2*n do begin
    for j:=1 to 2*n do write(g,a[i,j]);
    writeln(g);
  end;
  close(g);
end.