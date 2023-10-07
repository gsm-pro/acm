Var
  f,g:text;
  i,n,maxp,tekp,v,a:longint;
  s,t:string;
  w:char;
  code,z:integer;
Function P(x:longint):longint;
var
  a,m:longint;
begin
  m:=1;
  while x<>0 do begin
    a:=x mod 10;
    m:=m*a;
    x:=x div 10;
  end;
  P:=m;
end;
begin
  assign(f,'input.txt');
  reset(f);
  readln(f,n);
  close(f);
  str(n,s);
  v:=length(s);
  z:=pos('0',s);
  if z<>0 then begin
    for i:=z to v do s[i]:='9';
    t:=s[z-1];
    val(t,a,code);
    a:=a-1;
    str(a,t);
    delete(s,z-1,1);
    insert(t,s,z-1);
    val(s,n,code);
  end;
  maxp:=1;
  tekp:=P(n);
  if tekp>maxp then maxp:=tekp;
  for i:=1 to v-1 do begin
    t:=s[length(s)-i];
    val(t,a,code);
    a:=a-1;
    str(a,t);
    delete(s,length(s)-i,1);
    insert(t,s,length(s)-i+1);
    s[length(s)-i+1]:='9';
    val(s,a,code);
    tekp:=P(a);
    if tekp>maxp then maxp:=tekp;
  end;
  assign(g,'output.txt');
  rewrite(g);
  writeln(g,maxp);
  close(g);
end.