{$APPTYPE CONSOLE}
var
  a:array[1..100,1..100] of longint;
  vert:array[1..100] of boolean;
  n,m,i,vn,vk:longint;
  f,g:text;
  z:boolean;
procedure DFS(v:longint);
var
  i:longint;
begin
  vert[v]:=false;
  for i:=1 to n do
    if (a[v,i]<>0)and(vert[i]) then DFS(i)
end;
begin
  assign(f,'input.txt');
  reset(f);
  readln(f,n,m);
  fillchar(a,sizeof(a),0);
  for i:=1 to m do begin
    readln(f,vn,vk);
    inc(a[vn,vk]);
    inc(a[vk,vn]);
  end;
  close(f);
  assign(g,'output.txt');
  rewrite(g);
  fillchar(vert,sizeof(vert),true);
  DFS(1);
  z:=True;
  for i:=1 to n do
    if vert[i]=True then begin
      z:=False;
      break;
    end;
  if (m=n-1)and(z) then writeln(g,'YES') else writeln(g,'NO');
  close(g);
end.