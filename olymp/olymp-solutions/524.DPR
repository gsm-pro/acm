{$APPTYPE CONSOLE}
uses math;
Var
  k1,k2,k3,i,p1,p2,p3,ans:longint;
  a,b,c:array[1..1001] of longint;
Procedure Sort(x:longint;var z:array of longint);
var
  i,j,t:longint;
begin
  for i:=0 to x-2 do
    for j:=0 to x-2 do
      if z[j]>z[j+1] then begin
        t:=z[j];z[j]:=z[j+1];z[j+1]:=t;
      end;
end;
Begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(k1,k2,k3);
  for i:=1 to k1 do read(a[i]);
  for i:=1 to k2 do read(b[i]);
  for i:=1 to k3 do read(c[i]);
  Sort(k1,a);Sort(k2,b);Sort(k3,c);
  a[k1+1]:=-1;b[k2+1]:=-1;c[k3+1]:=-1;
  ans:=0;
  p2:=1;p3:=1;
  for p1:=1 to k1 do begin
    while (p2<=k2)and(b[p2]<=a[p1]) do inc(p2);
    if p2=k2+1 then break;
    while (p3<=k3)and(c[p3]<=b[p2]) do inc(p3);
    if p3=k3+1 then break;
    b[p2]:=-1;
    c[p3]:=-1;
    inc(ans);
  end;
  write(ans);
end.