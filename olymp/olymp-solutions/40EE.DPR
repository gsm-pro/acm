{$APPTYPE CONSOLE}
uses SysUtils,math;
const
  INF=round(1e9);
Var
  a,b:array[0..183,0..183] of longint;
  n,m,i,j,p,t:longint;
  s:string;
Begin
  reset(input,'input.txt');
  readln(n,m);
  for i:=1 to n do begin
    readln(s);
    for j:=1 to m do a[i,j]:=StrToInt(s[j]);
  end;
  for i:=0 to 183 do
    for j:=0 to 183 do
      if a[i,j]=1 then b[i,j]:=0 else b[i,j]:=INF;
  for p:=1 to n+m-2 do
    for i:=1 to n do
      for j:=1 to m do
        if b[i,j]=INF then begin
          t:=min(min(b[i-1,j],b[i+1,j]),min(b[i,j-1],b[i,j+1]));
          if t=p-1 then b[i,j]:=t+1;
        end;
  rewrite(output,'output.txt');
  for i:=1 to n do begin
    for j:=1 to m do write(b[i,j],' ');
    writeln;
  end;
end.