{$APPTYPE CONSOLE}
uses math,sysutils;
Var
  s,ans:string;
  i,n,j:longint;
  a:array[1..100] of longint;
  z:array[1..100,-1000..1000] of byte;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(s);
  n:=length(s);
  for i:=1 to n do a[i]:=StrToInt(s[i]);
  z[1,a[1]]:=1;
  for i:=1 to n-1 do
    for j:=-1000 to 1000 do
      if z[i,j]=1 then begin
        z[i+1,j-a[i+1]]:=1;
        z[i+1,j+a[i+1]]:=1;
      end;
  if z[n,0]=0 then begin
    write('NO');
    halt(0);
  end;
  ans:='';
  j:=0;
  for i:=n downto 2 do begin
    if z[i-1,j-a[i]]=1 then begin
      if z[i-1,j-a[i]]=1 then ans:='+'+IntToStr(a[i])+ans;
      dec(j,a[i]);
    end else begin
      if z[i-1,j+a[i]]=1 then ans:='-'+IntToStr(a[i])+ans;
      inc(j,a[i]);
    end;
  end;
  ans:=IntToStr(a[1])+ans;
  writeln('YES');
  write(ans);
end.