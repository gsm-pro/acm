{$APPTYPE CONSOLE}
Var
  x,y,xx,yy:array[1..100000] of int64;
  i,n:longint;
  k:int64;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  for i:=1 to n do begin
    read(x[i],y[i]);
    inc(xx[x[i]]);
    inc(yy[y[i]]);
  end;
  k:=0;
  for i:=1 to n do k:=k+(xx[x[i]]-1)*(yy[y[i]]-1);
  write(k);
end.