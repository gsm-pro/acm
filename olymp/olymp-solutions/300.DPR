{$APPTYPE CONSOLE}
uses SysUtils;
var
  s,t,a,ans:string[11];
  l,x:longint;
  f,g:text;
Procedure Rec(n:longint);
var
  i,v:longint;
  c:char;
begin
  if (n=l+1)and(ans<a) then begin
    v:=StrToInt(a);
    if v<=x then begin
      ans:=a;
      exit;
    end;  
  end;
  for i:=1 to l do begin
    c:=s[i];
    if c='A' then continue;
    a:=a+c;
    s[i]:='A';
    Rec(n+1);
    s[i]:=c;
    delete(a,length(a),1);
  end;
end;
begin
  assign(f,'input.txt');
  reset(f);
  readln(f,s);
  readln(f,t);
  x:=StrToInt(t);
  close(f);
  l:=length(s);
  a:='';
  Rec(1);
  assign(g,'output.txt');
  rewrite(g);
  writeln(g,ans);
  close(g);
end.