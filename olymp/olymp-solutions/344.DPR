{$APPTYPE CONSOLE}
uses Math;
Var
  a,z:array[0..10,0..10] of longint;
  n,m,i,j,k,l:longint;
  ans,mn:double;
Function Av(x1,y1,x2,y2:longint):double;
begin
  Av:=(z[x2,y2]-z[x2,y1-1]-z[x1-1,y2]+z[x1-1,y1-1])/((x2-x1+1)*(y2-y1+1));
end;
Begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n,m);
  for i:=1 to n do for j:=1 to m do read(a[i,j]);
  for i:=1 to n do for j:=1 to m do z[i,j]:=z[i-1,j]+z[i,j-1]-z[i-1,j-1]+a[i,j];
  ans:=-1e9;
  for i:=1 to n do
    for j:=1 to m do begin
      mn:=1e9;
      for k:=1 to i do
        for l:=1 to j do mn:=min(mn,Av(k,l,i,j));
      ans:=max(ans,mn);
    end;
  write(ans:0:4);
end.