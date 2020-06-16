{$APPTYPE CONSOLE}
var
  z:array of array of longint;
  n,i,k,kk,kol,j:longint;
  x,p:array[0..100000] of longint;
begin
  read(n);
  SetLength(z,n+1);
  for i:=1 to n do SetLength(z[i],1);
  k:=n;
  kol:=1;
  while k<>1 do begin
    kk:=k div 2;
    for i:=k-kk+1 to k do begin
      SetLength(z[i],kol+1);
      x[i]:=kol;
    end;
    dec(k,kk);
    kol:=kol*2;
  end;
  SetLength(z[1],n*2+1);
  x[1]:=n*2;
  k:=0;
  for i:=1 to n do begin
    if x[i-1]<>x[i] then k:=0;
    inc(k);
    p[i]:=k;
  end;
  for i:=1 to n do z[i,1]:=i;
  k:=n;
  kol:=1;
  while k<>1 do begin
    kk:=p[k];
    for j:=(1 shl(kol-1))+1 to (1 shl kol) do
      for i:=1 to kk do
        z[k-2*kk+i,j]:=z[k-i+1,1 shl kol-j+1];
    dec(k,kk);
    kol:=kol+1;
  end;
  for i:=1 to 2*n do if z[1,i]<>0 then write(z[1,i],' ');
end.