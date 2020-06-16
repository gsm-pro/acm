{$APPTYPE CONSOLE}
uses math;
var
  x,y,z:array[0..105] of longint;
  n,i:longint;
  w:array[0..105,0..105,0..105] of longint;
Function Calc(a,b,c:longint):longint;
var
  m:longint;
begin
  if (a>n)and(b>n)and(c>n) then begin
    Calc:=0;
    exit;
  end; 
  if w[a,b,c]<>-1 then begin
    Calc:=w[a,b,c];
    exit;
  end;  
  m:=0;
  if (a=b)and(a<=n) then m:=max(m,Calc(a+1,b+1,c)+x[a]*y[a]);
  if (a+1<=n) then m:=max(m,Calc(a+2,b,c)+x[a]*x[a+1]);
  if (b+1<=n) then m:=max(m,Calc(a,b+2,c)+y[b]*y[b+1]);
  if (c+1<=n) then m:=max(m,Calc(a,b,c+2)+z[c]*z[c+1]);
  if (b=c)and(b<=n) then m:=max(m,Calc(a,b+1,c+1)+y[c]*z[c]);
  w[a,b,c]:=m;
  Calc:=m;
end;  
Function Calc1(a,b,c:longint):longint;
var
  m:longint;
begin
  if (a>n)and(b>n)and(c>n) then begin
    Calc1:=0;
    exit;
  end; 
  if w[a,b,c]<>-1 then begin
    Calc1:=w[a,b,c];
    exit;
  end;  
  m:=1000000000;
  if (a=b)and(a<=n) then m:=min(m,Calc1(a+1,b+1,c)+x[a]*y[a]);
  if (a+1<=n) then m:=min(m,Calc1(a+2,b,c)+x[a]*x[a+1]);
  if (b+1<=n) then m:=min(m,Calc1(a,b+2,c)+y[b]*y[b+1]);
  if (c+1<=n) then m:=min(m,Calc1(a,b,c+2)+z[c]*z[c+1]);
  if (b=c)and(b<=n) then m:=min(m,Calc1(a,b+1,c+1)+y[c]*z[c]);
  w[a,b,c]:=m;
  Calc1:=m;
end;  
begin
  readln(n);
  for i:=1 to n do read(x[i]);
  for i:=1 to n do read(y[i]);  
  for i:=1 to n do read(z[i]);
  if odd(n) then begin
    writeln('No solution');
    halt;
  end;
  fillchar(w,sizeof(w),255);
  write(Calc1(1,1,1),' ');
  fillchar(w,sizeof(w),255);
  write(Calc(1,1,1));
end.