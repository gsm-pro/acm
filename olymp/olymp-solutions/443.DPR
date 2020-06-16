{$APPTYPE CONSOLE}
Var
  f,g:text;
  n,i,x,y,kol,t:longint;
begin
  assign(f,'input.txt');
  reset(f);
  readln(f,n);
  close(f);
  kol:=0;
  for i:=1 to n-1 do begin
    x:=i;
    y:=n-i;
    inc(kol);
    while x<y do begin
      t:=x;
      x:=y-x;
      y:=t;
      if (x<=0)or(y<=0) then break;
      inc(kol);
    end;
  end;
  assign(g,'output.txt');
  rewrite(g);
  write(g,kol);
  close(g);
end.