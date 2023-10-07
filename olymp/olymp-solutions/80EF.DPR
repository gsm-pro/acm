{$APPTYPE CONSOLE}
uses Math;
var
  a,b,c:longint;
Procedure P(a,b,c:longint);
begin
  writeln('Yes');
  write(a,' ',b,' ',c);
end;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(a,b,c);
  if a*b=c then P(a,b,c) else
  if a*c=b then P(a,c,b) else
  if b*c=a then P(b,c,a) else
  write('No');
end.