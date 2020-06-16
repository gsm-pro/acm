{$APPTYPE CONSOLE}
Var
  n,m,i,j,cnt,z,ans:longint;
  s:string;
  a:array[0..51,0..51] of char;
  c:array[0..51,0..51] of longint;
  tp:array[1..4] of longint;
  used:array[0..51,0..51] of boolean;
Procedure DFS(x,y,v:longint);
begin
  if used[x,y] then exit;
  c[x,y]:=v;
  used[x,y]:=True;
  if a[x+1,y]='*' then DFS(x+1,y,v);
  if a[x-1,y]='*' then DFS(x-1,y,v);
  if a[x,y+1]='*' then DFS(x,y+1,v);
  if a[x,y-1]='*' then DFS(x,y-1,v);
end;
Begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  while not seekeof do begin
    readln(n,m);
    fillchar(a,sizeof(a),'.');
    fillchar(c,sizeof(c),0);
    fillchar(used,sizeof(used),False);
    for i:=1 to n do begin
      readln(s);
      for j:=1 to m do a[i,j]:=s[j];
    end;
    cnt:=0;
    for i:=1 to n do
      for j:=1 to m do
        if (not used[i,j])and(a[i,j]='*') then begin
          inc(cnt);
          DFS(i,j,cnt);
        end;
    ans:=0;
    for z:=1 to cnt do begin
      fillchar(tp,sizeof(tp),0);
      for i:=1 to n do
        for j:=1 to m do begin
          if (c[i,j]=z)and(c[i+1,j]=z)and(c[i,j+1]=z)
            then inc(tp[1]);
          if (c[i,j]=z)and(c[i+1,j]=z)and(c[i,j-1]=z)
            then inc(tp[2]);
          if (c[i,j]=z)and(c[i-1,j]=z)and(c[i,j+1]=z)
            then inc(tp[3]);
          if (c[i,j]=z)and(c[i-1,j]=z)and(c[i,j-1]=z)
            then inc(tp[4]);
        end;
      if tp[1]+tp[2]+tp[3]+tp[4]=1 then inc(ans);
    end;
    writeln(ans);
  end;
end.