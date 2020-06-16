{$APPTYPE CONSOLE}
var
  n,k,s:longint;
  a:array[1..50] of byte;
Procedure Push(x:longint);begin inc(k);a[k]:=x;end;
Procedure Pop;begin dec(k);end;
Procedure Print;
var
  i:longint;
begin
  write(a[1]);
  for i:=2 to k do write('+',a[i]);
  writeln;
end;
Procedure Rec(x,pred:longint);
var
  i:longint;
begin
  if s>n then exit;
  if s=n then begin
    Print;
    exit;
  end;
  for i:=pred downto 1 do begin
    Push(i);
    inc(s,i);
    Rec(x-i,i);
    dec(s,i);
    Pop;
  end;
end;
begin
  read(n);
  k:=0;
  s:=0;
  Rec(n,n);
end.