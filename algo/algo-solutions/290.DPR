{$APPTYPE CONSOLE}
var
  _m:array[-200..1000000] of boolean;
  i,n,m,j,t:longint;
  a:array[1..10] of longint;
  b:boolean;
begin
  readln(n,m);
  for i:=1 to n do read(a[i]);
  for i:=-200 to -1 do _m[i]:=True;
  _m[0]:=False;
  for i:=1 to n do _m[a[i]]:=True;
  if n<>1 then
    for i:=1 to m do begin
      if _m[i] then continue;
      b:=True;
      for j:=1 to n do b:=b and _m[i-a[j]];
      if b then _m[i]:=False else _m[i]:=True;
    end else begin
      t:=m div a[1];
      if odd(t) then begin
        writeln('FIRST');
        writeln('1');
      end else writeln('SECOND');
      halt;
    end;  
  if _m[m] then begin
    writeln('FIRST');
    for i:=1 to n do if not _m[m-a[i]] then begin
      writeln(i);
      break;
    end;
  end else writeln('SECOND');
end.