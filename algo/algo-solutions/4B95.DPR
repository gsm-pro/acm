{$APPTYPE CONSOLE}
const
  nmax=1002;
  inf=20;
type prev=record
  rem:longint;
  last:char;
end;
var
  d:array[0..nmax,0..nmax] of longint;
  p:array[0..nmax,0..nmax] of prev;
  m,k,i,j,minones,bestlen,len:longint;
Procedure recout(len,rem:longint);
begin
  if len=0 then exit;
  recout(len-1,p[len,rem].rem);
  write(p[len,rem].last);
end;
begin
  readln(k,m);
  if (k<=0)or(k>m)or(m<1) then begin
    writeln('0');
    exit;
  end;  
  for i:=0 to nmax-1 do
    for j:=0 to nmax-1 do d[i,j]:=inf;
  d[0,0]:=0;
  for i:=0 to m-1 do
    for j:=0 to m-1 do begin
      if d[i,j]=inf then continue;
      if d[i+1,(j*2) mod m]>d[i,j] then begin
        d[i+1,(j*2) mod m]:=d[i,j];
        p[i+1,(j*2) mod m].last:='0';
        p[i+1,(j*2) mod m].rem:=j;
      end;
      if d[i+1,(j*2+1) mod m]>d[i,j]+1 then begin
        d[i+1,(j*2+1) mod m]:=d[i,j]+1;
        p[i+1,(j*2+1) mod m].last:='1';
        p[i+1,(j*2+1) mod m].rem:=j;
      end;
    end;
  minones:=inf;
  bestlen:=-1;
  for len:=1 to m do
    if minones>d[len,k] then begin
      minones:=d[len,k];
      bestlen:=len;
    end;
  if minones>inf then begin
    writeln('0');
    exit;
  end;  
  recout(bestlen,k);
end.