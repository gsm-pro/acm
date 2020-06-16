{$APPTYPE CONSOLE}
uses SysUtils;
var
  used_row,used_col:array[1..9,1..9] of boolean;
  used_sq:array[1..3,1..3,1..9] of boolean;
  pole,ans:array[1..9,1..9] of byte;
  i,j:longint;
  s:string[1];
  w:boolean;
Procedure Rec(x,y:longint);
var
  i:longint;
begin
  if w then exit;
  if y=10 then begin
    inc(x);
    y:=1;
  end;
  if (x=10)and(y=1) then begin
    w:=True;
    exit;
  end;
  if w then exit;
  if pole[x,y]<>0 then begin
    ans[x,y]:=pole[x,y];
    Rec(x,y+1);
    exit;
  end;
  for i:=1 to 9 do begin
    if (used_row[x,i])or(used_col[y,i])or
       (used_sq[(x-1) div 3+1,(y-1) div 3+1,i]) then continue;
    ans[x,y]:=i;
    used_row[x,i]:=True;
    used_col[y,i]:=True;
    used_sq[(x-1) div 3+1,(y-1) div 3+1,i]:=True;
    Rec(x,y+1);
    if w then exit;
    used_row[x,i]:=False;
    used_col[y,i]:=False;
    used_sq[(x-1) div 3+1,(y-1) div 3+1,i]:=False;
    ans[x,y]:=0;
  end;
end;
begin
  fillchar(used_row,sizeof(used_row),False);
  fillchar(used_col,sizeof(used_col),False);
  fillchar(used_sq,sizeof(used_sq),False);
  for i:=1 to 9 do begin
    for j:=1 to 9 do begin
      read(s);
      pole[i,j]:=StrToInt(s);
      if pole[i,j]<>0 then begin
        used_row[i,pole[i,j]]:=True;
        used_col[j,pole[i,j]]:=True;
        used_sq[(i-1) div 3+1,(j-1) div 3+1,pole[i,j]]:=True;
      end;
    end;
    readln;
  end;
  Rec(1,1);
  for i:=1 to 9 do begin
    for j:=1 to 9 do write(ans[i,j]);
    writeln;
  end;
end.