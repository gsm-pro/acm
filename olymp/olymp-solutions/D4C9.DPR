{$apptype console}
var
  a:array[1..55] of longint;
  e:array[1..100000] of shortint;
  ans:array[1..10] of longint;
  i,j,t,m,n:longint;
Procedure Rec(x,h:longint);
var
  i,w:longint;
  ok:boolean;
begin
  if h=n+1 then begin
    for i:=1 to n do write(ans[i],' ');
    halt(0);
  end;
  for w:=x to m do
    if (e[a[w]]>0) then begin
      if (h<>1)and(ans[h-1]=a[w]) then continue;
      dec(e[a[w]]);
      ans[h]:=a[w];
      ok:=true;
      for i:=1 to h-1 do begin
        dec(e[ans[h]-ans[i]]);
        if e[ans[h]-ans[i]]<0 then ok:=false;
      end;
      if ok then rec(w+1,h+1);
      for i:=1 to h-1 do inc(e[ans[h]-ans[i]]);
      inc(e[a[w]]);
    end;
end;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(m);
  for i:=1 to m do read(a[i]);
  for i:=1 to m-1 do
    for j:=1 to m-1 do
      if a[j]>a[j+1] then begin
        t:=a[j];
        a[j]:=a[j+1];
        a[j+1]:=t;
      end;
  for i:=1 to m do inc(e[a[i]]);
  n:=round(1+sqrt(1+8*m)) div 2-1;
  rec(1,1);
end.