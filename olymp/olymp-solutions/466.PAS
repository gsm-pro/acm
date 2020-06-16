Var
  f,g:text;
  n,s:longint;
Function SummaCifr(n:longint):longint;
var
  a,sum:longint;
begin
  sum:=0;
  while n<>0 do begin
    a:=n mod 10;
    inc(sum,a);
    n:=n div 10;
  end;
  SummaCifr:=sum;
end;
begin
  assign(f,'input.txt');
  reset(f);
  readln(f,n);
  close(f);
  s:=SummaCifr(n);
  while s>=10 do s:=SummaCifr(s);
  assign(g,'output.txt');
  rewrite(g);
  writeln(g,s);
  close(g);
end.