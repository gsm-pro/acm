{$apptype console}
type
  int=longint;
const
  dx_kon    : array[1..8] of int = (-1,-1, 1, 1, 2,-2, 2,-2);
  dy_kon    : array[1..8] of int = ( 2,-2, 2,-2, 1,-1,-1, 1);
  dx_korol  : array[1..8] of int = (-1,-1,-1, 1, 1, 1, 0, 0);
  dy_korol  : array[1..8] of int = (-1, 1, 0,-1, 1, 0, 1,-1);
  dx_peshka : array[1..2] of int = (-1,-1);
  dy_peshka : array[1..2] of int = (-1, 1);
var
  a,aa:array[-1..202,-1..202] of char;
  n,i,j,kol:int;
Procedure dfs_u(x,y,g:int);
begin
  if (a[x][y] in ['A'..'Z'])and(g<>0) then exit;
  if a[x][y] in ['a'..'z'] then begin
    aa[x][y]:='+';
    exit;
  end;
  if a[x][y]='.' then aa[x,y]:='+';
  dfs_u(x-1,y,g+1);
end;
Procedure dfs_d(x,y,g:int);
begin
  if (a[x][y] in ['A'..'Z'])and(g<>0) then exit;
  if a[x][y] in ['a'..'z'] then begin
    aa[x][y]:='+';
    exit;
  end;
  if a[x][y]='.' then aa[x,y]:='+';
  dfs_d(x+1,y,g+1);
end;
Procedure dfs_l(x,y,g:int);
begin
  if (a[x][y] in ['A'..'Z'])and(g<>0) then exit;
  if a[x][y] in ['a'..'z'] then begin
    aa[x][y]:='+';
    exit;
  end;
  if a[x][y]='.' then aa[x,y]:='+';
  dfs_l(x,y-1,g+1);
end;
Procedure dfs_r(x,y,g:int);
begin
  if (a[x][y] in ['A'..'Z'])and(g<>0) then exit;
  if a[x][y] in ['a'..'z'] then begin
    aa[x][y]:='+';
    exit;
  end;
  if a[x][y]='.' then aa[x,y]:='+';
  dfs_r(x,y+1,g+1);
end;
Procedure dfs_ul(x,y,g:int);
begin
  if (a[x][y] in ['A'..'Z'])and(g<>0) then exit;
  if a[x][y] in ['a'..'z'] then begin
    aa[x][y]:='+';
    exit;
  end;
  if a[x][y]='.' then aa[x,y]:='+';
  dfs_ul(x-1,y-1,g+1);
end;
Procedure dfs_ur(x,y,g:int);
begin
  if (a[x][y] in ['A'..'Z'])and(g<>0) then exit;
  if a[x][y] in ['a'..'z'] then begin
    aa[x][y]:='+';
    exit;
  end;
  if a[x][y]='.' then aa[x,y]:='+';
  dfs_ur(x-1,y+1,g+1);
end;
Procedure dfs_dl(x,y,g:int);
begin
  if (a[x][y] in ['A'..'Z'])and(g<>0) then exit;
  if a[x][y] in ['a'..'z'] then begin
    aa[x][y]:='+';
    exit;
  end;
  if a[x][y]='.' then aa[x,y]:='+';
  dfs_dl(x+1,y-1,g+1);
end;
Procedure dfs_dr(x,y,g:int);
begin
  if (a[x][y] in ['A'..'Z'])and(g<>0) then exit;
  if a[x][y] in ['a'..'z'] then begin
    aa[x][y]:='+';
    exit;
  end;
  if a[x][y]='.' then aa[x,y]:='+';
  dfs_dr(x+1,y+1,g+1);
end;
Procedure kon(x,y:int);
var
  i:int;
begin
  for i:=1 to 8 do
    if (a[x+dx_kon[i]][y+dy_kon[i]] in ['a'..'z','.']) then
       aa[x+dx_kon[i]][y+dy_kon[i]]:='+';
end;
Procedure peshka(x,y:int);
var
  i:int;
begin
  for i:=1 to 2 do
    if (a[x+dx_peshka[i]][y+dy_peshka[i]] in ['a'..'z','.']) then
       aa[x+dx_peshka[i]][y+dy_peshka[i]]:='+';
end;
Procedure korol(x,y:int);
var
  i:int;
begin
  for i:=1 to 8 do
    if (a[x+dx_korol[i]][y+dy_korol[i]] in ['a'..'z','.']) then
       aa[x+dx_korol[i]][y+dy_korol[i]]:='+';
end;
Procedure slon(x,y:int);
begin
  dfs_ul(x,y,0);
  dfs_ur(x,y,0);
  dfs_dr(x,y,0);
  dfs_dl(x,y,0);
end;
Procedure ladja(x,y:int);
begin
  dfs_u(x,y,0);
  dfs_d(x,y,0);
  dfs_l(x,y,0);
  dfs_r(x,y,0);
end;
Procedure ferz(x,y:int);
begin
  slon(x,y);
  ladja(x,y);
end;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(n);
  fillchar(a,sizeof(a),'H');
  fillchar(aa,sizeof(aa),'-');
  for i:=1 to n do begin
    for j:=1 to n do read(a[i][j]);
    readln;
  end;
  for i:=1 to n do
    for j:=1 to n do begin
      if a[i][j]='K' then korol(i,j);
      if a[i][j]='F' then ferz(i,j);
      if a[i][j]='L' then ladja(i,j);
      if a[i][j]='S' then slon(i,j);
      if a[i][j]='H' then kon(i,j);
      if a[i][j]='P' then peshka(i,j);
    end;
  kol:=0;
  for i:=1 to n do
    for j:=1 to n do
      if aa[i][j]='+' then inc(kol);
  write(kol);
end.