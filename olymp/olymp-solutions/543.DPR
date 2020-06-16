{$APPTYPE CONSOLE}
Var
  z:array[1..100,1..100] of char;
  i,j,n:longint;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  fillchar(z,sizeof(z),'.');
  if (n mod 2=0) then begin
    for i:=1 to n div 2 do z[1,i]:='*';
    for i:=1 to n div 2 do z[i,n]:='*';
    for i:=n div 2+1 to n do z[n,i]:='*';
    for i:=n div 2+1 to n do z[i,1]:='*';
  end;
  if (n mod 2=1) then begin
    for i:=1 to n div 2 do z[1,i]:='*';
    for i:=1 to n div 2+1 do z[i,n]:='*';
    for i:=n div 2+1 to n do z[n,i]:='*';
    for i:=n div 2+1 to n do z[i,1]:='*';
  end;
  for i:=1 to n do begin
    for j:=1 to n do write(z[i,j]);
    writeln;
  end;
end.