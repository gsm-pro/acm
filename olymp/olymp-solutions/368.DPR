{$apptype console}
var
  a:array[1..40,1..40] of char;
  i,j,k,n,m,x,y,_x,_y,tek,kol:longint;
  map:array[1..40,1..40] of longint;
  qx,qy:array[1..500000] of byte;
Procedure BFS(x,y:longint);
const
  dx:array[1..4] of longint=(-1,1,0,0);
  dy:array[1..4] of longint=( 0,0,1,-1);
var
  p,q,xx,yy,_x,_y,i:longint;
begin
  fillchar(map,sizeof(map),-1);
  map[x,y]:=k;
  qx[1]:=x;
  qy[1]:=y;
  p:=1;
  q:=1;
  while p<=q do begin
    xx:=qx[p];
    yy:=qy[p];
    inc(p);
    for i:=1 to 4 do begin
      _x:=xx+dx[i];
      _y:=yy+dy[i];
      if (_x<1)or(_x>n)or(_y<1)or(_y>m) then continue;
      if a[_x,_y]>a[xx,yy] then continue;
      if (a[_x,_y]=a[xx,yy])and(map[_x,_y]>=map[xx,yy]-1) then continue;
      if a[_x,_y]<a[xx,yy] then map[_x,_y]:=k;
      if a[_x,_y]=a[xx,yy] then map[_x,_y]:=map[xx,yy]-1;
      inc(q);
      qx[q]:=_x;
      qy[q]:=_y;
    end;
  end;
end;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(n,m,k);
  fillchar(a,sizeof(a),' ');
  for i:=1 to n do begin
    for j:=1 to m do read(a[i,j]);
    readln;
  end;
  _x:=0;
  _y:=0;
  kol:=-1;
  for x:=1 to n do
    for y:=1 to m do begin
      BFS(x,y);
      tek:=0;
      for i:=1 to n do
        for j:=1 to m do
          if map[i,j]>-1 then inc(tek);
      if tek>kol then begin
        kol:=tek;
        _x:=x;
        _y:=y;
      end;
    end;
  BFS(_x,_y);
  for i:=1 to n do
    for j:=1 to m do
      if map[i,j]>-1 then a[i,j]:='~';
  a[_x,_y]:='*';
  for i:=1 to n do begin
    for j:=1 to m do write(a[i,j]);
    writeln;
  end;
end.