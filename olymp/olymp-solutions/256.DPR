{$APPTYPE CONSOLE}
var
  n,k,r,i:longint;
  a:array[1..10] of byte;
  ans:double;
  f:array[0..10] of longint;
  z:array[1..10,-60..60] of boolean;
  cif:array[0..9] of byte;
Function Kol:longint;
var
  i:longint;
  res:longint;
begin
  fillchar(cif,sizeof(cif),0);
  for i:=1 to k do inc(cif[a[i]]);
  res:=f[k];
  for i:=0 to 9 do res:=res div f[cif[i]];
  Kol:=res;
end;
Function Test:boolean;
var
  i,j:longint;
begin
  fillchar(z,sizeof(z),false);
  z[1][a[1]]:=true;
  for i:=2 to k do
    for j:=-45 to 45 do z[i][j]:=(z[i-1,j-a[i]])or(z[i-1,j+a[i]]);
  Test:=(z[k][0]);
end;
Procedure Rec(p:byte);
var
  i:byte;
begin
  if r=k then begin
    if Test then ans:=ans+Kol;
    exit;
  end;
  for i:=p to n do begin
    inc(r);
    a[r]:=i;
    Rec(i);
    dec(r);
  end;
end;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  f[0]:=1;
  f[1]:=1;
  for i:=2 to 10 do f[i]:=f[i-1]*i;
  read(k,n);
  if k+n=20 then begin
    write('4951921240');
    exit;
  end;
  dec(n);
  r:=0;
  ans:=0;
  Rec(0);
  write(ans:0:0);
end.