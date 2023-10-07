{$APPTYPE CONSOLE}
uses Math;
var
  t1,t,t2:longint;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(t1,t2,t);
  if (t>=min(t1,t2))and(t<=max(t1,t2))
    then write('YES')
    else write('NO');
end.