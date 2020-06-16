Var
  f,g:text;
  x1,y1,r1,x2,y2,r2,k,d:longint;
Begin
  assign(f,'input.txt');
  reset(f);
  read(f,x1,y1,r1,x2,y2,r2);
  close(f);
  d:=(x2-x1)*(x2-x1)+(y2-y1)*(y2-y1);
  if (x1=x2)and(y1=y2)and(r1=r2) then k:=-1 else
    if ((r1-r2)*(r1-r2)<d)and((r1+r2)*(r1+r2)>d) then k:=2 else
      if ((r1-r2)*(r1-r2)=d)or((r1+r2)*(r1+r2)=d) then k:=1 else
        if ((r1-r2)*(r1-r2)>d)or((r1+r2)*(r1+r2)<d) then k:=0;
  if (x1=x2)and(y1=y2)and(r1=0)and(r2=0) then k:=1;
  assign(g,'output.txt');
  rewrite(g);
  writeln(g,k);
  close(g);
End.