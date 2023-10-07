{$APPTYPE CONSOLE}
var
  z:array[1..4000000] of longint;
  n,k,i,t,p,q:longint;
begin
  read(n);
  for i:=1 to n do begin
    read(t,k);
    p:=k div 32+1;
    q:=k mod 32+1;
    case t of
      0:z[p]:=z[p] or (1 shl q);
      1:if (z[p] shr q)and 1=0 then writeln('FALSE')
                               else writeln('TRUE');
      2:z[p]:=z[p] and (-1 xor (1 shl q))
    end;
  end;
end.