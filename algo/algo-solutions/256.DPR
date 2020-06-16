{$APPTYPE CONSOLE}
var
  s,ch:string;
  p,code,a:integer;
begin
  readln(s);
  p:=pos('m',s);
  if s[p-1]='k' then begin
    ch:=copy(s,1,p-2);
    val(ch,a,code);
    writeln(a*1000);
  end else begin
    ch:=copy(s,1,p-1);
    val(ch,a,code);
    writeln(a*1609);
  end;
end.