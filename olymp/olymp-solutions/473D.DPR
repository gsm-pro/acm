type
  pt=record
    x,y,t:longint;
  end;
var
  f,g:text;
  i,j,n,maxl,v,start:longint;
  temp:pt;
  c:array[0..1100] of pt;
  ap,b,pr,ans:array[0..1100] of longint;
Function Dost(z1,z2:pt):boolean;
begin
  Dost:=100*(z1.t-z2.t)*(z1.t-z2.t)>=(z1.x-z2.x)*(z1.x-z2.x)+(z1.y-z2.y)*(z1.y-z2.y);
end;
begin
  reset(input,'input.txt');
  read(n,c[0].x,c[0].y);
  for i:=1 to n do read(c[i].x,c[i].y,c[i].t);
  for i:=1 to n do ap[i]:=i;
  for i:=1 to n-1 do
    for j:=n downto i+1 do
      if c[j].t<c[j-1].t then begin
        temp:=c[j];c[j]:=c[j-1];c[j-1]:=temp;
        v:=ap[j];ap[j]:=ap[j-1];ap[j-1]:=v;
      end;
  for i:=1 to n do begin
    if not Dost(c[0],c[i]) then continue;
    maxl:=0;
    for j:=1 to i-1 do
      if (Dost(c[i],c[j]))and(b[j]>=maxl) then begin
        maxl:=b[j];
        pr[i]:=j;
      end;
    b[i]:=maxl+1;
  end;
  maxl:=0;
  start:=0;
  for i:=1 to n do if b[i]>maxl then begin
    maxl:=b[i];
    start:=i;
  end;
  rewrite(output,'output.txt');
  v:=0;
  fillchar(b,sizeof(b),0);
  repeat
    inc(v);
    b[v]:=start;
    start:=pr[start];
  until start=0;
  writeln(maxl);
  for i:=1 to maxl do ans[i]:=ap[b[i]];
  for i:=1 to maxl-1 do
    for j:=maxl downto i+1 do
      if ans[j]<ans[j-1] then begin
        v:=ans[j];
        ans[j]:=ans[j-1];
        ans[j-1]:=v;
      end;
  for i:=1 to maxl do write(ans[i],' ');
end.