{$APPTYPE CONSOLE}
var
  n,k,k1,k2,i,j:longint;
  a,b,c,v:array[1..11] of longint;
  m:array[1..2] of longint;
  z:boolean;
Function Has(v,i:longint):boolean;
begin
  Has:=(v shr i)and 1<>0;
end;
Function Test_B(x:longint):boolean;
var
  i,s1,s2,j:longint;
begin
  for i:=1 to (1 shl x)-1 do begin
    s1:=0;
    s2:=0;
    for j:=1 to x do if Has(i,j) then inc(s1,b[j]) else inc(s2,b[j]);
    if s1<>s2 then continue;
    Test_B:=True;
    exit;
  end;
  Test_B:=False;
end;
Function Test_C(x:longint):boolean;
var
  i,s1,s2,j:longint;
begin
  for i:=1 to (1 shl x)-1 do begin
    s1:=0;
    s2:=0;
    for j:=1 to x do if Has(i,j) then inc(s1,c[j]) else inc(s2,c[j]);
    if s1<>s2 then continue;
    Test_C:=True;
    exit;
  end;
  Test_C:=False;
end;
Procedure Rec(x:longint);
var
  i:longint;
begin
  if x=n+1 then begin
    fillchar(m,sizeof(m),0);
    for i:=1 to n do inc(m[v[i]],a[i]);
    if m[1]=m[2] then begin
      k1:=0;
      k2:=0;
      for i:=1 to n do begin
        if v[i]=1 then begin inc(k1);b[k1]:=a[i];end;
        if v[i]=2 then begin inc(k2);c[k2]:=a[i];end;
      end;
      if Test_B(k1) and Test_C(k2) then z:=True;
      if z then exit;
    end;
    exit;
  end;
  for i:=1 to 2 do begin
    if (x=1)and(i=2) then continue;
    v[x]:=i;
    Rec(x+1);
    v[x]:=0;
    if z then exit;
  end;
end;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(k,n);
  for i:=1 to k do begin
    for j:=1 to n do read(a[j]);
    z:=False;
    Rec(1);
    if z then writeln('YES')
         else writeln('NO');
  end;
end.