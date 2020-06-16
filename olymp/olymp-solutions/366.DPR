{$APPTYPE CONSOLE}
var
  a:array[1..100,1..100] of longint;
  n1,n2:array[1..100] of longint;
  vert:array[1..100] of boolean;
  n,m,i,j,ans1,ans2:longint;
Procedure DFS(v:longint);
var
  i:longint;
begin
  vert[v]:=False;
  for i:=1 to n do
    if (vert[i])and(a[v,i]=1) then DFS(i);
end;
begin
  reset(input,'input.txt');
  read(n,m);
  fillchar(a,sizeof(a),0);
  for i:=1 to m do read(n1[i],n2[i]);
  ans1:=0;
  for i:=1 to m do begin
    fillchar(vert,sizeof(vert),true);
    DFS(n1[i]);
    if vert[n2[i]]=False then begin
      ans1:=i;
      break;
    end;
    a[n1[i],n2[i]]:=1;
    a[n2[i],n1[i]]:=1;
  end;
  ans2:=0;
  fillchar(a,sizeof(a),0);
  for i:=1 to m do begin
    fillchar(vert,sizeof(vert),true);
    DFS(n1[i]);
    if vert[n2[i]]=True then  ans2:=i;
    a[n1[i],n2[i]]:=1;
    a[n2[i],n1[i]]:=1;
  end;
  rewrite(output,'output.txt');
  writeln(ans1,' ',ans2);
end.