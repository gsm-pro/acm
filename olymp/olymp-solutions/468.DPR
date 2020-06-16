 {$APPTYPE CONSOLE}
var
  n,k,x,y,z,t:longint;
threadvar
  xy,yz,xz:array[1..1000,1..1000] of byte;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n,k);
  for t:=1 to k do begin
    read(x,y,z);
    xy[x,y]:=1;
    yz[y,z]:=1;
    xz[x,z]:=1;
  end;
  t:=0;
  for x:=1 to n do
    for z:=1 to n do
      if xz[x,z]=0 then
        for y:=1 to n do begin
          if (xy[x,y]=0)and(yz[y,z]=0) then begin
            write('NO',#13#10,x,' ',y,' ',z);
            halt;
          end;
          inc(t);
          if t>20000000 then begin
            write('YES');
            halt;
          end;
        end;
  write('YES');
end.