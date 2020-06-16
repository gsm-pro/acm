Var
  f,g:text;
  a:array[1..100] of byte;
  i,n,z,p,d,m:byte;
  s:string[100];
Procedure Find(var p,d:byte);
var
  ps:byte;
  u:string;
begin
  u:=' ';
  ps:=1;
  while pos(u,s)<>0 do begin
    ps:=pos(u,s);
    u:=u+' ';
  end;
  p:=ps;
  d:=length(u)-1;
end;
begin
  assign(f,'input.txt');
  reset(f);
  readln(f,n);
  close(f);
  s:='';
  for i:=1 to n do s:=s+' ';
  for z:=1 to n do begin
    Find(p,d);
    m:=(2*p+d-1) div 2;
    a[m]:=z;
    s[m]:='-';
  end;
  assign(g,'output.txt');
  rewrite(g);
  for i:=1 to n do write(g,a[i],' ');
  close(g);
end.