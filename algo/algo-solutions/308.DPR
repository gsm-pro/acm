{$APPTYPE CONSOLE}
var
  k,n,m,z,i,a,nol:word;
  ans:array[1..5001] of word;
begin
  read(k);
  for z:=1 to k do begin
    read(n,m);
    fillchar(ans,sizeof(ans),0);
    nol:=1;
    for i:=1 to n do begin
      read(a);
      if ans[a]=0 then ans[a]:=i
                  else begin
        while (ans[nol]<>0)and(nol<=m) do inc(nol);
        if nol<=m then ans[nol]:=i;
      end;
    end;
    for i:=1 to m do write(ans[i],' ');
    writeln;
  end;
end.