{$APPTYPE CONSOLE}
uses math;
Var
  z,b,p1,p2,p,x:array[1..1000] of longint;
  i,n,maxl,j,mx1,mx2,i1,i2,k:longint;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  for i:=1 to n do read(z[i]);
  fillchar(b,sizeof(b),0);
  b[1]:=1;
  for i:=2 to n do begin
    maxl:=0;
    for j:=1 to i-1 do
      if (b[j]>=maxl)and
       (
        ((odd(b[j]+1))and(z[j]>z[i]))or
        ((odd(b[j]))and(z[j]<z[i]))
       ) then begin
           maxl:=b[j];
           p1[i]:=j;
         end;
    b[i]:=maxl+1;
  end;
  mx1:=0;
  i1:=0;
  for i:=1 to n do if b[i]>mx1 then begin mx1:=b[i];i1:=i;end;
  fillchar(b,sizeof(b),0);
  b[1]:=1;
  for i:=2 to n do begin
    maxl:=0;
    for j:=1 to i-1 do
      if (b[j]>=maxl)and
       (
        ((odd(b[j]))and(z[j]>z[i]))or
        ((odd(b[j]+1))and(z[j]<z[i]))
       ) then begin
           maxl:=b[j];
           p2[i]:=j;
         end;
    b[i]:=maxl+1;
  end;
  mx2:=0;
  i2:=0;
  for i:=1 to n do if b[i]>mx2 then begin mx2:=b[i];i2:=i;end;
  k:=0;
  if mx1>mx2 then begin
    writeln(n-mx1);
    while i1<>0 do begin
      inc(k);
      p[mx1-k+1]:=i1;
      i1:=p1[i1];
    end;
    for i:=1 to mx1 do x[p[i]]:=1;
    for i:=1 to n do if x[i]=0 then write(i,' ');
  end else begin
    writeln(n-mx2);
    while i2<>0 do begin
      inc(k);
      p[mx2-k+1]:=i2;
      i2:=p2[i2];
    end;
    for i:=1 to mx2 do x[p[i]]:=1;
    for i:=1 to n do if x[i]=0 then write(i,' ');
  end;
end.