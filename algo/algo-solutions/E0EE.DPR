{$APPTYPE CONSOLE}
const
  INF=99;
var
  i,m,n,k,a,b,ans:longint;
  z:array[1..20,0..20] of longint;
  arr,ar,used:array[1..20] of longint;
Procedure Rec(x:longint);
var
  i,j,k,sum:longint;
begin
  if x=n+1 then begin
    fillchar(used,sizeof(used),0);
    for i:=1 to n do
      if ar[i]=1 then
        for j:=1 to z[i,0] do used[z[i,j]]:=1;
    sum:=0;
    for i:=1 to m do inc(sum,used[i]);
    k:=0;
    for i:=1 to n do inc(k,ar[i]);
    if (k<ans)and(sum=m) then begin
      ans:=k;
      arr:=ar;
    end;
    exit;
  end;
  ar[x]:=0;
  Rec(x+1);
  ar[x]:=1;
  Rec(x+1);
end;
begin
  while not seekeof do begin
    fillchar(z,sizeof(z),0);
    fillchar(arr,sizeof(arr),0);
    read(n,m,k);
    for i:=1 to k do begin
      read(a,b);
      inc(z[a,0]);
      z[a,z[a,0]]:=b;
    end;
    ans:=INF;
    Rec(1);
    if ans=INF then ans:=-1;
    writeln(ans);
    for i:=1 to n do if arr[i]=1 then write(i,' ');
    writeln;
  end;
end.