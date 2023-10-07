{$APPTYPE CONSOLE}
uses Math,sysutils;
var
  s:string;
  a:array[1..1000] of longint;
  i,j,n,t:longint;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(s);
  if s='0' then begin
    write(0);
    halt(0);
  end;
  n:=length(s);
  for i:=1 to n do a[i]:=StrToInt(s[i]);
  for i:=1 to n-1 do
    for j:=1 to n-1 do
      if a[j]<a[j+1] then begin
        t:=a[j];
        a[j]:=a[j+1];
        a[j+1]:=t;
      end;
  i:=n;
  while a[i]=0 do dec(i);
  t:=a[n];
  a[n]:=a[i];
  a[i]:=t;
  for i:=n downto 1 do write(a[i]);
end.