{$APPTYPE CONSOLE}
Var
  f,g:text;
  n,m,i,j,z,k,ball,sum,kol,k3,k4,k5,s,w:longint;
  b,p:array[1..100] of longint;
  faculty,spec:string;
begin
  assign(f,'input.txt');
  reset(f);
  assign(g,'output.txt');
  rewrite(g);
  kol:=0;
  readln(f,n,m);
  for i:=1 to m do read(f,b[i]);
  readln(f);
  for z:=1 to n do begin
    sum:=0;
    readln(f,faculty);
    read(f,k);
    for i:=1 to k do read(f,p[i]);
    readln(f);
    for i:=1 to k do begin
      read(f,k3,k4,k5);
      if  b[p[(3*i+2)div 3]]>=k5 then inc(sum,5);
      if (b[p[(3*i+2)div 3]]<k5)and(b[p[(3*i+2)div 3]]>=k4) then inc(sum,4);
      if (b[p[(3*i+2)div 3]]<k4)and(b[p[(3*i+2)div 3]]>=k3) then inc(sum,3);
      if  b[p[(3*i+2)div 3]]<k3 then inc(sum,2);
    end;
    readln(f,s);
    for w:=1 to s do begin
      readln(f,spec);
      readln(f,ball);
      if sum>=ball then begin
        inc(kol);
        writeln(g,faculty,' ',spec);
      end;
    end;
  end;
  if kol=0 then writeln(g,'Army');
  close(f);
  close(g);
end.