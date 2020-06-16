{$APPTYPE CONSOLE}
uses math;
var
  a:array[1..1000] of longint;
  n,i:longint;
  z:array[1..1000,1..1000] of longint;
Function Calc(l,r:longint):longint;
var
  p:longint;
begin
  if l>r then begin
    Calc:=0;
    exit;
  end;
  if z[l,r]<>-1 then begin
    Calc:=z[l,r];
    exit;
  end;
  if odd(l-r+n) then p:=max(Calc(l+1,r)+a[l],Calc(l,r-1)+a[r])
                else p:=min(Calc(l+1,r)-a[l],Calc(l,r-1)-a[r]);
  z[l,r]:=p;
  Calc:=p;
end;
begin
  readln(n);
  for i:=1 to n do read(a[i]);
  fillchar(z,sizeof(z),255);
  write(Calc(1,n));
end.