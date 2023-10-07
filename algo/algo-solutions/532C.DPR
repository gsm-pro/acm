{$APPTYPE CONSOLE}
uses math;
var
  z:array[0..50,0..50,0..50,0..50] of longint;
  a:char;
  w:array[0..50,0..50] of longint;
  m,n,i,j:longint;
Function C(var x1,y1,x2,y2:byte):longint;
begin
  C:=sqr(w[x2,y2]-w[x2,y1-1]-w[x1-1,y2]+w[x1-1,y1-1]);
end;
Function Calc(x1,y1,x2,y2:byte):longint;
var
  p:longint;
begin
  if (x1>x2)or(y1>y2) then begin
    Calc:=0;
    exit;
  end;
  if z[x1,y1,x2,y2]<>-1 then begin
    Calc:=z[x1,y1,x2,y2];
    exit;
  end;
  p:=0;
  p:=max(p,Calc(x1+1,y1,x2,y2)+C(x1,y1,x1,y2));
  p:=max(p,Calc(x1,y1,x2-1,y2)+C(x2,y1,x2,y2));
  p:=max(p,Calc(x1,y1+1,x2,y2)+C(x1,y1,x2,y1));
  p:=max(p,Calc(x1,y1,x2,y2-1)+C(x1,y2,x2,y2));
  z[x1,y1,x2,y2]:=p;
  Calc:=p;
end;
begin
  readln(n,m);
  fillchar(z,sizeof(z),-1);
  fillchar(w,sizeof(w),0);
  for i:=1 to n do begin
    for j:=1 to m do begin
      read(a);
      w[i,j]:=w[i-1,j]+w[i,j-1]-w[i-1,j-1];
      if a='*' then inc(w[i,j]);
    end;
    readln;
  end;
  write(Calc(1,1,n,m));
end.