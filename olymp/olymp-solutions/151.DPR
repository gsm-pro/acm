{$APPTYPE CONSOLE}
type
  str=string[30];
  rec=record
    x:str;
    m:longint;
  end;
var
  w:array[0..500000] of str;
  a:array[1..10000] of rec;
  i,k,kol:longint;
Procedure QSort(l,r:longint);
var
  i,j:longint;
  m,t:str;
begin
  m:=w[(l+r) div 2];
  i:=l;
  j:=r;
  repeat
    while w[i]<m do inc(i);
    while w[j]>m do dec(j);
    if i<=j then begin
      t:=w[i];
      w[i]:=w[j];
      w[j]:=t;
      inc(i);dec(j);
    end;
  until i>j;
  if j>l then QSort(l,j);
  if i<r then QSort(i,r);
end;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  kol:=0;
  while not eof do begin
    inc(kol);
    readln(w[kol]);
  end;
  QSort(1,kol);
  k:=0;
  for i:=1 to kol do
    if w[i]=w[i-1] then inc(a[k].m) else begin
      inc(k);
      a[k].m:=1;
      a[k].x:=w[i];
    end;
  for i:=1 to k do writeln(a[i].x,' ',a[i].m/kol*100:0:4);
end.