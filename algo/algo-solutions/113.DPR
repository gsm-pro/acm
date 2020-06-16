{$APPTYPE CONSOLE}
var
  a:array[1..40,1..40] of byte;
  list,d:array[1..40] of longint;
  vert:array[1..40] of boolean;
  n,k,v1,v2,z,tp,dl,m:longint;
procedure BFS(v:longint);
var
  i,k,p,q:longint;
begin
  fillchar(list,sizeof(list),0);
  list[1]:=v;
  vert[v]:=False;
  p:=1;
  q:=1;
  while p<=q do begin 
    k:=list[p];
    inc(p);
    for i:=1 to n do
      if a[k,i]<>255 then begin
        if d[i]>d[k]+a[k,i] then begin
          d[i]:=d[k]+a[k,i];
          p:=1;
          break;
        end;
        if vert[i] then begin
          inc(q);
          list[q]:=i;
          vert[i]:=False;
        end;  
      end;
  end;
end;
begin
  readln(n,k);
  fillchar(a,sizeof(a),255);
  for z:=1 to k do begin
    read(tp);
    if tp=1 then begin
      readln(v1,v2,dl);
      if a[v1,v2]>dl then a[v1,v2]:=dl;
    end;
    if tp=2 then begin
      readln(v1,v2);
      if v1=v2 then begin
        writeln('0');
        continue;
      end;
      for m:=1 to 40 do d[m]:=1000000000;
      fillchar(vert,sizeof(vert),true);
      d[v1]:=0;
      BFS(v1);
      if vert[v2] then writeln('-1')
                  else writeln(d[v2]);
    end;
  end;
end.