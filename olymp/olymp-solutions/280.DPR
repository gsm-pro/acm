{$APPTYPE CONSOLE}
uses math;
var
  n,i,j,q,ans,start:longint;
  l,t:array[1..100] of longint;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  for i:=1 to n do read(t[i]);
  for i:=1 to n do read(l[i]);
  for i:=1 to n-1 do
    for j:=1 to n-1 do
      if l[j]<l[j+1] then begin
        q:=l[j];l[j]:=l[j+1];l[j+1]:=q;
        q:=t[j];t[j]:=t[j+1];t[j+1]:=q;
      end;
  ans:=0;
  start:=0;
  for i:=1 to n do begin
    inc(start,t[i]);
    ans:=max(ans,start+l[i]);
  end;
  write(ans);
end.