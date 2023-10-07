{$APPTYPE CONSOLE}
uses math;
var
  i,n,x,y,z,k:longint;
  a,p:array[1..1000000] of longint;
begin
  readln(n);
  a[1]:=0;
  p[1]:=0;
  for i:=2 to n do begin
    if i mod 3=0 then x:=a[i div 3] else x:=10000000;
    if i mod 2=0 then y:=a[i div 2] else y:=10000000;
    z:=a[i-1];
    a[i]:=min(x,min(y,z))+i;
    if a[i]=x+i then p[i]:=i div 3 else
      if a[i]=y+i then p[i]:=i div 2 else
        if a[i]=z+i then p[i]:=i-1;
  end;
  writeln(a[n]);
  k:=p[n];
  while k<>0 do begin
    if n div k=3 then write('/3 ') else
      if n div k=2 then write('/2 ') else
        if n-k=1 then write('-1 ');
    n:=p[n];
    k:=p[k];
  end;
end.