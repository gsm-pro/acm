{$APPTYPE CONSOLE}
var
  a,b,t1,t2,x,y,i,j,g1,b1,u1,g2,b2,u2:longint;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(a,b,x,y,g1,b1,u1,g2,b2,u2);
  t1:=9*g1+4*b1+4*u1;
  t2:=9*g2+4*b2+4*u2;
  for i:=0 to 2000 do
    for j:=0 to 2000 do
      if (i*t1+j*t2>=a)and(i*t1+j*t2<=b)and
         (i*g1+j*g2>=x)and(i*b1+j*b2>=y) then begin
           write(i,' ',j);
           halt(0);
         end;
  write(-1);
end.