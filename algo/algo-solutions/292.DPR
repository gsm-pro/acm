{$APPTYPE CONSOLE}
const
  nmax=100;
type
  pair=record
    first,second:longint;
  end;
var
  d:array[1..nmax,1..nmax] of pair;
  was:array[1..nmax,1..nmax] of boolean;
  a:array[1..nmax] of longint;
  n,i:longint;
Function Calc(i,j:longint):pair;
var
  w,g:pair;
begin
  if j=n+1 then begin
    g.first:=0;
    g.second:=0;
    Calc:=g;
    exit;
  end;
  if was[i,j] then begin
    Calc:=d[i,j];
    exit;
  end;
  was[i,j]:=true;
  w.first:=-1;
  w.second:=-1;
  g.first:=-1;
  g.second:=-1;
  if i<=n then begin
    w:=calc(i+1,j);
    inc(w.second,a[i]);
  end;
  if j<i then begin
    g:=Calc(i,j+1);
    inc(g.second,(a[j]*a[j]) mod 1000);
  end;
  if (w.second>g.second)or((w.second=g.second)and(w.first<g.first)) then begin
    d[i,j].first:=w.second;
    d[i,j].second:=w.first;
  end else begin
    d[i,j].first:=g.second;
    d[i,j].second:=g.first;
  end;
  Calc:=d[i,j];
end;
begin
  read(n);
  for i:=1 to n do read(a[i]);
  fillchar(d,sizeof(d),255);
  writeln(Calc(1,1).first,' ',Calc(1,1).second);
end.