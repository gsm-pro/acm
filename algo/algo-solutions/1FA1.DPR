{$apptype console}
uses Math;
const
  p=1000003;
  d=31;
var
 s:string;
 n,a:longint;
procedure rec(v,t:longint);
begin
  a:=max(a,t);
  if v>n then exit;
  rec(v+1,t);
  rec(v+1,(t*d+ord(s[v])) mod p);
end;
begin
  readln(s);
  n:=length(s);
  a:=0;
  rec(1,0);
  write(a);
end.