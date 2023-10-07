Var
  f,g:text;
  s,v:extended;
  n,k,r,i:longint;
Begin
  assign(f,'input.txt');
  reset(f);
  read(f,n,r);
  close(f);
  if n=0 then begin
    k:=1;
    s:=4*pi*r*r;
    v:=4*pi*r*r*r/3;
  end else begin
    k:=n*2;
    v:=4*pi*r*r*r/(3*k);
    s:=4*pi*r*r/k+pi*r*r
  end;
  assign(g,'output.txt');
  rewrite(g);
  writeln(g,k,' ',v:0:7,' ',s:0:7);
  close(g);
End.