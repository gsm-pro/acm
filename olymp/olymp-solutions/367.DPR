{$APPTYPE CONSOLE}
uses math;
var
  n,kol,i,j,rn:longint;
  v:array[1..1500] of longint;
Function RingNum(x,y:longint):longint;
begin
  RingNum:=min(min(y,x-y+1),min(x,n-x+1));
end;
Function TotalRings(n:longint):longint;
var
  k:longint;
begin
  k:=1;
  while n-3*(k-1)>0 do inc(k);
  dec(k);
  TotalRings:=k;
end;
Function RingSideLen(n,k:longint):longint;
begin
  RingSideLen:=n-3*(k-1);
end;
Function TotalRingLen(n,k:longint):longint;
begin
  TotalRingLen:=3*(n-3*(k-1))-3;
end;
Procedure FillV(kol:longint);
var
  i:longint;
begin
  v[1]:=1;
  for i:=2 to kol do v[i]:=v[i-1]+TotalRingLen(n,i-1);
end;
Function NumInRing(x,y,rn:longint):longint;
var
  vpx,vpy:longint;
begin
  vpx:=2*rn-1;
  vpy:=rn;
  if vpx-x=vpy-y then NumInRing:=x-vpx+1
    else if x=n-rn+1 then NumInRing:=2*RingSideLen(n,rn)+(vpy-y)-1
      else NumInRing:=3*RingSideLen(n,rn)-2+(vpx-x);
end;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  kol:=TotalRings(n);
  FillV(kol);
  for i:=1 to n do begin
    for j:=1 to i do begin
      rn:=RingNum(i,j);
      write(v[rn]+NumInRing(i,j,rn)-1,' ');
    end;
    writeln;
  end;
end.