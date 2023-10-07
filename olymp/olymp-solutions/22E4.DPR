{$APPTYPE CONSOLE}
{$MAXSTACKSIZE 50000000}
uses SysUtils,Math;
Var
  i,j,n,m,p,s:longint;
  w:string;
  a:array[0..801,0..801] of longint;
  v:array[0..801,0..801] of boolean;
Procedure DFS(x,y:word);
begin
  if (v[x,y])or(a[x,y]=-1)or(x>n)or(y<1)or(y>m) then exit;
  v[x,y]:=True;
  DFS(x+1,y);
  DFS(x,y-1);
  DFS(x,y+1);
end;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(n,m);
  fillchar(a,sizeof(a),-1);
  for i:=1 to n do begin
    readln(w);
    for j:=1 to length(w) do a[i,j]:=StrToIntDef(w[j],-1);
  end;
  DFS(1,1);
  if not v[n,m] then begin
    write('SEE YOU LATER');
    halt;
  end;
  for i:=1 to n do
    for j:=1 to m do
      if not v[i,j] then a[i,j]:=-1;
  for i:=1 to n do begin
    p:=0;
    s:=0;
    for j:=1 to m+1 do
      if a[i,j]<>-1 then begin
        if a[i,j-1]=-1 then p:=j;
        inc(s,a[i,j]);
      end else
      if (p<>0)and(a[i,j-1]<>-1) then begin
        a[i,p]:=s;
        s:=0;
      end;
    for j:=1 to m do
      if a[i,j]<>-1 then begin
        if a[i,j-1]<>-1 then a[i,j]:=p;
        if a[i,j-1] =-1 then p:=a[i,j];
      end;
  end;
  fillchar(a[0],sizeof(a[0]),0);
  a[0,1]:=0;
  for i:=1 to n do begin
    p:=0;
    s:=0;
    for j:=1 to m do if (a[i,j]<>-1)and(a[i-1,j]<>-1) then inc(a[i,j],a[i-1,j]);
    for j:=1 to m+1 do
      if a[i,j]<>-1 then begin
        if a[i,j-1]=-1 then p:=j;
        s:=max(s,a[i,j]);
      end else
      if (p<>0)and(a[i,j-1]<>-1) then begin
        a[i,p]:=s;
        s:=0;
      end;
    for j:=1 to m do
      if a[i,j]<>-1 then begin
        if a[i,j-1]<>-1 then a[i,j]:=p;
        if a[i,j-1] =-1 then p:=a[i,j];
      end;
  end;
  write(a[n,m]);
end.