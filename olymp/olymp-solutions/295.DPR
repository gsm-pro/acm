{$APPTYPE CONSOLE}
uses math;
Var
  z,b1,b2,p1,p2,ans:array[1..100] of word;
  i,n,maxl,j,ps,ind,kol,a,mx:word;
  f,g:text;
begin
  assign(f,'input.txt');
  reset(f);
  read(f,n);
  for i:=1 to n do read(f,z[i]);
  close(f);
  b1[1]:=1;
  for i:=2 to n do begin
    maxl:=0;
    for j:=1 to i-1 do
      if (b1[j]>=maxl)and(z[j]<z[i]) then begin
        maxl:=b1[j];
        p1[i]:=j;
      end;
    b1[i]:=maxl+1;
  end;
  b2[n]:=1;
  for i:=n-1 downto 1 do begin
    maxl:=0;
    for j:=n downto i+1 do
      if (b2[j]>=maxl)and(z[j]<z[i]) then begin
        maxl:=b2[j];
        p2[i]:=j;
      end;
    b2[i]:=maxl+1;
  end;
  mx:=0;
  ps:=0;
  for i:=1 to n do
    if min(b1[i],b2[i])>mx then begin
      mx:=min(b1[i],b2[i]);
      ps:=i;
    end;
  kol:=0;
  ind:=ps;
  a:=min(b1[ps],b2[ps]);
  dec(a);
  while true do begin
    ind:=p1[ind];
    if (kol=a) then break;
    inc(kol);
    ans[kol]:=ind;
  end;
  ind:=ps;
  while true do begin
    ind:=p2[ind];
    if kol=2*a then break;
    inc(kol);
    ans[kol]:=ind;
  end;
  a:=kol div 2;
  assign(g,'output.txt');
  rewrite(g);
  writeln(g,a);
  for i:=a downto 1 do write(g,ans[i],' ');
  write(g,ps,' ');
  for i:=a+1 to 2*a do write(g,ans[i],' ');
  close(g);
end.