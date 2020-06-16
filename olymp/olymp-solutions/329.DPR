{$apptype console}
uses SysUtils;
var
  s,s1,s2:string;
  k,m,chisl,znam,i,nod:longint;
Function gcd(a,b:longint):longint;
begin
  if b=0 then gcd:=a else gcd:=gcd(b,a mod b);
end;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(s);
  k:=pos(')',s)-pos('(',s)-1;
  m:=pos('(',s)-pos(',',s)-1;
  s1:=s;
  if pos(',',s1)<>0 then delete(s1,pos(',',s1),1);
  if pos('(',s1)<>0 then delete(s1,pos('(',s1),1);
  if pos(')',s1)<>0 then delete(s1,pos(')',s1),1);
  s2:=copy(s,1,pos('(',s));
  if pos('(',s2)<>0 then delete(s2,pos('(',s2),1);
  if pos(',',s2)<>0 then delete(s2,pos(',',s2),1);
  chisl:=StrToInt(s1)-StrToInt(s2);
  znam:=0;
  for i:=1 to k do znam:=znam*10+9;
  for i:=1 to m do znam:=znam*10;
  nod:=gcd(chisl,znam);
  write(chisl div nod,'/',znam div nod);
end.