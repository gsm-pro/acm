{$APPTYPE CONSOLE}
var
  i,j,N:longint;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(N);
  write('1 ');
  i:=2;
  while (2*i<=N) do begin
    write(2*i,' ');
    inc(i);
  end;
  if (N>1)and odd(N) then begin
    write(N,' ');
    inc(i);
  end;
  while i<=N do begin
    j:=i;
    while odd(j) do j:=(j+1) div 2;
    if j>2 then write(j-1,' ') else write(j,' ');
    inc(i);
  end;
end.