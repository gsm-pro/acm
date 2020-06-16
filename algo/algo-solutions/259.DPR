{$APPTYPE CONSOLE}
var
  s:string;
  v,i:integer;
  b:boolean;
begin
  readln(s);
  v:=length(s);
  b:=True;
  for i:=1 to v do
    if (ord(s[i]) in [48..57])or
       (ord(s[i]) in [65..90])or
       (ord(s[i]) in [97..122])or(ord(s[i])=95) then else begin
         b:=False;
         break;
       end;
  if (b=True)and((s[1]<'0')or(s[1]>'9')) then write('YES')
                                         else write('NO');
end.