{$APPTYPE CONSOLE}
var
  n,k,ans:longint;
  p:array[1..7,1..7] of longint;
procedure brute(k,x1,y1:longint);
const
  dx:array[1..8] of longint=(-1,-1,1,1,2,-2,2,-2);
  dy:array[1..8] of longint=(2,-2,2,-2,1,-1,-1,1);
var
  i,x,y,nx,ny:longint;
begin
  if k=0 then begin
    inc(ans);
    exit;
  end;
  if y1>n then begin
    y1:=1;
    inc(x1);
  end;
  if x1>n then exit;
  for x:=x1 to n do begin
    if x<>x1 then y1:=1;
    for y:=y1 to n do
      if p[x,y]<>0 then continue else begin
        p[x,y]:=1000000;
        for i:=1 to 8 do begin
          nx:=x+dx[i];
          ny:=y+dy[i];
          if (nx<1)or(nx>n)or(ny<1)or(ny>n) then continue;
          inc(p[nx,ny]);
        end;
        brute(k-1,x,y+1);
        for i:=1 to 8 do begin
          nx:=x+dx[i];
          ny:=y+dy[i];
          if (nx<1)or(nx>n)or(ny<1)or(ny>n) then continue;
          dec(p[nx,ny]);
        end;
        p[x,y]:=0;
      end;
    end;
end;
begin
  readln(n,k);
  ans:=0;
  fillchar(p,sizeof(p),0);
  brute(k,1,1);
  writeln(ans);
end.