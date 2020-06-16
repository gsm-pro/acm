{$APPTYPE CONSOLE}
uses SysUtils;
Type
  ShortStr=string[11];
var
  xx,yy,a:ShortStr;
  l,x,y,z,ans:longint;
  f,g:text;
  q:boolean;
Procedure Sort(var w:ShortStr);
var
  i,j:longint;
  c:char;
begin
  for i:=1 to length(w)-1 do
    for j:=1 to length(w)-1 do
      if w[j]>w[j+1] then begin
        c:=w[j];
        w[j]:=w[j+1];
        w[j+1]:=c;
      end;
end;
Procedure Rec(n:longint);
var
  i,v:longint;
  c:char;
  m:ShortStr;
begin
  if n=l+1 then begin
    v:=StrToInt(a);
    ans:=z-v;
    m:=IntToStr(ans);
    Sort(m);
    m:=IntToStr(StrToInt(m));
    if m=xx then begin
      q:=True;
      exit;
    end;
  end;
  for i:=1 to l do begin
    c:=yy[i];
    if c='#' then continue;
    a:=a+c;
    yy[i]:='#';
    Rec(n+1);
    if q then exit;
    yy[i]:=c;
    delete(a,length(a),1);
  end;
end;
begin
  assign(f,'input.txt');
  reset(f);
  read(f,x,y,z);
  close(f);
  xx:=IntToStr(x);
  yy:=IntToStr(y);
  Sort(xx);
  xx:=IntToStr(StrToInt(xx));
  l:=length(yy);
  a:='';
  q:=False;
  ans:=0;
  Rec(1);
  assign(g,'output.txt');
  rewrite(g);
  if q then begin
    writeln(g,'YES');
    writeln(g,ans,' ',z-ans);
  end else writeln(g,'NO');
  close(g);
end.