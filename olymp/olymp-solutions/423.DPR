{$APPTYPE CONSOLE}
uses math;
var
  w:array[1..500] of string;
  s:array[1..500,1..500] of string;
  kol:array[1..500] of longint;
  i,j,n:longint;
  tmp:string;
Function Common(q:longint):longint;
var
  i:longint;
begin
  for i:=1 to min(kol[q],kol[q-1]) do
    if s[q,i]<>s[q-1,i] then begin
      Common:=i-1;
      exit;
    end;
  Common:=min(kol[q],kol[q-1]);
end;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(n);
  for i:=1 to n do readln(w[i]);
  for i:=1 to n do
    for j:=1 to length(w[i]) do
      if w[i,j]='\' then w[i,j]:=' ';
  for i:=1 to n-1 do
    for j:=1 to n-1 do
      if w[j]>w[j+1] then begin
        tmp:=w[j];
        w[j]:=w[j+1];
        w[j+1]:=tmp;
      end;
  for i:=1 to n do
    for j:=1 to length(w[i]) do
      if w[i,j]=' ' then w[i,j]:='\';
  for i:=1 to n do
    for j:=1 to length(w[i]) do begin
      if (w[i,j]='\')or(j=1) then inc(kol[i]);
      if (w[i,j]<>'\') then s[i,kol[i]]:=s[i,kol[i]]+w[i,j];
    end;
  for i:=1 to n do begin
    tmp:='';
    for j:=1 to kol[i] do begin
      s[i,j]:=tmp+s[i,j];
      tmp:=tmp+' ';
    end;
  end;
  for i:=1 to kol[1] do writeln(s[1,i]);
  for i:=2 to n do
    for j:=common(i)+1 to kol[i] do writeln(s[i,j]);
end.