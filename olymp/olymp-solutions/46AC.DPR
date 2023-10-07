{$APPTYPE CONSOLE}
uses SysUtils;
var
  c,n,i,j,k:longint;
  nabr,v:int64;
  q,s:string;
  a:array[-10..50000] of longint;
  o:array[-10..50000] of int64;
  ok:boolean;
  s10:array[0..18] of int64;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  s10[0]:=1;
  for i:=1 to 18 do s10[i]:=s10[i-1]*10;
  readln(n,c,k);
  readln(s);
  for i:=1 to length(s) do a[i]:=StrToInt(s[i]);
  ok:=true;
  if c<10 then begin
    for i:=1 to n do if a[i]>c then ok:=false;
    if not ok then begin
      write(0);
      halt(0);
    end;
  end;
  o[0]:=1;
  for i:=1 to n do begin
    nabr:=0;
    for j:=0 to 9 do
      if nabr+a[i-j]*s10[j]>c then break else nabr:=nabr+a[i-j]*s10[j];
    q:=IntToStr(nabr);
    q:=q+' ';
    v:=0;
    for j:=1 to length(q)-1 do
      if not ((q[j]='0')and(q[j+1] in ['0'..'9']))
        then v:=(v+o[i-length(q)+1+j-1]) mod s10[k];
    o[i]:=v;
  end;
  write(o[n]);
end.