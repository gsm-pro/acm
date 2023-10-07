{H+,Q-,R-}
{$APPTYPE CONSOLE}
uses SysUtils;
Var
  s,t:string;
  i:longint;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(s);
  s:=LowerCase(s);
  s:=' '+s;
  for i:=2 to length(s) do
    if (s[i-1] in [' ','.',','])and(s[i] in ['a'..'z']) then s[i]:=chr(ord(s[i])-ord('a')+65);
  t:='';
  for i:=1 to length(s) do if s[i]<>' ' then t:=t+s[i];
  s:=t;
  if s='' then halt(0);
  i:=1;
  repeat
    if s[i] in ['A'..'Z'] then begin
      insert(' ',s,i);
      inc(i);
    end;
    inc(i);
  until i>length(s);
  s:=LowerCase(s);
  s:=Trim(s);
  for i:=1 to length(s) do
    if (i=1)or((s[i-2]='.')and(s[i] in ['a'..'z'])) then s[i]:=chr(ord(s[i])-ord('a')+65);
  write(s);
end.