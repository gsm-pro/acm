{$APPTYPE CONSOLE}
uses math;
var
  a:array[1..100] of longint;
  n,i:longint;
  z:array[0..101,0..101,0..14] of longint;
Function Calc(l,r,k:longint):longint;
var
  p,k7,k14:longint;
begin
  if l>r then begin
    Calc:=0;
    exit;
  end;
  k14:=k mod 14;
  k7:=k mod 7;
  if z[l,r,k14]<>-1 then begin
    Calc:=z[l,r,k14];
    exit;
  end;
  if odd(k) then begin
    p:=max(Calc(l+1,r,k+1)+a[l],Calc(l,r-1,k+1)+a[r]);
    if (k7=0)and(r-l>=1) then begin
      p:=max(p,Calc(l+2,r,k+1)+a[l]+a[l+1]);
      p:=max(p,Calc(l,r-2,k+1)+a[r]+a[r-1]);
    end;
  end else begin
    p:=min(Calc(l+1,r,k+1)-a[l],Calc(l,r-1,k+1)-a[r]);
    if (k7=0)and(r-l>=1) then begin
      p:=min(p,Calc(l+2,r,k+1)-a[l]-a[l+1]);
      p:=min(p,Calc(l,r-2,k+1)-a[r]-a[r-1]);
    end;
  end;
  z[l,r,k14]:=p;
  Calc:=p;
end;
begin
  readln(n);
  for i:=1 to n do read(a[i]);
  fillchar(z,sizeof(z),255);
  write(Calc(1,n,1));
end.