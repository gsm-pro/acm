{$APPTYPE CONSOLE}
uses SysUtils;
type
  rec=record
    m:string;
    h:longint;
  end;
var
  s:string;
  i,j,k,l,kol,bit,ans:longint;
  chars:array[32..127] of longint;
  st:array[1..62] of rec;
  b:array[1..5] of byte;
  t:rec;
Procedure BitForm(n:longint);
var
  i:integer;
begin
  for i:=bit downto 1 do begin
    if odd(n) then b[i]:=1 else b[i]:=0;
    n:=n shr 1;
  end;
end;
begin
  k:=0;
  for bit:=1 to 5 do
    for j:=0 to (1 shl bit)-1 do begin
      fillchar(b,sizeof(b),0);
      BitForm(j);
      inc(k);
      for l:=1 to bit do st[k].m:=st[k].m+IntToStr(b[l]);
    end;
  for i:=1 to 62 do
    for j:=1 to length(st[i].m) do
      with st[i] do
        if m[j]='0' then inc(h) else inc(h,3);
  for i:=1 to 61 do
    for j:=1 to 61 do
      if st[j].h>st[j+1].h then begin
        t:=st[j];
        st[j]:=st[j+1];
        st[j+1]:=t;
      end;
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(s);
  s:=LowerCase(s);
  for i:=1 to length(s) do inc(chars[ord(s[i])]);
  kol:=0;
  for i:=32 to 127 do if chars[i]>0 then inc(kol);
  for i:=32 to 126 do
    for j:=32 to 126 do
      if chars[j]<chars[j+1] then begin
        k:=chars[j];
        chars[j]:=chars[j+1];
        chars[j+1]:=k;
      end;
  ans:=0;
  for i:=1 to kol do ans:=ans+chars[31+i]*st[i].h;
  write(ans);
end.