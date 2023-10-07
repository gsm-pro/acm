{$APPTYPE CONSOLE}
var
  i,n,k:longint;
  a:array[1..20] of longint;
  x,y:array[1..100000] of longint;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n,k);
  for i:=1 to k do read(a[i]);
  if k=1 then write(a[1]*n) else
    if a[1]*n<a[k] then write(0) else begin
      for i:=1 to n do x[a[1]*i]:=1;
      for i:=1 to n do y[a[k]*i]:=1;
      for i:=100000 downto 1 do if x[i]+y[i]=2 then begin
        write(i);
        break;
      end;
  end;
end.