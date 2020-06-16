{$APPTYPE CONSOLE}
Var
  x,y,r:array[1..200] of longint;
  n,i,j,ans,unicht,mx,t,ost:longint;
  q:array[1..200] of longint;
  z:array[1..200,1..200] of byte;
  ex,used:array[1..200] of boolean;
Procedure DFS(x:longint);
var
  i:longint;
begin
  used[x]:=true;
  for i:=1 to n do
    if ex[i] and (used[i]=false) and (z[x,i]=1) then begin
      inc(t);
      dfs(i);
    end;
end;
Procedure DFS_UN(x:longint);
var
  i:longint;
begin
  ex[x]:=false;
  for i:=1 to n do
    if ex[i] and (z[x,i]=1) then DFS_UN(i);
end;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  for i:=1 to n do read(x[i],y[i],r[i]);
  for i:=1 to n do
    for j:=1 to n do
      if i<>j then
        if sqr(x[i]-x[j])+sqr(y[i]-y[j])<=r[i]*r[i] then z[i,j]:=1;
  fillchar(ex,sizeof(ex),true);
  ans:=0;
  while true do begin
    mx:=0;
    unicht:=0;
    for i:=1 to n do begin
      if ex[i] then begin
        fillchar(used,sizeof(used),false);
        t:=1;
        dfs(i);
        if t>mx then begin
          mx:=t;
          unicht:=i;
        end;
      end;
    end;
    DFS_UN(unicht);
    inc(ans);
    q[ans]:=unicht;
    ost:=0;
    for i:=1 to n do if ex[i] then inc(ost);
    if ost=0 then break;
  end;
  writeln(ans);
  for i:=1 to ans-1 do
    for j:=1 to ans-1 do
      if q[j]>q[j+1] then begin
        t:=q[j];
        q[j]:=q[j+1];
        q[j+1]:=t;
      end;
  for i:=1 to ans do write(q[i],' ');
end.