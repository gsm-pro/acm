{$APPTYPE CONSOLE}
var
  a:array[1..300000] of longint;
  i,j,n,s,flag:longint;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(n);
  for i:=1 to n do read(a[i]);
  for i:=1 to n do a[i+n]:=a[i];
  i:=1;
  repeat
    s:=0;
    flag:=0;
    for j:=i to i+n-1 do begin
      s:=s+a[j];
      if s<=0 then begin
        flag:=j+1;
        break;
      end;
    end;
    if flag<>0 then i:=flag-1 else break;
    inc(i);
  until i>n;
  if i>n then write('NO') else begin
    writeln('YES');
    writeln(i);
  end;
end.