{$APPTYPE CONSOLE}
uses math;
const
  INF=20000000;
type
  rec=record
    ac,al,bc,bl,cc,cl:longint;
  end;
var
  i,j,n,s,ans:longint;
  r:array[1..1000] of rec;
  d:array[0..1000,-1000..1000] of longint;
Begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n,s);
  for i:=1 to n do
    with r[i] do read(ac,al,bc,bl,cc,cl);
  for i:=0 to n do
    for j:=-1000 to 1000 do d[i,j]:=INF;
  d[0,0]:=0;
  for i:=1 to n do
    for j:=0 to s do begin
      if (r[i].ac>=0)and(j+r[i].ac<=s)
        then d[i,j+r[i].ac]:=min(d[i,j+r[i].ac],d[i-1,j]+r[i].al);
      if (r[i].bc>=0)and(j+r[i].bc<=s)
        then d[i,j+r[i].bc]:=min(d[i,j+r[i].bc],d[i-1,j]+r[i].bl);
      if (r[i].cc>=0)and(j+r[i].cc<=s)
        then d[i,j+r[i].cc]:=min(d[i,j+r[i].cc],d[i-1,j]+r[i].cl);
    end;
  ans:=INF;
  for i:=0 to s do ans:=min(ans,d[n,i]);
  if ans=INF then write(-1) else write(ans);
end.