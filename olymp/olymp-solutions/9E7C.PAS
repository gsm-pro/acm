Var
  f,g:text;
  a:array[1..7500]of byte;
  i,j,k,n,s,q,max:longint;
  sr:single;
begin
  assign(f,'input.txt');
  reset(f);
  readln(f,n,k);
  for i:=1 to n do read(f,a[i]);
  close(f);
  max:=0;
  for i:=1 to n-k+1 do begin
    s:=0;
    for j:=i to i+k-1 do inc(s,a[j]);
    if s>max then begin
      max:=s;
      q:=i;
    end;
  end;
  sr:=max/k;
  assign(g,'output.txt');
  rewrite(g);
  writeln(g,sr:0:3);
  writeln(g,q);
  close(g);
end.