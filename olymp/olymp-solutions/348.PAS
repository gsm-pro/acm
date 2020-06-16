Var
  f,g:text;
  a:array[1..5000]of integer;
  j,i,n,k,q,p,kol:longint;
  z,x:boolean;
  r1,r2:array[1..10000]of integer;
begin
  assign(f,'input.txt');
  reset(f);
  readln(f,n,k);
  for i:=1 to n do read(f,a[i]);
  close(f);
  x:=True;
  for i:=1 to n do if a[i]<>k then begin
    x:=False;
    break;
  end;
  kol:=0;
  p:=1;
  q:=1;
  repeat
    inc(kol);
    for i:=p to n do
      if a[i]>k then begin
        p:=i;
        break;
      end;
    r1[kol]:=p;
    for i:=q to n do
      if a[i]<k then begin
        q:=i;
        break;
      end;
    r2[kol]:=q;
    dec(a[p]);
    inc(a[q]);
    z:=False;
    for i:=1 to n do if a[i]<>k then begin
      z:=True;
      break;
    end;
  until z=False;
  assign(g,'output.txt');
  rewrite(g);
  if x=True then writeln(g,'0') else begin
    writeln(g,kol);
    for i:=1 to kol do writeln(g,r1[i],' ',r2[i]);
  end;
  close(g);
end.