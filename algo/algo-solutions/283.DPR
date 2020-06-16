{$APPTYPE CONSOLE}
var
  v:int64;
  n,m,k,a,b:int64;
  i:longint;
  x,w:array[1..1001,1..101] of int64;
Function Calc(k,c:int64):int64;
var
  z:int64;
  i:longint;
begin
  if k=1 then begin
    Calc:=1;
    exit;
  end;
  if w[k,c]<>-1 then begin
    Calc:=w[k,c];
    exit;
  end;  
  z:=0;
  for i:=1 to m do if x[i,c]<>1 then z:=(z+Calc(k-1,i)) mod 98759873;
  w[k,c]:=z;    
  Calc:=z;  
end;
begin
  read(n,m,k);
  for i:=1 to k do begin
    read(a,b);
    x[a,b]:=1;
    x[b,a]:=1;
  end;
  v:=0;
  fillchar(w,sizeof(w),255);
  for i:=1 to m do v:=v+(Calc(n,i) mod 98759873);
  writeln(v mod 98759873);
end.