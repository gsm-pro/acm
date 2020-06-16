{$APPTYPE CONSOLE}
const
  N=8;
type
  tpoint=record
    u,v:longint;
  end;
var
  ans,s:string;
  paint:array[1..N,1..N] of longint;
  start,finish,tmp,cur:tpoint;
  from:array[1..N,1..N] of tpoint;
  i,h,t:longint;
  q:array[1..N*N] of tpoint;
procedure str2point(s:string;var a:tpoint);
begin
  a.u:=ord(s[1])-ord('A')+1;
  a.v:=ord(s[2])-ord('0');
end;
function point2str(var a:tpoint):string;
begin
  point2str:=chr(ord('A')+a.u-1)+chr(ord('0')+a.v);
end;
procedure OutData;
Var
  cur:tpoint;
begin
  ans:=point2str(finish);
  cur:=finish;
  while (cur.u<>start.u)or(cur.v<>start.v) do begin
    cur:=from[cur.u,cur.v];
    ans:=point2str(cur)+ans;
  end;
  write(ans);
  halt;
end;
procedure add(u,v:longint;fr:tpoint);
begin
  if (u<1)or(u>N) then exit;
  if (v<1)or(v>N) then exit;
  if paint[u,v]<>0 then exit;
  from[u,v]:=fr;
  if (u=finish.u)and(v=finish.v) then OutData;
  paint[u,v]:=1;
  inc(t);
  q[t].u:=u;
  q[t].v:=v;
end;
procedure Solve;
begin
  h:=1;
  t:=1;
  q[1]:=start;
  while h<=t do begin
    cur:=q[h];
    inc(h);
    add(cur.u-2,cur.v-1,cur);
    add(cur.u-1,cur.v-2,cur);
    add(cur.u+2,cur.v-1,cur);
    add(cur.u+1,cur.v-2,cur);
    add(cur.u-2,cur.v+1,cur);
    add(cur.u-1,cur.v+2,cur);
    add(cur.u+2,cur.v+1,cur);
    add(cur.u+1,cur.v+2,cur);
  end;
  write(0);
  halt;
end;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(s);
  str2point(s,start);
  readln(s);
  str2point(s,finish);
  readln(s);
  fillchar(paint,sizeof(paint),0);
  for i:=0 to length(s) div 2-1 do begin
    str2point(s[i*2+1]+s[i*2+2],tmp);
    paint[tmp.u,tmp.v]:=1;
  end;
  Solve;
  OutData;
end.