{$APPTYPE CONSOLE}
Var
  a:array[1..200,1..200] of char;
  used:array[1..200,1..200] of boolean;
  i,j,n,m,q,qm,k,km:longint;
Procedure Calc(x,y:longint);
begin
  if (x>n)or(x<1)or(y>m)or(y<1) then exit;
  if used[x,y] then exit;
  if a[x,y]='*' then inc(k);
  if a[x,y]='+' then begin
    inc(q);
    exit;
  end;
  used[x,y]:=True;
  Calc(x+1,y);
  Calc(x-1,y);
  Calc(x,y-1);
  Calc(x,y+1);
end;
Begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(n,m);
  for i:=1 to n do begin
    for j:=1 to m do read(a[i,j]);
    readln;
  end;
  qm:=0;km:=0;
  for i:=1 to n do
    for j:=1 to m do
      if (a[i,j]='*')and(not used[i,j]) then begin
        q:=0;k:=0;
        Calc(i,j);
        if q=qm then inc(km,k);
        if q>qm then begin
          qm:=q;
          km:=k;
        end;
      end;
  write(qm,' ',km);
end.