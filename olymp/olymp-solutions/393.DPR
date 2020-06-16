{$APPTYPE CONSOLE}
uses
  SysUtils;
Var
  f,g:text;
  k,i,kol:longint;
  s,snew:ansistring;
Function Convert(s:ansistring):ansistring;
var
  snew:ansistring;
  pred:string[1];
  kol,i:longint;
begin
  if length(s)=1 then begin
    Convert:='1'+s;
    exit;
  end;  
  pred:='';
  snew:='';
  for i:=1 to length(s) do begin
    if pred='' then kol:=1;
    if pred= s[i] then inc(kol);
    if (pred<>s[i])and(pred<>'') then begin
      snew:=snew+IntToStr(kol)+pred;
      kol:=1;
    end;
    pred:=s[i];
  end;
  if s[length(s)]=s[length(s)-1] then snew:=snew+IntToStr(kol)+s[length(s)]
                                 else snew:=snew+'1'+s[length(s)];
  Convert:=snew;
end;
begin
  assign(f,'input.txt');
  reset(f);
  readln(f,s);
  readln(f,k);
  close(f);
  for i:=2 to k do begin
    snew:=Convert(s);
    s:=snew;
  end;
  assign(g,'output.txt');
  rewrite(g);
  writeln(g,s);
  close(g);
end.