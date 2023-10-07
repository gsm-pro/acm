{$APPTYPE CONSOLE}
uses SysUtils;
type
  num=array[1..200000] of byte;
var
  s,v:ansistring;
  n:num;
  d,r,i,len:longint;
  z:boolean;
Procedure DivShort(var n:num;divisor:longint;var rem:longint);
var
  i:longint;
begin
  rem:=0;
  for i:=len downto 1 do begin
    rem:=rem*10+n[i];
    n[i]:=rem div divisor;
    rem:=rem mod divisor;
  end;
end;
begin
  len:=200000;
  readln(v);
  s:=copy(v,1,pos(' ',v)-1);
  d:=StrToInt(copy(v,pos(' ',v)+1,length(v)-length(s)));
  for i:=1 to length(s) do n[i]:=StrToInt(s[length(s)-i+1]);
  DivShort(n,d,r);
  z:=False;
  for i:=len downto 1 do begin
    if n[i]<>0 then z:=true;
    if z then write(n[i]);
  end;
  if not z then write('0');
  writeln;
  write(r);
end.