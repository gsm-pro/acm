{$APPTYPE CONSOLE}
uses SysUtils,math;
const
  inf=99999;
var
  m,n,i,ps,cost:longint;
  w:array[1..100] of string;
  s,inp,ans:string;
  z:array[1..1000] of longint;
  way:array[1..1000] of longint;
Function dist_ch(c1,c2:char):longint;
var
  k1,k2,kk1,kk2:longint;
begin
  k1:=ord(c1)-96;
  k2:=ord(c2)-96;
  kk1:=min(k1,k2);
  kk2:=max(k1,k2);
  dist_ch:=min(kk2-kk1,kk1+26-kk2);
end;
Function dist(start,len:longint;t:string):longint;
var
  i,res:longint;
begin
  res:=0;
  for i:=0 to len-1 do
    res:=res+dist_ch(s[start+i],t[i+1]);
  dist:=res;
end;
Function Calc(p:longint):longint;
var
  i,q,d,clc,ind:longint;
begin
  if p=n+1 then begin
    Calc:=0;
    exit;
  end;
  if z[p]<>-1 then begin
    Calc:=z[p];
    exit;
  end;
  q:=inf;
  ind:=0;
  for i:=1 to m do begin
    if p+length(w[i])>n+1 then continue;
    d:=dist(p,length(w[i]),w[i]);
    clc:=Calc(p+length(w[i]))+d;
    if q>clc then begin q:=clc;ind:=i;end;
  end;
  z[p]:=q;
  way[p]:=ind;
  Calc:=q;
end;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(m);
  for i:=1 to m do begin
    readln(w[i]);
    w[i]:=LowerCase(w[i]);
    w[i]:=trim(w[i]);
  end;
  readln(inp);
  inp:=trim(inp);
  s:=inp;
  s:=LowerCase(s);
  n:=length(s);
  fillchar(z,sizeof(z),-1);
  cost:=Calc(1);
  if cost=inf then begin
    write(-1);
    halt(0);
  end;
  ps:=1;
  while ps<>n+1 do begin
    ans:=ans+w[way[ps]];
    ps:=ps+length(w[way[ps]]);
  end;
  for i:=1 to length(ans) do
    if inp[i] in ['A'..'Z'] then ans[i]:=chr(ord(ans[i])-32);
  write(ans);
end.