{$APPTYPE CONSOLE}
Var
  n,i,p,q,sum:longint;
  a:array[1..1001] of byte;
  s:string;
  t:array[1..10000] of longint;
Begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(n);
  fillchar(a,sizeof(a),2);
  for i:=1 to n do begin
    readln(s);
    if s='U' then a[i]:=1 else a[i]:=0;
  end;
  q:=0;
  repeat
    p:=1;
    while a[p]=a[1] do inc(p);
    dec(p);
    sum:=0;
    for i:=1 to n do inc(sum,a[i]);
    if sum=n then continue;
    inc(q);
    t[q]:=p;
    for i:=1 to p do a[i]:=(a[i]+1) mod 2;
  until p=n;
  writeln(q);
  for i:=1 to q do write(t[i],' ');
end.