{$APPTYPE CONSOLE}
Var
  f,g:text;
  k,n,m,t,d:longint;
begin
  assign(f,'input.txt');
  reset(f);
  readln(f,n,k);
  close(f);
  m:=1;
  t:=0;
  if k<>1 then
    repeat
      while (m<n)and(m<k) do begin m:=m*2;inc(t);end;
      if (m<n)and(m>=k) then begin m:=m+k;inc(t);end;
    until m>=n
          else t:=n-1;
  if n=1 then t:=0;
  assign(g,'output.txt');
  rewrite(g);
  writeln(g,t);
  close(g);
end.