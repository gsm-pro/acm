{$APPTYPE CONSOLE}
uses SysUtils;
Var
  a,b,s,v,w:string;
  i,p,c,ost,pr,n,j:longint;
Begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(a);
  readln(b);
  readln(p);
  if b='0' then halt(0);
  for i:=1 to 255-length(a) do a:='0'+a;
  for i:=1 to 255-length(b) do b:='0'+b;
  s:='';
  for i:=1 to 255 do s:=s+'0';
  ost:=0;
  for i:=255 downto 1 do begin
    c:=(ord(a[i])-48)+(ord(b[i])-48)+ost;
    ost:=c div 10;
    c:=c mod 10;
    s[i]:=chr(c+48);
  end;
  p:=length(s)-p+1;
  v:=copy(a,p+1,length(a)-p);
  w:=copy(s,p+1,length(s)-p);
  if v<>w then begin
    write('No solution');
    halt(0);
  end;
  pr:=1;
  for i:=1 to 255 do if copy(a,1,i)<>copy(s,1,i) then begin
    pr:=i;
    break;
  end;
  for i:=p downto pr do begin
    n:=StrToInt(s[i])-StrToInt(a[i]);
    if n<0 then inc(n,10);
    for j:=1 to n do writeln('+');
    if i<>pr then writeln('move');
  end;
end.