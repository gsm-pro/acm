{$apptype console}
var
  s:string;
  i,n:longint;
  z:array[1..100] of string;
Function toStr(x:longint):string;
var
  s:string;
begin
  str(x,s);
  toStr:=s;
end;
Function Rec(x:longint):string;
var
  w,q,r:string;
  i,j,min_len:longint;
  ok:boolean;
  m:string;
begin
  if x>n+1 then exit;
  if x=n+1 then begin
    Rec:='';
    exit;
  end;
  if z[x]<>'#' then begin
    Rec:=z[x];
    exit;
  end;
  w:='';
  min_len:=300;
  for i:=1 to 100 do begin
    if x+i>n+1 then break;
    q:=copy(s,x,i);
    ok:=false;
    for j:=1 to 100 do begin
      r:=copy(s,x+i*(j-1),i);
      if r=q then begin
        ok:=true;
        if j=1 then m:=q+Rec(x+i*j) else m:='('+toStr(j)+q+')'+Rec(x+i*j);
        if length(m)<min_len then begin min_len:=length(m);w:=m;end;
      end else break;
    end;
    if not ok then break;
  end;
  z[x]:=w;
  Rec:=w;
end;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  for i:=1 to 100 do z[i]:='#';
  readln(s);
  n:=length(s);
  write(rec(1));
end.