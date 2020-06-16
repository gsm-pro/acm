{$APPTYPE CONSOLE}
Var
  l1,l2,l3,x,vv,v:longint;
Begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(l1,l2,l3,x);
  v:=l1*l1+l2*l2+l3*l3;
  vv:=0;
  if x<l3 then vv:=x*l1+x*l2+x*l3;
  if (x>=l3)and(x<l2) then vv:=l3*l3+x*l2+x*l1;
  if (x>=l2)and(x<l1) then vv:=l3*l3+l2*l2+x*l1;
  write(vv,' ',v-vv);
end.