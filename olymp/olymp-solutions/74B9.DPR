{$APPTYPE CONSOLE}
uses math;
const
  INF=1000000000;
var
  a:array[1..100,1..100] of longint;
  minans,ans,i,j,k,n,m,v1,v2,d,p1,p2:longint;
  ppl:array[1..100] of longint;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n,m);
  for i:=1 to n do read(ppl[i]);
  for i:=1 to n do for j:=1 to n do a[i,j]:=INF;
  for i:=1 to m do begin
    read(v1,v2,d);
    a[v1,v2]:=d;
    a[v2,v1]:=d;
  end;
  for k:=1 to n do
    for i:=1 to n do
      for j:=1 to n do
        if a[i,k]+a[k,j]<a[i,j] then a[i,j]:=a[i,k]+a[k,j];
  for i:=1 to n do a[i,i]:=0;
  p1:=0;
  p2:=0;
  minans:=INF;
  for i:=1 to n do
    for j:=1 to n do begin
      ans:=0;
      for k:=1 to n do inc(ans,ppl[k]*min(a[k,i],a[k,j]));
      if ans<minans then begin
        minans:=ans;
        p1:=i;
        p2:=j;
      end;
    end;
  writeln(minans);
  write(p1,' ',p2);
end.