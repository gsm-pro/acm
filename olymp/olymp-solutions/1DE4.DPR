{$APPTYPE CONSOLE}
var
  f,g:text;
  n,i,q,m,z:longint;
  a:array[1..60] of int64;
  c:char;
Procedure Letter(n,m:longint);
begin
  if (n<=3) then begin
    if (n<>1)and(m=n) then c:='B' else c:='A';
    exit;
  end;
  if m<=a[n-2] then Letter(n-2,m);
  if c<>'X' then exit;
  if (m>a[n-2])and(m<=a[n-2]+a[n-3]) then Letter(n-3,m-a[n-2]);
  if c<>'X' then exit;
  if m>a[n-2]+a[n-3] then Letter(n-2,m-a[n-2]-a[n-3]);
  if c<>'X' then exit;
end;
begin
  a[1]:=1;
  a[2]:=2;
  for i:=3 to 60 do a[i]:=a[i-1]+a[i-2];
  assign(f,'input.txt');
  reset(f);
  assign(g,'output.txt');
  rewrite(g);
  readln(f,q);
  for z:=1 to q do begin
    readln(f,m,n);
    if m>a[n] then begin
      writeln(g,'No solution');
      continue;
    end;
    c:='X';
    Letter(n,m);
    writeln(g,c);
  end;
  close(f);
  close(g);
end.