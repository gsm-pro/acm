{$APPTYPE CONSOLE}
uses Math;
Var
  a,x:array[1..21] of byte;
  i,res,n,k,j,t:longint;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  for i:=1 to n do read(a[i]);
  for i:=1 to n-1 do
    for j:=1 to n-1 do
      if a[j]>a[j+1] then begin
        t:=a[j];
        a[j]:=a[j+1];
        a[j+1]:=t;
      end;
  k:=0;
  for i:=1 to n do
    if (i mod 2)=1 then begin
      inc(k);
      x[k]:=a[i];
    end;
  for i:=n downto 1 do
    if (i mod 2)=0 then begin
      inc(k);
      x[k]:=a[i];
    end;
  x[n+1]:=x[1];
  res:=0;
  for i:=1 to n do res:=max(res,abs(x[i+1]-x[i]));
  write(res);
end.