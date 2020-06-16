{$APPTYPE CONSOLE}
const
  INF=99999999;
var
  z:array[1..16,1..16] of char;
  d:array[1..16,1..16] of longint;
  vert:array[1..16,1..16] of boolean;
  n,m,x,y,i,j:longint;
  st:string;
  w:set of char;
Function Dost(x1,y1,x2,y2,t:longint):boolean;
var
  q:boolean;
begin
  if (x2<1)or(x2>n)or(y2<1)or(y2>m)or
     not (z[x2,y2] in ['.','s']) then begin
    Dost:=False;
    exit;
  end;
  q:=False;
  case t of
    1:if ((z[x1-1,y1] in w)and(z[x1-1,y1+1] in w))or
         ((z[x1,y1+1] in w)and(z[x1,y1+2] in w))then q:=True;
    2:if ((z[x1,y1-2] in w)and(z[x1,y1-1] in w))or
         ((z[x1-1,y1-1] in w)and(z[x1-1,y1] in w))then q:=True;
    3:if ((z[x1,y1+1] in w)and(z[x1,y1+2] in w))or
         ((z[x1+1,y1] in w)and(z[x1+1,y1+1] in w))then q:=True;
    4:if ((z[x1,y1-2] in w)and(z[x1,y1-1] in w))or
         ((z[x1+1,y1-1] in w)and(z[x1+1,y1] in w))then q:=True;
    5:if ((z[x1+1,y1] in w)and(z[x1+2,y1] in w))or
         ((z[x1,y1+1] in w)and(z[x1+1,y1+1] in w))then q:=True;
    6:if ((z[x1-2,y1] in w)and(z[x1-1,y1] in w))or
         ((z[x1-1,y1-1] in w)and(z[x1,y1-1] in w))then q:=True;
    7:if ((z[x1+1,y1] in w)and(z[x1+2,y1] in w))or
         ((z[x1,y1-1] in w)and(z[x1+1,y1-1] in w))then q:=True;
    8:if ((z[x1-2,y1] in w)and(z[x1-1,y1] in w))or
         ((z[x1-1,y1+1] in w)and(z[x1,y1+1] in w))then q:=True;
  end;
  Dost:=q;
end;
procedure BFS(x,y:longint);
const
  dx:array[1..8] of longint=(-1,-1,1,1,2,-2,2,-2);
  dy:array[1..8] of longint=(2,-2,2,-2,1,-1,-1,1);
var
  i,p,q,_x,_y:longint;
  list:array[1..500,1..2] of longint;
begin
  fillchar(list,sizeof(list),0);
  list[1,1]:=x;
  list[1,2]:=y;
  vert[x,y]:=False;
  p:=1;
  q:=1;
  while p<=q do begin
    x:=list[p,1];
    y:=list[p,2];
    inc(p);
    for i:=1 to 8 do begin
      _x:=x+dx[i];
      _y:=y+dy[i];
      if not Dost(x,y,_x,_y,i) then continue;
      if d[_x,_y]>d[x,y]+1 then begin
        d[_x,_y]:=d[x,y]+1;
        p:=1;
        break;
      end;
      if vert[_x,_y] then begin
        inc(q);
        list[q,1]:=_x;
        list[q,2]:=_y;
        vert[_x,_y]:=False;
      end;
    end;
  end;
end;
begin
  w:=['.','+','s','h'];
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(n,m);
  x:=0;y:=0;
  for i:=1 to n do begin
    readln(st);
    for j:=1 to m do begin
      z[i,j]:=st[j];
      if z[i,j]='h' then begin x:=i;y:=j;end;
    end;
  end;
  for i:=1 to n do
    for j:=1 to m do d[i,j]:=INF;
  d[x,y]:=0;
  fillchar(vert,sizeof(vert),True);
  BFS(x,y);
  x:=0;y:=0;
  for i:=1 to n do
    for j:=1 to m do
      if z[i,j]='s' then begin x:=i;y:=j;end;
  if d[x,y]=INF then write(-1) else write(d[x,y]);
end.