{$APPTYPE CONSOLE}
Var
  n,m,i,j:longint;
  w:string;
  a:array[0..80,0..80] of longint;
  code:integer;
begin
  readln(n,m);
  for i:=1 to n do begin
    readln(w);
    for j:=1 to m do
      if w[j]<>'*' then val(w[j],a[i,j],code)
                   else a[i,j]:=-1;
  end;
  for i:=0 to n do a[i,0]:=-1;
  for j:=0 to m do a[0,j]:=-1;
  for i:=1 to n do
    for j:=1 to m do begin
      if a[i,j]=-1 then continue;
      if ((i<>1)or(j<>1))and(a[i-1,j]=-1)and(a[i,j-1]=-1) then begin
        a[i,j]:=-1;
        continue;
      end;
      if (a[i-1,j]<>-1)and(a[i,j-1]<>-1) then
        if a[i-1,j]>=a[i,j-1] then a[i,j]:=a[i,j]+a[i-1,j]
                              else a[i,j]:=a[i,j]+a[i,j-1];
      if (a[i-1,j]= -1)and(a[i,j-1]<>-1) then a[i,j]:=a[i,j]+a[i,j-1];
      if (a[i-1,j]<>-1)and(a[i,j-1]= -1) then a[i,j]:=a[i,j]+a[i-1,j];
    end;
  if a[n,m]=-1 then writeln('SEE YOU LATER')
               else write(a[n,m]);
end.