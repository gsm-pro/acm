{$APPTYPE CONSOLE}
var
  a:array[0..10000] of longint;
  used:array[0..10000] of boolean;
  ans,i,v,n:longint;
begin
  read(n);
  for i:=0 to n-1 do read(a[i]);
  for i:=0 to n-1 do dec(a[i]);
  for i:=0 to n-1 do used[i]:=false;
  ans:=0;
  for i:=0 to n-1 do
    if not used[i] then begin
      inc(ans);
      v:=i;
      while not used[v] do begin
        used[v]:=true;
        v:=a[v];
      end;
    end;
  writeln(n-ans);
end.