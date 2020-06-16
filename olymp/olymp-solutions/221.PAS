type
  rec=record
    p,q:longint;
  end;
var
  i,j,n,sum,ned,z:longint;
  x:array[1..250] of rec;
  t:rec;
  f,g:text;
begin
  assign(f,'input.txt');
  reset(f);
  read(f,n);
  for i:=1 to n do read(f,x[i].p,x[i].q);
  close(f);
  for i:=1 to n-1 do
    for j:=1 to n-1 do
      if x[j].p>x[j+1].p then begin
        t:=x[j];
        x[j]:=x[j+1];
        x[j+1]:=t;
      end;
  for i:=1 to n do x[i].p:=(x[i].p+6) div 7;
  sum:=0;
  z:=1;
  for ned:=1 to 10000 do begin
    if (x[z].p>ned)and(sum=0) then continue;
    while x[z].p=ned do begin
      inc(sum,x[z].q);
      inc(z);
    end;
    dec(sum,10000);
    if (sum<=0)and(z>n) then break;
    if sum<0 then sum:=0;
  end;
  assign(g,'output.txt');
  rewrite(g);
  write(g,ned*7+1);
  close(g);
end.