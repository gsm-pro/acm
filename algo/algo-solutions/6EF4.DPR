{$APPTYPE CONSOLE}
uses math;
const INF=10000000;
var
  a:array[1..200,1..200] of longint;
  c,n,i,v1,v2,m,ans:longint;
  d:array[1..200,1..3] of longint;
procedure BFS(v:longint);
var
  i,k,p,q,t:longint;
  list:array[1..40000] of longint;
  used:array[1..200] of boolean;
begin
  fillchar(used,sizeof(used),False);
  fillchar(list,sizeof(list),0);
  list[1]:=v;
  used[v]:=True;
  p:=1;
  q:=1;
  while p<=q do begin
    k:=list[p];
    inc(p);
    for i:=1 to n do
      if a[k,i]>0 then begin
        if used[i] then begin
          t:=0;
          case a[k,i] of
            1:t:=min(d[k,2],d[k,3]);
            2:t:=min(d[k,1],d[k,3]);
            3:t:=min(d[k,1],d[k,2]);
          end;
          if t+1<d[i,a[k,i]] then begin
            d[i,a[k,i]]:=t+1;
            p:=1;
          end;
        end;
        if not used[i] then begin
          inc(q);
          list[q]:=i;
          used[i]:=True;
          case a[k,i] of
            1:d[i,a[k,i]]:=min(d[k,2],d[k,3])+1;
            2:d[i,a[k,i]]:=min(d[k,1],d[k,3])+1;
            3:d[i,a[k,i]]:=min(d[k,1],d[k,2])+1;
          end;
          if d[i,a[k,i]]>INF then d[i,a[k,i]]:=INF;
        end;
      end;
  end;
end;
begin
  read(n,m);
  for i:=1 to m do begin
    read(v1,v2,c);
    a[v1,v2]:=c;
  end;
  for i:=2 to 200 do begin
    d[i,1]:=INF;d[i,2]:=INF;d[i,3]:=INF;
  end;
  BFS(1);
  ans:=min(min(d[n,1],d[n,2]),d[n,3]);
  if ans=INF then write(-1) else write(ans);
end.