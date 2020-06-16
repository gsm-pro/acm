{$apptype console}
uses SysUtils;
const
  vowels:set of char=['e','y','u','i','o','a'];
var
  s,t,_s,_t,ans:string;
  dict,gl,sogl:array[1..100] of string;
  i,n,xx,yy,j,num:longint;
  z:array[1..100,1..100] of string;
  is_big:array[1..100] of boolean;
  stop:boolean;
Function Can(var a1,a2:string;var x1,x2:longint):boolean;
begin
  if (x1+length(a1)>xx+1)or(x2+length(a2)>yy+1) then Can:=false else
    if (copy(s,x1,length(a1))<>a1)or(copy(t,x2,length(a2))<>a2) then
      Can:=false else Can:=true;
end;
Function Calc(x,y:longint):string;
var
  i:longint;
  m:string;
begin
  if (x=xx+1)and(y=yy+1) then begin
    Calc:='';
    stop:=true;
    exit;
  end;
  if z[x][y]<>'$' then begin
    Calc:=z[x][y];
    exit;
  end;
  m:='';
  for i:=1 to n do
    if (can(sogl[i],gl[i],x,y))and(not stop) then
      m:=dict[i]+' '+Calc(x+length(sogl[i]),y+length(gl[i]));
  z[x][y]:=m;
  Calc:=m;
end;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  for i:=1 to 100 do
    for j:=1 to 100 do z[i,j]:='$';
  readln(_s);
  readln(_t);
  s:=lowercase(_s);
  t:=lowercase(_t);
  s:=trim(s);
  t:=trim(t);
  xx:=length(s);
  yy:=length(t);
  readln(n);
  for i:=1 to n do begin
    readln(dict[i]);
    dict[i]:=trim(dict[i]);
    dict[i]:=lowercase(dict[i]);
    for j:=1 to length(dict[i]) do
      if (dict[i][j] in vowels) then gl[i]:=gl[i]+dict[i][j]
                                else sogl[i]:=sogl[i]+dict[i][j];
  end;
  stop:=false;
  ans:=Calc(1,1);
  fillchar(is_big,sizeof(is_big),false);
  for i:=1 to xx do
    if _s[i] in ['A'..'Z'] then is_big[i]:=true;
  num:=0;
  for i:=1 to length(ans) do
    if (ans[i]<>' ')and(not(ans[i] in vowels)) then begin
      inc(num);
      if is_big[num] then ans[i]:=char(ord(ans[i])-32);
    end;
  fillchar(is_big,sizeof(is_big),false);
  for i:=1 to yy do
    if _t[i] in ['A'..'Z'] then is_big[i]:=true;
  num:=0;
  for i:=1 to length(ans) do
    if (ans[i]<>' ')and(ans[i] in vowels) then begin
      inc(num);
      if is_big[num] then ans[i]:=char(ord(ans[i])-32);
    end;
  write(trim(ans));
end.