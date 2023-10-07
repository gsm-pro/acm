{$APPTYPE CONSOLE}
var
  m,n,i,r,rmin,q,sum1,sum2,sum:longint;
  w:array[0..15001] of word;
Procedure QSort(l,r:longint);
var
  m,i,j,t:longint;
begin
  m:=w[(l+r) div 2];
  i:=l;
  j:=r;
  repeat
    while w[i]<m do inc(i);
    while w[j]>m do dec(j);
    if i<=j then begin
      t:=w[i];w[i]:=w[j];w[j]:=t;
      inc(i);dec(j);
    end;
  until i>j;
  if j>l then QSort(l,j);
  if i<r then QSort(i,r);
end;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n,m);
  sum:=0;
  for i:=1 to n do begin
    read(w[i]);
    inc(sum,w[i]);
  end;
  QSort(1,n);
  rmin:=1000000000;
  w[n+1]:=50000;
  q:=0;
  sum1:=0;
  for i:=w[1] to w[n] do begin
    while w[q+1]<=i do begin inc(q);inc(sum1,w[q]);end;
    sum2:=sum-sum1;
    r:=(q*i-sum1)+((n-q)*(i+m+1)-sum2);
    if r<rmin then rmin:=r;
  end;
  write(rmin);
end.