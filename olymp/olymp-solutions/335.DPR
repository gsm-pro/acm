{$APPTYPE CONSOLE}
Var
  f,g:text;
  z,p,q,m,n,kol,w,i:longint;
  a:array[1..50] of byte;
  b:boolean;
Begin
  assign(f,'input.txt');
  reset(f);
  assign(g,'output.txt');
  rewrite(g);
  readln(f,q);
  for z:=1 to q do begin
    read(f,n,m,p);
    kol:=0;
    fillchar(a,sizeof(a),0);
    w:=trunc(sqrt(p));
    for i:=1 to w do
      if (p mod i)=0 then begin
        inc(kol);
        a[kol]:=i;
      end;
    if w*w=p then begin
      inc(kol);
      a[kol]:=w;
    end;
    b:=False;
    for i:=1 to kol do
      if((m>=a[i])and(n>=p div a[i]))or
        ((n>=a[i])and(m>=p div a[i]))then begin
           b:=True;
           break;
        end;
    if (p=1)or(b=True) then writeln(g,'Yes')
                       else writeln(g,'No');
  end;
  close(f);
  close(g);
end.