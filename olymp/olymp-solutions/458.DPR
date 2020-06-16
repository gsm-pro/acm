{$APPTYPE CONSOLE}
label
  lb;
var
  f,g:text;
  ans,x,n,a,b,c,d,e,h,i:longint;
begin
  assign(f,'input.txt');
  reset(f);
  readln(f,n);
  close(f);
  ans:=-1;
  for a:=0 to 9 do
    for b:=a to 9 do
      for c:=b to 9 do
        for d:=c to 9 do
          for e:=d to 9 do
            for h:=e to 9 do
              for i:=h to 9 do begin
                x:=i+10*h+100*e+1000*d+10000*c+100000*b+1000000*a;
                if x<=n then inc(ans) else goto lb;
              end;
  lb:
  assign(g,'output.txt');
  rewrite(g);
  writeln(g,ans);
  close(g);
end.