{$APPTYPE CONSOLE}
Var
  f,g:text;
  n,m,ans,d,l,k:longint;
begin
  assign(f,'input.txt');
  reset(f);
  readln(f,n,m);
  close(f);
  ans:=0;
  for d:=1 to n do
    for l:=1 to n do begin
      k:=(n-l+1) div d;
      if (n-l+1) mod d<>0 then inc(k);
      if k>=m then inc(ans);
    end;
  if n<m then ans:=0;
  if m=0 then ans:=1;
  if m=1 then ans:=n;
  assign(g,'output.txt');
  rewrite(g);
  writeln(g,ans);
  close(g);
end.