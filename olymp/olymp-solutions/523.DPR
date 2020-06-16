{$APPTYPE CONSOLE}
uses math;
Var
  s1,s2,s3:array[1..1000] of byte;
  x,n,k,i,ans,kk,kk2:longint;
Begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n,k);
  for i:=1 to n do begin read(x);s1[x]:=1;end;
  for i:=1 to n do begin read(x);s2[x]:=1;end;
  for i:=1 to n do begin read(x);s3[x]:=1;end;
  for i:=1 to 1000 do begin
    if (s1[i]=1)and(s2[i]=1)and(s3[i]=1) then begin
      s1[i]:=0;s2[i]:=0;s3[i]:=0;
    end;
    if (s1[i]=1)and(s2[i]=1) then begin
      s1[i]:=0;s2[i]:=0;
    end;
    if (s1[i]=1)and(s3[i]=1) then begin
      s1[i]:=0;s3[i]:=0;
    end;
  end;
  kk:=0;
  for i:=1 to 1000 do if (s2[i]=1)and(s3[i]=1) then begin
    inc(kk);
    s2[i]:=0;
    s3[i]:=0;
  end;
  if k<=kk then begin
    write(min(k,kk)*2);
    halt(0);
  end;
  ans:=kk*2;
  kk2:=0;
  for i:=1 to 1000 do if (s2[i]=1)or(s3[i]=1) then inc(kk2);
  ans:=ans+min(k-kk,kk2);
  write(ans);
end.