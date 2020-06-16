{$APPTYPE CONSOLE}
const
  nmax=22;
  smax=201;
var
  n,t,i,mask,num,add,nd,np,nmask:longint;
  sum:array[0..smax] of longint;
  d,p:array[0..4194305] of longint;
  a:array[0..nmax] of longint;
Function Has(v,i:longint):boolean;
begin
  Has:=(v shr i)and 1<>0;
end;
begin
  read(n);
  for i:=0 to n-1 do read(a[i]);
  for i:=0 to smax do begin
    t:=i;
    while t<>0 do begin
      sum[i]:=sum[i]+t mod 10;
      t:=t div 10;
    end;
  end;
  for mask:=1 to (1 shl n)-1 do begin
    nd:=-1;
    np:=-1;
    for i:=0 to n-1 do begin
      if not Has(mask,i) then continue;
      num:=0;
      if (i>0)and(Has(mask,i-1)) then num:=num+a[i-1];
      if (i<n-1)and(Has(mask,i+1)) then num:=num+a[i+1];
      add:=sum[num];
      nmask:=mask xor (1 shl i);
      if (nd<p[nmask]+add)or((nd=p[nmask]+add)and(np>d[nmask])) then begin
        nd:=p[nmask]+add;
        np:=d[nmask];
      end;
    end;
    d[mask]:=nd;
    p[mask]:=np;
  end;
  write(d[(1 shl n)-1],' ',p[(1 shl n)-1]);
end.