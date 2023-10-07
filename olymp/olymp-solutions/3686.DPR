{$apptype console}
uses math;
type
  el=record
    prev,inf,next:longint;
    ex:boolean;
  end;
  diag=record
    len,x,y:longint;
  end;
var
  v:array[1..5005] of el;
  d:array[1..5005] of diag;
  n,i,k,xx,yy,tt,z,tri:longint;
  ans:array[1..5005] of longint;
Procedure QSort(l,r:longint);
var
  m,i,j:longint;
  t:diag;
begin
  m:=d[(l+r) div 2].len;
  i:=l;
  j:=r;
  repeat
    while d[i].len<m do inc(i);
    while d[j].len>m do dec(j);
    if i<=j then begin
      t:=d[i];d[i]:=d[j];d[j]:=t;
      inc(i);dec(j);
    end;
  until i>j;
  if j>l then QSort(l,j);
  if i<r then QSort(i,r);
end;
Procedure Delete(x:longint);
begin
  v[v[x].prev].next:=v[x].next;
  v[v[x].next].prev:=v[x].prev;
  v[x].ex:=false;
end;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(n,k);
  for i:=1 to k do read(d[i].x,d[i].y);
  for i:=1 to k do begin
    xx:=min(d[i].x,d[i].y);
    yy:=max(d[i].x,d[i].y);
    d[i].len:=min(abs(xx-yy),n-abs(xx-yy));
    if d[i].len=n-abs(xx-yy) then begin
      tt:=xx;
      xx:=yy;
      yy:=tt;
    end;
    d[i].x:=xx;
    d[i].y:=yy;
  end;
  QSort(1,k);
  for i:=1 to n do begin
    v[i].prev:=i-1;
    v[i].inf:=i;
    v[i].next:=i+1;
    v[i].ex:=true;
  end;
  v[1].prev:=n;
  v[n].next:=1;
  tri:=0;
  for i:=1 to k do begin
    xx:=d[i].x;
    yy:=d[i].y;
    z:=1;
    while xx<>yy do begin
      inc(z);
      xx:=v[xx].next;
      if xx<>yy then delete(xx);
    end;
    inc(tri);
    ans[tri]:=z;
  end;
  z:=1;
  xx:=1;
  while v[xx].ex=false do inc(xx);
  yy:=v[xx].next;
  while xx<>yy do begin
    inc(z);
    yy:=v[yy].next;
  end;
  inc(tri);
  ans[tri]:=z;
  writeln(tri);
  for i:=1 to tri do write(ans[i],' ');
end.