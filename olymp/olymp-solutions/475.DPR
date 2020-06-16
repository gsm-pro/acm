{$APPTYPE CONSOLE}
type
  data=record
    a,b,c,d,p:longint;
  end;
Var
  f,g:text;
  x:array[1..101] of data;
  i,n,k1,k2,res:longint;
begin
  assign(f,'input.txt');
  reset(f);
  readln(f,n);
  for i:=1 to n do begin
    readln(f,x[i].a,x[i].b,x[i].c,x[i].d);
    x[i].p:=(20*x[i].b+x[i].a)-(20*x[i].d+x[i].c);
  end;
  close(f);
  x[n+1]:=x[1];
  res:=-100000000;
  for i:=1 to n do
    if x[i].p+x[i+1].p>res then begin
      res:=x[i].p+x[i+1].p;
      k1:=i;
      k2:=i+1;
    end;
  if k2=n+1 then k2:=1;  
  assign(g,'output.txt');
  rewrite(g);
  writeln(g,k1,' ',k2);
  close(g);
end.