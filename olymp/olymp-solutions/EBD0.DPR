{$APPTYPE CONSOLE}
Var
  s,t:string;
  i,j,ch:longint;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(s);
  s:=s+' ';
  t:='';
  for i:=1 to 26 do
    for j:=1 to i do t:=t+chr(64+i);
  ch:=0;
  for i:=1 to length(s) do
    if s[i]='/' then begin
      if ch>0 then write(t[ch]);
      write(' ');
      ch:=0;
    end else begin
      if (s[i] in ['0'..'9']) then ch:=ch*10+(ord(s[i])-48);
      if s[i]=' ' then begin
        if ch>0 then write(t[ch]);
        ch:=0;
      end;
    end;
end.