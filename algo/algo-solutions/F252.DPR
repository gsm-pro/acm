{$APPTYPE CONSOLE}
var
  s:string;
  k,i:longint;
  a:array[1..26] of longint;
begin
  readln(s);
  for i:=1 to length(s) do inc(a[ord(s[i])-96]);
  k:=0;
  for i:=1 to 26 do if a[i]<>0 then inc(k);
  write(k);
end.