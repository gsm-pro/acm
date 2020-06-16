{$APPTYPE CONSOLE}
var
  n,i,j,k,l,ans:longint;
  a,b:array[0..1001] of longint;
  z:boolean;
begin
  readln(n);
  for i:=1 to n do read(a[i]);
  if (n=1)and(a[1]=0) then begin writeln('1');exit;end;
  if (n=1)and(a[1]=1) then begin writeln('1');exit;end;
  if (n=1)and(a[1]=2) then begin writeln('0');exit;end;
  if (n=1)and(a[1]=3) then begin writeln('0');exit;end;
  ans:=0;
  for i:=0 to 1 do
    for j:=0 to 1 do
      for l:=0 to 1 do begin
        b[1]:=i;b[2]:=j;b[3]:=l;
        z:=True;
        for k:=4 to n do begin
          b[k]:=a[k-1]-a[k-2]+b[k-3];
          if (b[k]<>1)and(b[k]<>0) then begin
            z:=False;
            break;
          end;
        end;
        if not z then continue;
        for k:=1 to n do if a[k]<>b[k-1]+b[k]+b[k+1] then begin
          z:=False;
          break;
        end;
        if z then inc(ans);
      end;
  write(ans);
end.