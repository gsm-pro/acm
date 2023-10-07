{$APPTYPE CONSOLE}
var
  m,n,z,i,t:longint;
  a,b:array[1..1000] of longint;
begin
  read(m);
  for z:=1 to m do begin
    read(n);
    fillchar(b,sizeof(b),0);
    for i:=1 to n do begin
      read(a[i]);
      inc(b[a[i]]);
    end;
    t:=0;
    for i:=1 to n do if b[i]<>1 then begin
      writeln('No');
      t:=1;
      break;
    end;
    if t=0 then writeln('Yes');
  end;
end.