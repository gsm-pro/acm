{$APPTYPE CONSOLE}
var
  a:array[1..100,1..100] of byte;
  vert:array[1..100] of boolean;
  way:array[1..100] of longint;
  n,i,j,k,kol,v,q:longint;
  z:boolean;
procedure DFS(v:longint);
var
  i:longint;
begin
  vert[v]:=False;
  inc(k);
  way[k]:=v;
  for i:=1 to n do
    if (a[v,i]<>0)and(vert[i]) then DFS(i);
end;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  for i:=1 to n do begin
    read(k);
    for j:=1 to k do begin
      read(q);
      a[i,q]:=1;
    end;
  end;
  fillchar(vert,sizeof(vert),true);
  k:=0;
  v:=0;
  repeat
    z:=False;
    for i:=1 to n do
      if vert[i] then begin
        kol:=0;
        for j:=1 to n do if a[i,j]<>0 then inc(kol);
        if kol=0 then begin
          z:=true;
          v:=i;
          break;
        end;
      end;
    if v=0 then break;
    for i:=1 to n do a[i,v]:=0;
    if z then DFS(v);
  until z=False;
  for i:=1 to n do if way[i]=0 then begin
    v:=0;
    break;
  end;
  if v=0 then write(0) else for i:=1 to n do write(way[i],' ');
end.