{$APPTYPE CONSOLE}
const
  MAXN=101;
  MAXX=101;
type
  PointType=record
    X,Y:integer;
  end;
var
  a:array[1..MAXN] of pointtype;
  p:array[1..MAXX,1..MAXX] of byte;
  t:array[0..16] of byte;
  N,i,j,k,z,max,s:integer;
  ans1,ans2,ans3,ans4,ans5:longint;
begin
  read(N);
  max:=0;
  ans1:=0;ans2:=0;ans3:=0;ans4:=0;ans5:=0;
  for i:=1 to N do begin
    read(a[i].x,a[i].y);
    if a[i].x>max then max:=a[i].x;
    if a[i].y>max then max:=a[i].y;
  end;
  p[1,1]:=0;
  for i:=1 to max do
    for j:=i to max do begin
      fillchar(t,sizeof(t),0);
      for k:=1 to i-1 do t[p[k,j] xor p[i-k,j]]:=1;
      for k:=1 to j-1 do t[p[i,k] xor p[i,j-k]]:=1;
      for k:=1 to i-2 do t[p[k,j] xor p[i-k-1,j]]:=1;
      for k:=1 to j-2 do t[p[i,k] xor p[i,j-k-1]]:=1;
      if (i>=3)and(j>=3) then t[p[i-2,j-2]]:=1;
      for k:=0 to 16 do
        if t[k]=0 then begin
          p[i,j]:=k;
          p[j,i]:=k;
          break;
        end;
      end;
  s:=0;
  for z:=1 to N do s:=s xor p[a[z].x,a[z].y];
  for z:=1 to N do begin
    i:=a[z].x;j:=a[z].y;
    for k:=1 to i-1 do
      if s xor p[i,j] xor p[k,j] xor p[i-k,j]=0 then inc(ans2);
    for k:=1 to j-1 do
      if s xor p[i,j] xor p[i,k] xor p[i,j-k]=0 then inc(ans1);
    for k:=1 to i-2 do
      if s xor p[i,j] xor p[k,j] xor p[i-k-1,j]=0 then inc(ans4);
    for k:=1 to j-2 do
      if s xor p[i,j] xor p[i,k] xor p[i,j-k-1]=0 then inc(ans3);
    if (i>=3)and(j>=3) then
      if s xor p[i,j] xor p[i-2,j-2] = 0 then inc(ans5);
  end;
  write(ans1+ans2+ans3+ans4+ans5);
end.