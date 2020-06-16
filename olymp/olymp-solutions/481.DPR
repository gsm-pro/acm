{$APPTYPE CONSOLE}
uses math;
Var
  n:byte;
  s1,s2,a,b,c,d,p,x,y:double;
Begin
  reset(input,'input.txt');
  readln(x,y);
  s1:=x*y;
  read(n);
  if n=3 then begin
    read(a,b,c);
    p:=(a+b+c)/2;
    s2:=sqrt(p*(p-a)*(p-b)*(p-c));
  end else begin
    read(a,b,c,d);
    if (a=c)and(b=d) then s2:=a*b;
    if (a=b)and(c=d) then s2:=a*c;
  end;
  rewrite(output,'output.txt');
  write(log2(s1/s2):0:0);
end.