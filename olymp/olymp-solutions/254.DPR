{$APPTYPE CONSOLE}
uses math;
label lb;
var
  n,m,i,j,q,test,mn,z:longint;
  a:array[1..101,1..101] of longint;
  e,p,x:array[1..101] of longint;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(test);
  for q:=1 to test do begin
    readln(n,m);
    fillchar(e,sizeof(e),0);
    for i:=1 to n do e[i]:=1;
    for i:=1 to m do p[i]:=1;
    for i:=1 to m do for j:=1 to n do read(a[i,j]);
    repeat
      for i:=1 to m do begin
        z:=p[i];
        while (z<=n)and(e[a[i,z]]=0) do inc(z);
        if z>n then begin
          writeln(0);
          goto lb;
        end;
        p[i]:=z;
      end;
      fillchar(x,sizeof(x),0);
      for i:=1 to m do inc(x[a[i,p[i]]]);
      for i:=1 to n do if x[i]>m div 2 then begin
        writeln(i);
        goto lb;
      end;
      mn:=999;
      for i:=1 to n do if e[i]=1 then mn:=min(mn,x[i]);
      for i:=1 to n do if x[i]=mn then e[i]:=0;
    until false;
    lb:
  end;
end.