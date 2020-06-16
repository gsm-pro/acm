{$APPTYPE CONSOLE}
var
  a,b,n,p,k,i:longint;
  z:array[0..100000] of longint;
  list,ans:array[1..100000] of longint;
  vert:array[0..100000] of boolean;
procedure BFS(v:longint);
var
  i,k,p,q:longint;
  w,t:int64;
begin
  fillchar(list,sizeof(list),0);
  list[1]:=v;
  vert[v]:=False;
  z[v]:=0;
  p:=1;
  q:=1;
  while p<=q do begin
    k:=list[p];
    inc(p);
    t:=1;
    for i:=1 to 3 do begin
      t:=t*k;
      w:=(t+1)mod n;
      if vert[w] then begin
        vert[w]:=False;
        z[w]:=k;
        if w=b then exit;
        inc(q);
        list[q]:=w;
      end;
    end;
  end;
end;
begin
  read(n,a,b);
  fillchar(z,sizeof(z),-1);
  fillchar(vert,sizeof(vert),True);
  BFS(a);
  if z[b]=-1 then write(-1) else begin
    k:=0;
    p:=b;
    while p<>a do begin
      inc(k);
      ans[k]:=p;
      p:=z[p];
    end;
    inc(k);
    ans[k]:=a;
    writeln(k-1);
    for i:=k downto 1 do write(ans[i],' ');
  end;
end.