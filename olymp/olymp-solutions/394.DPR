{$APPTYPE CONSOLE}
var
  a,k1,k2,ans:array[0..10000] of longint;
  i,n,z,r,rmin,kol,t,num:longint;
begin
  reset(input,'input.txt');
  read(n);
  for i:=1 to n do begin
    read(a[i]);
    if a[i]= 1 then begin k1[i]:=k1[i-1]+1;k2[i]:=k2[i-1];end;
    if a[i]=-1 then begin k2[i]:=k2[i-1]+1;k1[i]:=k1[i-1];end;
  end;
  rmin:=50000;
  kol:=0;
  num:=0;
  for z:=0 to n do begin
    r:=k1[n]-k1[z]+k2[z];
    if r<rmin then begin
      rmin:=r;
      kol:=0;
      num:=z;
    end;
    if r=rmin then inc(kol);
  end;
  rewrite(output,'output.txt');
  writeln(rmin);
  writeln(kol);
  t:=0;
  for i:=1 to n do begin
    if (i<=num)and(a[i]=-1) then begin inc(t);ans[t]:=i;end;
    if (i> num)and(a[i]= 1) then begin inc(t);ans[t]:=i;end;
  end;
  for i:=1 to rmin do write(ans[i],' ');
end.