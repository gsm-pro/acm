Var
  f,g:text;
  i,n,a1,b1,a2,b2,a,b:longint;
Begin
  assign(f,'input.txt');
  reset(f);
  readln(f,n);
  assign(g,'output.txt');
  rewrite(g);
  for i:=1 to n do begin
    readln(f,a1,b1,a2,b2,a,b);
    if ((a1<=b)and(a2<=b)and(b1+b2<=a))or
       ((b1<=b)and(a2<=b)and(a1+b2<=a))or
       ((a1<=b)and(b2<=b)and(b1+a2<=a))or
       ((b1<=b)and(b2<=b)and(a1+a2<=a))or
       ((b1<=a)and(b2<=a)and(a1+a2<=b))or
       ((b1<=a)and(a2<=a)and(a1+b2<=b))or
       ((a1<=a)and(b2<=a)and(a2+b1<=b))or
       ((a1<=a)and(a2<=a)and(b1+b2<=b))or
       ((a1+a2<=a)and(b1+b2<=b))or
       ((a1+b2<=a)and(b1+a2<=b))or
       ((b1+a2<=a)and(a1+b2<=b))or
       ((b1+b2<=a)and(a1+a2<=b))then writeln(g,'1')
                                else writeln(g,'0');
  end;
  close(f);
  close(g);
End.