{$APPTYPE CONSOLE}
Const
  COUNT=2100000;
Var
  f,g:text;
  a1,a2:array[1..COUNT+500] of longint;
  n,p1,p2,r1,r2,ans,i:longint;
begin
  assign(f,'input.txt');
  reset(f);
  assign(g,'output.txt');
  rewrite(g);
  readln(f,n);
  p1:=COUNT;
  r1:=COUNT+n-1;
  p2:=p1;
  r2:=r1;
  for i:=1 to n do read(f,a1[p1+i-1]);
  for i:=1 to n do read(f,a2[p2+i-1]);
  close(f);
  ans:=0;
  repeat
    inc(ans);
    if ans>1000000 then begin
      write(g,'TOO MANY');
      break;
    end;
    if a1[r1]>a2[r2] then begin
      a1[p1-1]:=a1[r1];
      a1[p1-2]:=a2[r2];
      dec(r2);
      dec(r1);
      dec(p1,2);
    end else begin
      a2[p2-1]:=a2[r2];
      a2[p2-2]:=a1[r1];
      dec(r1);
      dec(r2);
      dec(p2,2);
    end;
    if (r2<p2)or(r1<p1) then begin
      write(g,ans);
      break;
    end;
  until false;
  close(g);
end.