{$APPTYPE CONSOLE}
var
  n,k,m,vn,vk,ans,i:longint;
  a:array[1..8,1..8] of longint;
  cvet:array[1..8] of longint;
procedure brute(t:longint);
var
  i,j:longint;
  b:boolean;
begin
  if t=n+1 then begin
    inc(ans);
    exit;
  end;
  for i:=1 to k do begin
    cvet[t]:=i;
    b:=True;
    for j:=1 to n do
      if (a[j,t]=1)and(cvet[t]=cvet[j])then begin
        b:=False;
        break;
      end;
    if b then brute(t+1);
    cvet[t]:=0;
  end;
end;
begin
  readln(n,k,m);
  for i:=1 to m do begin
    readln(vn,vk);
    a[vn,vk]:=1;
    a[vk,vn]:=1;
  end;
  ans:=0;
  fillchar(cvet,sizeof(cvet),0);
  brute(1);
  write(ans);
end.