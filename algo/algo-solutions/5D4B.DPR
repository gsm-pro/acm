{$APPTYPE CONSOLE}
var
  i,n:longint;
  a,b:array[0..100000] of int64;
begin
  readln(n);
  a[0]:=1;
  b[0]:=0;
  a[1]:=0;
  b[1]:=1;
  for i:=2 to n do begin
    a[i]:=a[i-1] mod 10000019+a[i-2] mod 10000019;
    b[i]:=b[i-1] mod 10000019+b[i-2] mod 10000019;
  end;
  write(a[n] mod 10000019,' ',b[n] mod 10000019);
end.