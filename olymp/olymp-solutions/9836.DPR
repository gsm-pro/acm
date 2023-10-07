{$APPTYPE CONSOLE}
uses Math;
Var
  n,i,j,t:longint;
  a:array[1..100] of longint;
  z:array[1..100,1..100] of longint;
Function Rec(s,t:longint):longint;
var
  m:longint;
begin
  if t>n then begin
    Rec:=a[n]-a[s];
    exit;
  end;
  if z[s,t]<>-1 then begin
    Rec:=z[s,t];
    exit;
  end;
  if (s=t)or(t=n-1) then m:=Rec(s,t+1)
                    else m:=min(max(a[t]-a[s],Rec(t+1,t+1)),Rec(s,t+1));
  z[s,t]:=m;
  Rec:=m;
end;
Begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  for i:=1 to n do read(a[i]);
  for i:=1 to n-1 do
    for j:=1 to n-1 do
      if a[j]>a[j+1] then begin
        t:=a[j];
        a[j]:=a[j+1];
        a[j+1]:=t;
      end;
  for i:=1 to 100 do for j:=1 to 100 do z[i,j]:=-1;
  write(Rec(1,1));
end.