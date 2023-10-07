{$APPTYPE CONSOLE}
Var
  f,g:text;
  a,p:array[1..1000] of longint;
  i,n,d,k1,k2:longint;
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
      t:=p[i];
      p[i]:=p[j];
      p[j]:=t;
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
  readln(f,n);
  for i:=1 to n do read(f,a[i]);
  close(f);
  for i:=1 to n do p[i]:=i;
  QSort(1,n);
  d:=high(longint);
  for i:=2 to n do
    if abs(a[i-1]-a[i])<d then begin
      d:=abs(a[i-1]-a[i]);
      k1:=p[i-1];
      k2:=p[i];
    end;
  assign(g,'output.txt');
  rewrite(g);
  writeln(g,d);
  writeln(g,k1,' ',k2);
  close(g);
end.