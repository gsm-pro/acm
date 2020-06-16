Var
  f,g:text;
  n,i,d1,d2:longint;
  a:array[1..4] of longint;
begin
  assign(f,'input.txt');
  reset(f);
  read(f,n);
  assign(g,'output.txt');
  rewrite(g);
  for i:=1 to n do begin
    read(f,a[1],a[2],a[3],a[4],d1,d2);
    if ((a[1]<=d1)and(a[2]+a[3]+a[4]+2<=d2))or
       ((a[2]<=d1)and(a[1]+a[3]+a[4]+2<=d2))or
       ((a[3]<=d1)and(a[1]+a[2]+a[4]+2<=d2))or
       ((a[4]<=d1)and(a[1]+a[2]+a[3]+2<=d2))or
       ((a[1]<=d2)and(a[2]+a[3]+a[4]+2<=d1))or
       ((a[2]<=d2)and(a[1]+a[3]+a[4]+2<=d1))or
       ((a[3]<=d2)and(a[1]+a[2]+a[4]+2<=d1))or
       ((a[4]<=d2)and(a[1]+a[2]+a[3]+2<=d1))or
       ((a[1]+a[2]+1<=d1)and(a[3]+a[4]+1<=d2))or
       ((a[1]+a[3]+1<=d1)and(a[2]+a[4]+1<=d2))or
       ((a[1]+a[4]+1<=d1)and(a[2]+a[3]+1<=d2))or
       ((a[2]+a[3]+1<=d1)and(a[1]+a[4]+1<=d2))or
       ((a[2]+a[4]+1<=d1)and(a[1]+a[3]+1<=d2))or
       ((a[3]+a[4]+1<=d1)and(a[1]+a[2]+1<=d2))then writeln(g,'YES')
                                              else writeln(g,'NO');
  end;
  close(f);
  close(g);
end.