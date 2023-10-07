{$APPTYPE CONSOLE}
type
  rec=record
    p,t:longint;
    q:boolean;
  end;
var
  z:array[1..1000000] of rec;
  i,n,k,m,j:longint;
begin
  read(n);
  for i:=1 to n do begin
    z[i].p:=i-1;
    z[i].t:=i+1;
    if i=1 then z[i].p:=n;
    if i=n then z[i].t:=1;
    z[i].q:=True;
  end;
  m:=1;
  for i:=1 to n-1 do begin
    read(k);
    if k>0 then for j:=1 to k do m:=z[m].t;
    if k<0 then for j:=1 to abs(k) do m:=z[m].p;
    writeln(m);
    z[m].q:=False;
    z[z[m].p].t:=z[m].t;
    z[z[m].t].p:=z[m].p;
    while z[m].q=False do m:=z[m].t;
    if k<0 then m:=z[m].p;
  end;
  write(m);
end.