Var
  f,g:text;
  n,k,i,l:longint;
  s1,s2:real;
  s:string;
begin
  assign(f,'input.txt');
  reset(f);
  readln(f,n,k);
  s1:=0;
  s2:=0;
  for i:=1 to n do begin
    readln(f,s);
    if copy(s,1,8)='Sharik: ' then s1:=s1+length(s)*k;
    if copy(s,1,8)='Matros: ' then s2:=s2+length(s)*k;
  end;
  s1:=s1/100;
  s2:=s2/100;
  close(f);
  assign(g,'output.txt');
  rewrite(g);
  writeln(g,s1:0:2,' ',s2:0:2);
  close(g);
end.