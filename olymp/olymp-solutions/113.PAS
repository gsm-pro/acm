Var
  f,g:text;
  n,i,best,r,t,code:integer;
  s:string;
  p:char;
begin
  assign(f,'input.txt');
  reset(f);
  readln(f,n);
  best:=0;
  for i:=1 to n do begin
    s:='';
    readln(f,s);
    val(copy(s,1,length(s)-1),r,code);
    p:=s[length(s)];
    if p='s' then r:=r*10;
    if r>best then best:=r;
  end;
  close(f);
  assign(g,'output.txt');
  rewrite(g);
  writeln(g,best);
  close(g);
end.