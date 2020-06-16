{$APPTYPE CONSOLE}
var
  f,g:text;
  a,v,p:array[1..101] of longint;
  i,j,n,k,z,w:longint;
begin
  assign(f,'input.txt');
  reset(f);
  readln(f,n);
  for i:=1 to n do read(f,v[i],a[i]);
  for i:=1 to n do read(f,p[i]);
  close(f);
  for w:=1 to n do begin
    j:=p[w]+1;
    z:=p[w];
    while (a[z]>0)and(j<=n) do begin
      if a[z]>=v[j]-a[j] then begin
        a[z]:=a[z]-(v[j]-a[j]);
        a[j]:=v[j];
       end;
      if a[z]< v[j]-a[j] then begin
        a[j]:=a[j]+a[z];
        a[z]:=0;
      end;
      inc(j);
    end;
  end;
  assign(g,'output.txt');
  rewrite(g);
  for i:=1 to n do write(g,a[i],' ');
  close(g);
end.