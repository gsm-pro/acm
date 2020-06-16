Var
  g1,g2:text;
  m,n,k,sum,i,z,k1,k2,spusk,podjem:longint;
  a:array[1..300] of longint;
begin
  assign(g1,'input.txt');
  reset(g1);
  read(g1,m,n,k);
  close(g1);
  z:=0;
  for i:=0 to round(m/k)+1 do begin
    inc(z);
    a[z]:=i*k+1;
  end;
  for i:=1 to z-1 do
    if (a[i]<n)and(a[i+1]>n) then begin
      k1:=a[i];
      k2:=a[i+1];
      break;
    end;
  spusk:=100*(k2-n);
  podjem:=200*(n-k1);
  if spusk<=podjem then sum:=spusk
                   else sum:=podjem;
  if k2>m then sum:=(n-k1)*200;
  for i:=1 to z do if a[i]=n then begin
    sum:=0;
    break;
  end;
  assign(g2,'output.txt');
  rewrite(g2);
  writeln(g2,sum);
  close(g2);
end.