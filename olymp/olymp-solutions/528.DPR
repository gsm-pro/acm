{$APPTYPE CONSOLE}
uses SysUtils;
var
  a,b:array[1..100] of string[100];
  v:string[4];
  n,m,i,j:longint;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(n,m);
  for i:=1 to m do begin
    readln(a[i]);
    trim(a[i]);
  end;
  for i:=1 to m do begin
    readln(b[i]);
    trim(b[i]);
  end;
  readln(v);
  for i:=1 to m do begin
    for j:=1 to n do begin
      if (a[i,j]='0')and(b[i,j]='0') then write(v[1]);
      if (a[i,j]='0')and(b[i,j]='1') then write(v[2]);
      if (a[i,j]='1')and(b[i,j]='0') then write(v[3]);
      if (a[i,j]='1')and(b[i,j]='1') then write(v[4]);
    end;
    writeln;
  end;
end.