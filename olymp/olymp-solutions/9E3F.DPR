{$APPTYPE CONSOLE}
Var
  a:array[1..10000] of longint;
  z:array[1..101] of longint;
  n,k,i,j,q,mx,e,r,s:longint;
Begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  for i:=1 to n do read(a[i]);
  q:=trunc(sqrt(n));
  if q*q<>n then n:=(q+1)*(q+1);
  q:=trunc(sqrt(n));
  for i:=1 to q do begin
    mx:=0;
    for j:=1 to q do if a[(i-1)*q+j]>mx then mx:=a[(i-1)*q+j];
    z[i]:=mx;
  end;
  read(k);
  for i:=1 to k do begin
    read(e);
    r:=q+1;
    for j:=1 to q do
      if z[j]>=e then begin
        r:=j;
        break;
      end;
    if r=q+1 then continue;
    for j:=1 to q do
      if a[(r-1)*q+j]>=e then begin
        dec(a[(r-1)*q+j],e);
        break;
      end;
    mx:=0;
    for j:=1 to q do if a[(r-1)*q+j]>mx then mx:=a[(r-1)*q+j];
    z[r]:=mx;
  end;
  s:=0;
  for i:=1 to n do inc(s,a[i]);
  write(s);
end.