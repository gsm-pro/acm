{$APPTYPE CONSOLE}
var
  f,g:text;
  n,w:int64;
  i:longint;
  a:array[1..100] of int64;
Function _2x(x:longint):int64;
var
  i:longint;
  v:int64;
begin
  v:=1;
  for i:=1 to x do v:=v*2;
  _2x:=v;
end;
begin
  assign(f,'input.txt');
  reset(f);
  readln(f,n);
  close(f);
  a[1]:=2;
  a[2]:=3;
  a[3]:=3;
  w:=1;
  i:=3;
  repeat
    inc(i);
    a[i]:=a[i-2]+_2x(w);
    inc(i);
    a[i]:=a[i-2]+_2x(w);
    inc(w);
  until i=71;
  assign(g,'output.txt');
  rewrite(g);
  if n=0 then writeln(g,'2') else writeln(g,a[n]);
  close(g);
end.