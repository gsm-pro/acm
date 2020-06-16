{$APPTYPE CONSOLE}
const
  MAXN=500;
  inf=1000000;
type
  integer=smallint;
type
  tCell=record
    x,y,A:longint;
  end;
var
  N,N2:integer;
  W:longint;
  x0,y0,H:longint;
  cells:array[1..MAXN] of tCell;
  cells2:array[1..MAXN] of tCell;
  sum:array[0..MAXN] of longint;
procedure ReadData;
var
  i:integer;
begin
  reset(input,'input.txt');
  read(N,W);
  for i:=1 to N do read(cells[i].x,cells[i].y,cells[i].A);
end;
procedure swap(var c1,c2:tCell);
var
  t:tCell;
begin
  t:=c1;
  c1:=c2;
  c2:=t;
end;
procedure SortX;
var
  i,j:integer;
begin
  for i:=1 to N do
    for j:=i to N do
      if cells[i].x>cells[j].x then swap(cells[i],cells[j]);
end;
procedure Solve;
var
  i,j,c1,c2:integer;
  l,r,m:longint;
  b:boolean;
  procedure PrepareCells2(x,h:longint);
  var
    j:integer;
  begin
    N2:=0;
    for j:=i to N do
      if (cells[j].x<x+h) then begin
        inc(N2);
        cells2[N2]:=cells[j];
      end;
    end;
  procedure SortCells2Y;
  var
    i:integer;
    procedure Heapify(i,hs:integer);
    var
      l,r,largest:integer;
    begin
      while true do begin
        l:=2*i;
        r:=2*i+1;
        largest:=i;
        if (l<=hs)and(cells2[l].y<cells2[largest].y) then largest:=l;
        if (r<=hs)and(cells2[r].y<cells2[largest].y) then largest:=r;
        if largest=i then break;
        swap(cells2[i], cells2[largest]);
        i:=largest;
      end;
    end;
  begin
    for i:=(N2 div 2) downto 1 do Heapify(i,N2);
    for i:=N2 downto 2 do begin
      swap(cells2[1],cells2[i]);
      Heapify(1,i-1);
    end;
  end;
  procedure PrepareSum;
  var
    i:integer;
  begin
    sum[0]:=0;
    for i:=1 to N2 do sum[i]:=sum[i-1]+cells2[i].A;
  end;
  function GetCell(y:longint):integer;
  var
    l,r,m:integer;
  begin
    l:=1;
    r:=N2;
    while l<r do begin
      m:=(l+r) div 2+(l+r) mod 2;
      if (y>cells2[m].y-1) then r:=m-1;
      if (y<=cells2[m].y-1) then l:=m;
    end;
    GetCell:=l;
  end;
begin
  H:=inf;
  SortX;
  for i:=1 to N do begin
    l:=1;
    r:=10001;
    while l<r do begin
      m:=(l+r) shr 1;
      b:=false;
      PrepareCells2(cells[i].x, m);
      SortCells2Y;
      PrepareSum;
      for j:=1 to N2 do begin
        c1:=j;
        c2:=GetCell(cells2[j].y-m);
        if (sum[c2]-sum[c1-1]>=W) then b:=true;
        if (sum[c2]-sum[c1-1]>=W) and (H>m) then begin
          H:=m;
          x0:=cells[i].x;
          y0:=cells2[j].y;
        end;
      end;
      if b then r:=m else l:=m+1;
    end;
  end;
end;
procedure WriteData;
begin
  rewrite(output,'output.txt');
  if H=inf then write('NO SOLUTION')
           else write(x0,' ',y0,' ',x0+H,' ',y0-H);
end;
begin
  ReadData;
  Solve;
  WriteData;
end.