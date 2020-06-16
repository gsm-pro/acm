{$APPTYPE CONSOLE}
Var
  f,g:text;
  s,ch,m,x:ansistring;
  p1,p2,i,kol,code:integer;
begin
  assign(f,'input.txt');
  reset(f);
  readln(f,s);
  close(f);
  while true do begin
    p1:=length(s);
    while (p1>=1)and(s[p1]<>'(') do dec(p1);
    if p1=0 then break;
    p2:=p1+1;
    while (p2<=length(s))and(s[p2]<>')') do inc(p2);
    i:=p1+1;
    ch:='';
    while s[i] in ['0'..'9'] do begin ch:=ch+s[i];inc(i);end;
    m:=copy(s,i,p2-i);
    delete(s,p1,p2-p1+1);
    x:='';
    val(ch,kol,code);
    for i:=1 to kol do x:=x+m;
    insert(x,s,p1);
  end;
  assign(g,'output.txt');
  rewrite(g);
  write(g,s);
  close(g);
end.