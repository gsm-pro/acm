{$APPTYPE CONSOLE}
const
  s:array[1..10] of byte=(1,2,3,4,5,6,7,8,9,10);
Var
  n,a,b:longint;
  r:array[1..10] of byte;
  used:array[1..10] of Boolean;
Procedure rec(t:byte);
var
  j,k,w:longint;
Begin
  if t=n+1 then begin
    w:=0;
    for j:=1 to n do w:=w+r[j]*j;
    if (w>=a)and(w<=b) then begin
      for k:=1 to n do write(r[k],' ');
      writeln;
    end;
    exit;
  end;
  for j:=1 to n do
    if used[j] then begin
      r[t]:=s[j];
      used[j]:=false;
      rec(t+1);
      used[j]:=true;
    end;
end;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n,a,b);
  fillchar(used,sizeof(used),true);
  rec(1);
end.