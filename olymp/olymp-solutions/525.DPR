{$APPTYPE CONSOLE}
uses math;
var
  n,m,i,j,k,l:longint;
  ans:extended;
  s:array[1..20] of extended;
  a:array[1..7,1..20,1..20] of extended;
  z:array[0..7,1..20] of extended;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(n,m);
  for i:=1 to n do read(s[i]);
  for i:=1 to m do
    for j:=1 to n do
      for k:=1 to n do read(a[i][j][k]);
  ans:=0;
  for i:=1 to n do begin
    for j:=0 to 7 do for k:=1 to 20 do z[j][k]:=0;
    z[0][i]:=s[i];
    for j:=1 to m do
      for k:=1 to n do
        for l:=1 to n do
          z[j][l]:=max(z[j][l],z[j-1][k]*a[j][k][l]);
    ans:=ans+z[m][1];
  end;
  write(ans:0:8);
end.