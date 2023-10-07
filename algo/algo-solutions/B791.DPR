{$APPTYPE CONSOLE}
var
  a:array[1..100,1..100] of byte;
  vert:array[1..100] of boolean;
  way:array[1..500] of longint;
  n,i,j,v1,v2,k,p:longint;
  stop:boolean;
procedure DFS(v:longint);
var
  i:longint;
  z:boolean;
begin
  z:=False;
  if v=v2 then stop:=True;
  if stop then exit;
  vert[v]:=False;
  for i:=1 to n do begin
    if stop then exit;
    z:=False;
    if (a[v,i]<>0)and(vert[i]) then begin
      inc(k);
      way[k]:=i;
      z:=true;
      DFS(i);
    end;
  end;
  if (z=False)and(v<>v2) then begin
    way[k]:=0;
    dec(k);
  end;
end;
begin
  readln(n,v1,v2);
  for i:=1 to n do
    for j:=1 to n do read(a[i,j]);
  fillchar(vert,sizeof(vert),true);
  stop:=False;
  k:=1;
  way[1]:=v1;
  DFS(v1);
  p:=-1;
  for i:=1 to k do if way[i]=v2 then begin
    p:=i;
    break;
  end;
  if p=-1 then  begin
    writeln('-1');
    halt(0);
  end;
  writeln(p-1);
  for i:=1 to p do write(way[i],' ');
end.