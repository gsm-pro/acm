Var
  f,g:text;
  c:char;
  k,i:longint;
begin
  assign(f,'input.txt');
  reset(f);
  assign(g,'output.txt');
  rewrite(g);
  k:=0;
  repeat
    read(f,c);
    if c='!' then inc(k);
    if c=#13 then begin writeln(g,k);k:=0;end;
  until eof(f);
  writeln(g,k);
  close(f);
  close(g);
end.