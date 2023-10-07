{$APPTYPE CONSOLE}
label lb;
var
  f,g:text;
  s:string;
  x1,y1,x2,y2:array[1..110] of longint;
  t,i,j,kol,n,x,y:longint;
begin
  assign(f,'input.txt');
  reset(f);
  readln(f,s);
  close(f);
  n:=length(s);
  x:=0;
  y:=0;
  kol:=0;
  t:=0;
  for i:=1 to n do begin
    inc(kol);
    x1[kol]:=x;
    y1[kol]:=y;
    if s[i]='S' then dec(y);
    if s[i]='N' then inc(y);
    if s[i]='W' then dec(x);
    if s[i]='E' then inc(x);
    x2[kol]:=x;
    y2[kol]:=y;
    for j:=1 to i-1 do
      if((x1[kol]=x2[j])and(y1[kol]=y2[j])and
         (x2[kol]=x1[j])and(y2[kol]=y1[j]))or
        ((x1[kol]=x1[j])and(y1[kol]=y1[j])and
         (x2[kol]=x2[j])and(y2[kol]=y2[j]))then begin
          inc(t);
          goto lb;
        end;
    inc(t,5);
    lb:
  end;
  assign(g,'output.txt');
  rewrite(g);
  writeln(g,t);
  close(g);
end.