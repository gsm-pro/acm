var
  n,i,j,k:longint;
  f,g:text;
  a,b:array[1..1000] of longint;
begin
  assign(f,'input.txt');
  reset(f);
  readln(f,n);
  for i:=1 to n do read(f,a[i]);
  close(f);
  for i:=1 to n do b[i]:=-1;
  for i:=1 to n do begin
    k:=a[i]+1;
    for j:=1 to n do begin
      if b[j]=-1 then dec(k);
      if k=0 then begin
        b[j]:=i;
        break;
      end;
    end;
  end;
  assign(g,'output.txt');
  rewrite(g);
  for i:=1 to n do write(g,b[i],' ');
  close(g);
end.