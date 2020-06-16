{$APPTYPE CONSOLE}
var
  z:array[-1000002..1000002] of longint;
  i,n,k1,k2,kol,nasl,maxnasl:longint;
begin
  readln(n);
  for i:=1 to n do begin
    read(k1,k2);
    inc(z[k1]);
    dec(z[k2+1]);
  end;
  nasl:=0;
  kol:=1;
  maxnasl:=-1;
  for i:=-1000002 to 1000002 do begin
    inc(nasl,z[i]);
    if nasl=maxnasl then inc(kol);
    if nasl>maxnasl then begin
      maxnasl:=nasl;
      kol:=1;
    end;
  end;
  write(kol);
end.