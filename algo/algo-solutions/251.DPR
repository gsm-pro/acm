{$APPTYPE CONSOLE}
type
  rec=record
    k:longint;
    t:string[5];
    text:string;
  end;
var
  c:char;
  n,id,p,i,j,k:longint;
  z:array[0..500,1..500] of rec;
  kol:array[0..500] of longint;
  tmp:rec;
  used:array[1..500] of boolean;
Procedure DFS(x,h:longint);
var
  i,j:longint;
begin
  used[x]:=True;
  for i:=1 to kol[x] do
    if not used[z[x,i].k] then begin
      for j:=1 to h do write('-');
      writeln(z[x,i].text);
      DFS(z[x,i].k,h+1);
    end;
end;
begin
  while not seekeof do begin
    read(id);
    read(p);
    if p=-1 then p:=0;
    inc(kol[p]);
    z[p,kol[p]].k:=id;
    read(c);
    read(z[p,kol[p]].t);
    read(c);
    readln(z[p,kol[p]].text);
  end;
  n:=500;
  while kol[n]=0 do dec(n);
  for i:=0 to n do
    for j:=1 to kol[i]-1 do
      for k:=1 to kol[i]-1 do
        if z[i,k].t>z[i,k+1].t then begin
          tmp:=z[i,k];
          z[i,k]:=z[i,k+1];
          z[i,k+1]:=tmp;
        end;
  fillchar(used,sizeof(used),False);
  for i:=1 to kol[0] do begin
    writeln(z[0,i].text);
    DFS(z[0,i].k,1);
  end;
end.