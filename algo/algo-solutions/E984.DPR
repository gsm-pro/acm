{$APPTYPE CONSOLE}
var
  a:array[0..60] of longint;
  i,j,t,n,p:longint;
begin
  readln(n);
  for i:=1 to n do read(a[i]);
  if n=1 then begin
    writeln(a[1]);
    halt(0);
  end;  
  for i:=1 to n-1 do
    for j:=1 to n-1 do
      if a[j]>a[j+1] then begin
        t:=a[j];
        a[j]:=a[j+1];
        a[j+1]:=t;
      end;
  i:=1;
  a[0]:=-50;
  repeat
    p:=i;
    if a[p]=a[i-1]+1 then while (a[p]=a[i-1]+1)and(p<n) do inc(p);
    t:=a[i];
    a[i]:=a[p];
    a[p]:=t;
    inc(i);
  until i=n;
  for j:=n downto 1 do
    for i:=n downto 2 do
      if a[i]=a[i-1]+1 then begin
        t:=a[i];
        a[i]:=a[i-1];
        a[i-1]:=t;
      end;
  for i:=1 to n do write(a[i],' ');
end.