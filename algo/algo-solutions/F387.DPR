{$APPTYPE CONSOLE}
uses math;
Var
  x,y:array[1..3] of longint;
  a,b,c:array[1..6] of int64;
  k,i,j,d:longint;
Function GCD(a,b:longint):longint;
begin
  if a mod b=0 then GCD:=b else GCD:=GCD(b,a mod b);
end;
begin
  for i:=1 to 3 do read(x[i],y[i]);
  if ((x[1]=x[2])and(y[1]=y[2]))or
     ((x[1]=x[3])and(y[1]=y[3]))or
     ((x[3]=x[2])and(y[3]=y[2]))then begin
       write('YES');
       halt(0);
     end;
  k:=0;
  for i:=1 to 2 do
    for j:=i+1 to 3 do begin
      inc(k);
      a[k]:=y[j]-y[i];
      b[k]:=x[i]-x[j];
      if b[k]<>0 then d:=GCD(a[k],b[k]) else d:=a[k];
      if d=0 then d:=1;
      a[k]:=a[k] div d;
      b[k]:=b[k] div d;
      c[k]:=-a[k]*x[i]-b[k]*y[i];
    end;
  if (a[1]=a[2])and(a[2]=a[3])and
     (b[1]=b[2])and(b[2]=b[3])and
     (c[1]=c[2])and(c[2]=c[3]) then write('YES') else write('NO');
end.