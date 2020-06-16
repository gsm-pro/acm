{$APPTYPE CONSOLE}
uses Math;
var
  z:array[1..1000,1..1000] of longint;
  a,k:array[1..1000] of longint;
  w:array[1..1000] of longint;
  n,m,i,j,ind,kol:longint;
  ans:array[-1..1] of longint;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(n,m);
  fillchar(w,sizeof(w),-1);
  for i:=1 to n do begin
    read(a[i],k[i]);
    for j:=1 to k[i] do read(z[i,j]);
  end;
  for i:=1 to n do
    if a[i]=0 then
      for j:=1 to k[i] do w[z[i,j]]:=1;
  for i:=1 to n do
    if a[i]=1 then begin
      ind:=0;
      kol:=0;
      for j:=1 to k[i] do if w[z[i,j]]=-1 then begin
        inc(kol);
        ind:=j;
      end;
      if kol=1 then w[z[i,ind]]:=0;
    end;
  for i:=1 to m do inc(ans[w[i]]);
  write(ans[1],' ',ans[0],' ',ans[-1]);
end.