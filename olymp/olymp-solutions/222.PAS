Var
  f,g:text;
  a:array[1..52,1..52] of char;
  i,j,m,n,k:longint;
begin
  assign(f,'input.txt');
  reset(f);
  readln(f,n,m);
  for i:=1 to n+2 do
    for j:=1 to m+2 do a[i,j]:='.';
  for i:=2 to n+1 do begin
    for j:=2 to m+1 do read(f,a[i,j]);
    readln(f);
  end;
  close(f);
  for i:=2 to n+1 do
    for j:=2 to m+1 do
      if a[i,j]='*' then begin
        if (a[i-1,j]='.')or(a[i+1,j]='.')or
           (a[i,j-1]='.')or(a[i,j+1]='.')or
           (a[i-1,j-1]='.')or(a[i+1,j+1]='.')or
           (a[i+1,j-1]='.')or(a[i-1,j+1]='.')then a[i,j]:='+';
        end;
  k:=0;
  for i:=2 to n+1 do
    for j:=2 to m+1 do
      if a[i,j]='*' then inc(k);
  assign(g,'output.txt');
  rewrite(g);
  writeln(g,k*10000);
  close(g);
end.