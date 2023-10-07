{$APPTYPE CONSOLE}
Var
  m,i,n:longint;
  s:string;
  r:String;
  used:Array[1..9] of Boolean;
Procedure rec(t:byte);
var
  j,k:byte;
Begin
  if t=n+1 then begin
    for k:=1 to n do write(r[k],' ');
    writeln;
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
  read(n);
  m:=1;
  for i:=1 to n do m:=m*i;
  writeln(m);
  fillchar(used,sizeof(used),true);
  s:='123456789';
  r:=s;
  rec(1);
end.