Var
  f,g:text;
  a,b,c,p:longint;
  s,sa,sb,z:string[30];
  code:integer;
begin
  assign(f,'input.txt');
  reset(f);
  readln(f,s);
  close(f);
  delete(s,length(s),1);
  p:=pos('+',s);
  if p=0 then p:=pos('-',s);
  if p=0 then p:=pos('*',s);
  if p=0 then p:=pos('/',s);
  sa:=copy(s,1,p-1);
  z:=s[p];
  sb:=copy(s,p+1,length(s)-p);
  val(sa,a,code);
  val(sb,b,code);
  if z='+' then c:=a+b;
  if z='-' then c:=a-b;
  if z='*' then c:=a*b;
  if z='/' then c:=a div b;
  assign(g,'output.txt');
  rewrite(g);
  write(g,c);
  close(g);
end.