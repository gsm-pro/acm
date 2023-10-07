{$APPTYPE CONSOLE}
uses Math;
var
  n,i,x:longint;
  z:array[1..6000000,1..4] of word;
  s:string;
  w:array[1..10] of longint = (2,13,47,341,2419,16811,117643,823611,1754803,8053607);
Function getHash(a:string):longint;
var
  i:longint;
  q:longint;
begin
  q:=0;
  for i:=1 to length(a) do
    q:=(q+(ord(a[i])-61)*w[i]) mod 5011001;
  getHash:=(q+5011001) mod 5011001;
end;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(n);
  for i:=1 to n do begin
    readln(s);
    s:=copy(s,2,length(s)-1);
    x:=getHash(s);
    if z[x,1]<>0 then writeln('Disconnected #',z[x,1]);
    z[x,1]:=z[x,2];
    z[x,2]:=z[x,3];
    z[x,3]:=z[x,4];
    z[x,4]:=i;
  end;
end.