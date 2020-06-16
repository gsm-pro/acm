{$apptype console}
var
  n,m,i,j,d,t,c,s:longint;
  g:array[1..50,1..50] of longint;
  p:array[1..20001] of longint;
procedure rec(s:longint);
var
  i:longint;
begin
  for i:=1 to n do begin
    if g[s,i]>0 then begin
      dec(g[i,s]);
      dec(g[s,i]);
      rec(i);
    end;
  end;
  inc(t);
  p[t]:=s;
end;
begin
  read(n,m);
  for t:=1 to m do begin
    read(i,j);
    inc(g[i,j]);
    inc(g[j,i]);
  end;
  t:=0;
  s:=0;
  c:=0;
  for i:=1 to n do begin
    d:=0;
    for j:=1 to n do inc(d,g[i,j]);
    if d and 1=1 then begin
      inc(c);
      s:=i;
    end;
    if (s=0)and(d>0) then s:=i;
  end;
  if (c=0)or(c=2) then rec(s);
  if t<>m+1 then write(-1) else begin
    writeln(t);
    for i:=1 to t do write(p[i],' ');
  end;
end.