{$APPTYPE CONSOLE}
var
  k,n,m,z,i,a,nol:longint;
  ans:array[1..5001] of smallint;
  f,g:text;
begin
  assign(f,'input.txt');
  reset(f);
  assign(g,'output.txt');
  rewrite(g);
  readln(f,k);
  for z:=1 to k do begin
    readln(f,n,m);
    fillchar(ans,sizeof(ans),0);
    nol:=1;
    for i:=1 to n do begin
      read(f,a);
      if ans[a]=0 then ans[a]:=i
                  else begin
        while (ans[nol]<>0)and(nol<=m) do inc(nol);
        if nol>m then continue else ans[nol]:=i;
      end;
    end;
    for i:=1 to m do write(g,ans[i],' ');
    writeln(g);
  end;
  close(f);
  close(g);
end.