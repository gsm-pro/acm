{$APPTYPE CONSOLE}
uses SysUtils;
const
  I=9999;
Var
  s,t:string;
  a,b:longint;
Begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(s);
  readln(t);
  a:=StrToIntDef(s,I);
  b:=StrToIntDef(t,I);
  if (a=I)and(b=I) then write('INF') else
  if ((a=I)and(b=1))or((a=1)and(b=I)) then write('INF') else
  if (a=3)and(b=3) then write(2) else
  if (a=1)and(b<>I) then write(b) else
  if (a<>I)and(b=1) then write(a) else
  if (a=2)or(b=2) then write(4) else
  write(1);
end.