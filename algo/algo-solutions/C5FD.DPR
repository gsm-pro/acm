{$APPTYPE CONSOLE}
var
  a,b:array[1..10000] of longint;
  i,j,k,n:longint;
begin
  read(n);
  for i:=1 to n do begin read(a[i]);b[i]:=-1;end;
  for i:=1 to n do begin
    k:=a[i]+1;
    for j:=1 to n do begin
      if b[j]=-1 then dec(k);
      if k=0 then begin
        b[j]:=i;
        break;
      end;
    end;
  end;
  for i:=1 to n do write(b[i],' ');
end.