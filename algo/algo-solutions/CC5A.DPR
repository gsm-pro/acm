{$APPTYPE CONSOLE}
var
  ans:int64;
  i,n,k:byte;
  a:array[1..18] of byte;
Procedure Rec(p,r:byte);
var
  i:byte;
begin
  if r=0 then begin
    for i:=1 to n do if a[i]=1 then write(i,' ');
    writeln;
    exit;
  end;
  for i:=p to n do begin
    a[i]:=1;
    Rec(i+1,r-1);
    a[i]:=0;
  end;
end;
begin
  read(n,k);
  ans:=1;
  for i:=n downto n-k+1 do ans:=ans*i;
  for i:=1 to k do ans:=ans div i;
  writeln(ans);
  Rec(1,k);
end.