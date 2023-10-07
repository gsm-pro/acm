{$APPTYPE CONSOLE}
type
  rec=record
    prev,inf,next:longint;
  end;
var
  n,i,d,k,kol:longint;
  a:array[1..35000] of rec;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  for i:=1 to 35000 do begin
    a[i].inf:=2*i-1;
    a[i].next:=i+1;
    a[i].prev:=i-1;
  end;
  d:=2;
  repeat
    inc(d);
    i:=1;
    k:=1;
    kol:=0;
    repeat
      i:=a[i].next;
      inc(k);
      if k mod d=0 then begin
        inc(kol);
        a[a[i].prev].next:=a[i].next;
        a[a[i].next].prev:=a[i].prev;
      end;
    until a[i].inf>n;
  until kol=0;
  i:=1;
  while (a[i].inf<=n) do begin
    write(a[i].inf,' ');
    i:=a[i].next;
  end;
end.