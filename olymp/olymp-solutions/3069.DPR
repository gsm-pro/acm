{$APPTYPE CONSOLE}
var
  f,g:text;
  t,n,k,m,p1,p2,i,j,kol,ans:longint;
  v,matr,sh,pch:array[0..1000] of byte;
begin
  assign(f,'input.txt');
  reset(f);
  read(f,t,n,k,m);
  for i:=1 to n do begin
    read(f,p1,p2);
    for j:=p1 to p2 do sh[j]:=1;
  end;
  for i:=1 to k do begin
    read(f,p1,p2);
    for j:=p1 to p2 do matr[j]:=1;
  end;
  for i:=1 to m do begin
    read(f,p1,p2);
    for j:=p1 to p2 do pch[j]:=1;
  end;
  close(f);
  for i:=0 to 1000 do
    if (sh[i]=0)and(matr[i]=0)and(pch[i]=1) then v[i]:=1;
  kol:=0;
  ans:=-1;
  for i:=0 to 1000 do
    if v[i]=1 then begin
      inc(kol);
      if kol=t then begin
        ans:=i-t+1;
        break;
      end;
    end else kol:=0;
  assign(g,'output.txt');
  rewrite(g);
  if ans=-1 then write(g,'NO') else write(g,ans);
  close(g);
end.