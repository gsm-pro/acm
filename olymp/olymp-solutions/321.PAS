Var
  f,g:text;
  n1,n2,k,m1,m2,i:longint;
begin
  assign(f,'input.txt');
  reset(f);
  readln(f,n1,n2);
  m1:=high(longint);
  for i:=1 to n1 do begin
    read(f,k);
    if k<m1 then m1:=k;
  end;
  readln(f);
  m2:=high(longint);
  for i:=1 to n2 do begin
    read(f,k);
    if k<m2 then m2:=k;
  end;
  close(f);
  assign(g,'output.txt');
  rewrite(g);
  if m1<m2 then writeln(g,'RIGHT')
           else writeln(g,'WRONG');
  close(g);
end.