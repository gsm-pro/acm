{$APPTYPE CONSOLE}
Var
  f,g:text;
  a:array[1..9,-1..9] of char;
  n,i,j:longint;
begin
  assign(f,'input.txt');
  reset(f);
  for i:=1 to 7 do begin
    for j:=1 to 7 do read(f,a[i,j]);
    readln(f);
  end;
  close(f);
  n:=0;
  for i:=1 to 7 do
    for j:=1 to 7 do begin
      if (a[i,j]='o')and(a[i+1,j]='o')and(a[i+2,j]='.')then inc(n);
      if (a[i,j]='.')and(a[i+1,j]='o')and(a[i+2,j]='o')then inc(n);
      if (a[i,j]='o')and(a[i,j+1]='o')and(a[i,j+2]='.')then inc(n);
      if (a[i,j]='.')and(a[i,j+1]='o')and(a[i,j+2]='o')then inc(n);
    end;
  assign(g,'output.txt');
  rewrite(g);
  writeln(g,n);
  close(g);
end.