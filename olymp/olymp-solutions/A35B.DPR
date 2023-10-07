{$APPTYPE CONSOLE}
var
  a:array[1..16,1..16] of byte;
  s,vert:array[1..16] of byte;
  n,m,k,i,j,v1,v2,kol:byte;
begin
  reset(input,'input.txt');
  read(n,m,k);
  for i:=1 to m do begin
    read(v1,v2);
    a[v1,v2]:=1;
    a[v2,v1]:=1;
  end;
  for i:=1 to n do for j:=1 to n do if a[i,j]=1 then inc(s[i]);
  rewrite(output,'output.txt');
  kol:=0;
  for i:=1 to n do
    if s[i]<=k then begin
      vert[i]:=1;
      for j:=1 to n do if a[i,j]=1 then begin
        write(j,' ');
        vert[j]:=1;
        inc(kol);
      end;
      if kol<k then
        for j:=1 to n do
          if (vert[j]=0)and(kol<k) then begin
            write(j,' ');
            inc(kol);
          end;  
      halt(0);
    end;
  write('0');  
end.