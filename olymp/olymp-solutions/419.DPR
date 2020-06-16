{$APPTYPE CONSOLE}
var
  f,g:text;
  a:array[1..101,1..101] of string[1];
  i,j,n,kol,w,x,y:longint;
function FindValue(x,y:longint):longint;
var
  i,j,k,maxr:longint;
begin
  if n-y+1<=n-x+1 then maxr:=n-y+1
                  else maxr:=n-x+1;
  for k:=1 to maxr+1 do
    for i:=x to x+k-1 do
      for j:=y to y+k-1 do
        if a[i,j]='#' then begin
          FindValue:=k-1;
          exit;
        end;
end;
begin
  assign(f,'input.txt');
  reset(f);
  readln(f,n);
  for i:=1 to 101 do for j:=1 to 101 do a[i,j]:='#';
  for i:=1 to n do begin
    for j:=1 to n do read(f,a[i,j]);
    readln(f);
  end;
  close(f);
  kol:=0;
  for i:=1 to n do
    for j:=1 to n do
      if a[i,j]<>'#' then begin
        w:=FindValue(i,j);
        for x:=i to i+w-1 do
          for y:=j to j+w-1 do a[x,y]:='#';
        inc(kol);
      end;
  assign(g,'output.txt');
  rewrite(g);
  writeln(g,kol);
  close(g);
end.