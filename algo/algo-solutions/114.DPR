{$APPTYPE CONSOLE}
var
  a:array[1..100,1..100] of byte;
  vert:array[1..100] of boolean;
  list,pr,way:array[1..100] of longint;
  n,i,j,v1,v2,m:longint;
procedure BFS(v:byte);
var i,k,p,q:byte;
begin
  fillchar(list,sizeof(list),0);
  list[1]:=v;
  vert[v]:=false;
  p:=1;
  q:=1;
  while p<=q do begin
    k:=list[p];
    inc(p);
    for i:=1 to n do
      if (a[k,i]=1)and(vert[i]) then begin
        vert[i]:=false;
        pr[i]:=k;
        inc(q);
        list[q]:=i;
      end;
  end;
end;
begin
  readln(n,v1,v2);
  for i:=1 to n do
    for j:=1 to n do read(a[i,j]);
  fillchar(vert,sizeof(vert),true);
  fillchar(pr,sizeof(pr),0);
  BFS(v1);
  if vert[v2] then begin
    writeln('-1');
    halt(0);
  end;
  m:=1;
  way[m]:=v2;
  i:=v2;
  while i<>v1 do begin
    inc(m);
    i:=pr[i];
    way[m]:=i;
  end;
  writeln(m-1);
  for i:=m downto 1 do write(way[i],' ');
end.