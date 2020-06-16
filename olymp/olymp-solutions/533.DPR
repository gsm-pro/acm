{$APPTYPE CONSOLE}
uses SysUtils,math;
Var
  kol,i,j:longint;
  _a,_b,_c,code:longint;
  a,b,c:string;
  t:int64;
  z:array[1..6] of string;
  p,q:array[0..6] of int64;
Function sum(aa,bb:string):string;
var
  zz,ch1,ch2:string;
  i,mx:longint;
begin
  zz:='';
  mx:=max(length(aa),length(bb));
  for i:=1 to mx-length(aa) do aa:='0'+aa;
  for i:=1 to mx-length(bb) do bb:='0'+bb;
  for i:=mx downto 1 do begin
    ch1:=aa[i];
    ch2:=bb[i];
    zz:=IntToStr(StrToInt(ch1)+StrToInt(ch2))+zz;
  end;
  sum:=zz;
end;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(_a,_b,_c);
  a:=IntToStr(_a);
  b:=IntToStr(_b);
  c:=IntToStr(_c);
  z[1]:=sum(sum(a,b),c);
  z[2]:=sum(sum(b,a),c);
  z[3]:=sum(sum(a,c),b);
  z[4]:=sum(sum(c,a),b);
  z[5]:=sum(sum(b,c),a);
  z[6]:=sum(sum(c,b),a);
  for i:=1 to 6 do val(z[i],p[i],code);
  for i:=1 to 5 do
    for j:=1 to 5 do
      if p[j]>p[j+1] then begin
        t:=p[j];
        p[j]:=p[j+1];
        p[j+1]:=t;
      end;
  kol:=0;
  for i:=1 to 6 do
    if p[i]<>p[i-1] then begin
      inc(kol);
      q[kol]:=p[i];
    end;
  if kol=1 then writeln('NO') else writeln('YES');
  for i:=1 to kol do writeln(q[i]);
end.