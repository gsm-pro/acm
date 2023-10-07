{$APPTYPE CONSOLE}
Var
  f,g:text;
  a:array[1..15000] of longint;
  i,n,d,q,r:longint;
  z:array[1..15000] of boolean;
Procedure QSort(left,right:longint);
var
  m,i,j,t:longint;
begin
  m:=a[(left+right) div 2];
  i:=left;
  j:=right;
  repeat
    while a[i]<m do inc(i);
    while a[j]>m do dec(j);
    if i<=j then begin
      t:=a[i];
      a[i]:=a[j];
      a[j]:=t;
      inc(i);
      dec(j);
    end;
  until i>j;
  if j>left then QSort(left,j);
  if i<right then QSort(i,right);
end;
begin
  assign(f,'input.txt');
  reset(f);
  readln(f,n,d);
  for i:=1 to n do read(f,a[i]);
  close(f);
  QSort(1,n);
  q:=0;
  r:=n;
  i:=0;
  repeat
    inc(i);
    if i>=r then break;
    while (r>=i)and(a[i]+a[r]>d) do dec(r);
    if (r>0)and(a[i]+a[r]<=d) then begin
      inc(q);
      z[i]:=true;
      z[r]:=true;
      dec(r);
    end;
  until false;
  for i:=1 to n do if not z[i] then inc(q);
  assign(g,'output.txt');
  rewrite(g);
  writeln(g,q);
  close(g);
end.