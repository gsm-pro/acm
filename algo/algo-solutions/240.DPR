{$APPTYPE CONSOLE}
var
  a:string[30];
  l,i,j:longint;
  z:array[0..30] of longint;
begin
  readln(a);
  l:=length(a);
  z[0]:=1;
  for i:=1 to l do begin
    j:=i-1;
    while (j>0)and(a[j]<>a[i]) do dec(j);
    if j<>0 then z[i]:=z[i-1]*2-z[j-1]
            else z[i]:=z[i-1]*2;
  end;
  write(z[l]);
end.