{$APPTYPE CONSOLE}
uses Math;
type
  rb=record
    a,b,v:longint;
  end;
Var
  m,n,i,cost1,cost2,x,aa,bb,l,kol,old_id,new_id,j:longint;
  tree_id:array[1..100] of longint;
  g,gg,w:array[1..6000] of rb;
  z:array[1..100,1..100] of longint;
Procedure QSort(l,r:longint);
var
  m,i,j,t:longint;
begin
  m:=w[(l+r) div 2].v;
  i:=l;
  j:=r;
  repeat
    while w[i].v<m do inc(i);
    while w[j].v>m do dec(j);
    if i<=j then begin
      t:=w[i].v;w[i].v:=w[j].v;w[j].v:=t;
      t:=w[i].a;w[i].a:=w[j].a;w[j].a:=t;
      t:=w[i].b;w[i].b:=w[j].b;w[j].b:=t;
      inc(i);dec(j);
    end;
  until i>j;
  if j>l then QSort(l,j);
  if i<r then QSort(i,r);
end;
Begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(n,x,m);
  for i:=1 to m do with g[i] do read(a,b,v);
  w:=g;
  QSort(1,m);
  g:=w;
  cost1:=0;
  for i:=1 to n do tree_id[i]:=i;
  for i:=1 to m do begin
    aa:=g[i].a;
    bb:=g[i].b;
    l:=g[i].v;
    if tree_id[aa]<>tree_id[bb] then begin
      inc(cost1,l);
      old_id:=tree_id[bb];
      new_id:=tree_id[aa];
      for j:=1 to n do
        if tree_id[j]=old_id then tree_id[j]:=new_id;
    end;
  end;
  for i:=1 to m do begin
    z[g[i].a,g[i].b]:=g[i].v;
    z[g[i].b,g[i].a]:=g[i].v;
  end;
  for i:=1 to n do
    for j:=1 to n do
      if (i<>x)and(j<>x)and(z[i,x]<>0)and(z[j,x]<>0) then begin
        if z[i,j]<>0 then z[i,j]:=min(z[i,j],z[i,x]+z[j,x]);
        if z[i,j]=0 then z[i,j]:=z[i,x]+z[j,x];
      end;
  for i:=1 to n do begin
    z[i,i]:=0;
    z[i,x]:=0;
    z[x,i]:=0;
  end;
  m:=0;
  for i:=1 to n-1 do
    for j:=i+1 to n do
      if z[i,j]<>0 then begin
        inc(m);
        gg[m].a:=i;
        gg[m].b:=j;
        gg[m].v:=z[i,j];
      end;
  w:=gg;
  QSort(1,m);
  gg:=w;
  cost2:=0;
  for i:=1 to n do tree_id[i]:=i;
  for i:=1 to m do begin
    aa:=gg[i].a;
    bb:=gg[i].b;
    l:=gg[i].v;
    if tree_id[aa]<>tree_id[bb] then begin
      inc(cost2,l);
      old_id:=tree_id[bb];
      new_id:=tree_id[aa];
      for j:=1 to n do
        if tree_id[j]=old_id then tree_id[j]:=new_id;
    end;
  end;
  write(min(cost1,cost2));
end.