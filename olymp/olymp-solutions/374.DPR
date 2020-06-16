{$APPTYPE CONSOLE}
uses Math;
var
  a:array[1..500000] of word;
  used:array[1..10000] of boolean;
  kol:array[1..10000] of word;
  z:array[1..10000] of array of word;
  i,n,dest,num,j:longint;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  n:=0;
  num:=0;
  while not eof do begin
    inc(n);
    read(a[n]);
    num:=max(num,a[n]);
  end;
  dest:=a[1];
  used[a[1]]:=True;
  for i:=2 to n do begin
    if not used[a[i]] then begin
      inc(kol[dest]);
      used[a[i]]:=True;
    end;
    dest:=a[i];
  end;
  for i:=1 to 10000 do SetLength(z[i],kol[i]+1);
  fillchar(kol,sizeof(kol),0);
  fillchar(used,sizeof(used),False);
  dest:=a[1];
  used[a[1]]:=True;
  for i:=2 to n do begin
    if not used[a[i]] then begin
      inc(kol[dest]);
      z[dest,kol[dest]]:=a[i];
      used[a[i]]:=True;
    end;
    dest:=a[i];
  end;
  for i:=1 to num do begin
    for j:=1 to kol[i] do write(z[i,j],' ');
    writeln(0);
  end;
end.