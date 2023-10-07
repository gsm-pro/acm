{$APPTYPE CONSOLE}
uses math;
var
  a,d:array[0..200,0..200] of byte;
  i,j,k,n,m,maxs,s,x1,y1,x2,y2,q:longint;
begin
  read(n,m);
  for i:=1 to n do
    for j:=1 to m do begin
      read(a[i,j]);
      if a[i,j]=1 then d[i,j]:=i else d[i,j]:=d[i-1,j];
    end;
  x1:=0;y1:=0;x2:=0;y2:=0;maxs:=0;
  for i:=1 to n do
    for j:=1 to m do begin
      q:=0;
      for k:=1 to m-j+1 do begin
        q:=max(q,d[i,j+k-1]);
        s:=k*(i-q);
        if s>maxs then begin
          maxs:=s;
          x1:=q+1;
          y1:=j;
          x2:=i;
          y2:=j+k-1;
        end;
      end;
    end;
  write(x1,' ',y1,' ',x2,' ',y2);
end.