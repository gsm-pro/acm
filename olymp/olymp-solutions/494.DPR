{$APPTYPE CONSOLE}
var
  a,b,c,d,ans:array[0..10000] of longint;
  n,i,j,k,s,t,k1,k2:longint;
  net:boolean;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(t,n);
  for i:=1 to n do read(a[i]);
  s:=0;
  for i:=1 to n do inc(s,a[i]);
  k:=s div 2;
  b[0]:=0;
  for i:=1 to s do b[i]:=-1;
  for i:=1 to n do
    for j:=0 to s-a[i] do
      if (b[j]<>-1)and(b[j]<>i)and(b[j+a[i]]=-1)then b[j+a[i]]:=i;
  while (b[k]=-1)and(k>0) do dec(k);
  k1:=0;
  while (k>0) do  begin
    inc(k1);
    c[k1]:=b[k];
    k:=k-a[b[k]];
  end;
  k2:=0;
  for i:=1 to n do begin
    net:=True;
    for j:=1 to k1 do if c[j]=i then net:=net and False;
    if net then begin inc(k2);d[k2]:=i;end;
  end;
  t:=0;
  for i:=1 to k1 do begin
    ans[c[i]]:=t;
    inc(t,a[c[i]]);
  end;
  t:=0;
  for i:=1 to k2 do begin
    ans[d[i]]:=t;
    inc(t,a[d[i]]);
  end;
  for i:=1 to n do write(ans[i],' ');
end.