{$APPTYPE CONSOLE}
var
  a,b:array[1..3000] of longint;
  i,j,n,max:longint;
  z:boolean;
begin
  readln(n);
  for i:=1 to n do read(a[i]);
  b[1]:=1;
  for i:=2 to n do begin
    z:=false;
    max:=0;
    for j:=i-1 downto 1 do
      if (a[i]>a[j])and
         (
         ((odd(a[i])and(not odd(a[j])))or
         ((not odd(a[i]))and(odd(a[j]))))
         )then begin
           if b[j]>=max then max:=b[j];
           z:=true;
         end;
    if z then b[i]:=max+1 else b[i]:=1;
  end;
  max:=0;
  for i:=1 to n do if b[i]>=max then max:=b[i];
  writeln(max);
end.