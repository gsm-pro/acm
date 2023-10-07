{$APPTYPE CONSOLE}
var
  a:array[1..1000,1..1000] of byte;
  vert:array[1..1000] of boolean;
  ans:array[1..1000]of longint;
  n,m,i,z,vn,vk,cnt:longint;
procedure DFS(v,z:longint);
var
  i:longint;
begin
  vert[v]:=False;
  ans[v]:=z;
  for i:=1 to n do
    if (a[v,i]<>0)and(vert[i]) then DFS(i,z);
end;
begin
  readln(n,m);
  for i:=1 to m do begin
    readln(vn,vk);
    a[vn,vk]:=1;
    a[vk,vn]:=1;
  end;
  fillchar(vert,sizeof(vert),true);
  fillchar(ans,sizeof(ans),0);
  cnt:=0;
  z:=0;
  for i:=1 to n do
    if (vert[i]) then begin
      inc(cnt);
      inc(z);
      DFS(i,z);
    end;
  writeln(cnt);
  for i:=1 to n do write(ans[i],' ');
end.