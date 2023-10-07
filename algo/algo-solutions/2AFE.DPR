{$APPTYPE CONSOLE}
var
  a,b,z:ansistring;
  i,ans:longint;
begin
  readln(a);
  readln(b);
  z:='';
  if pos(a,b)<>0 then ans:=length(a)
                 else begin
    ans:=0;
    for i:=1 to length(a) do begin
      z:=z+a[i];
      if pos(z,b)=0 then begin
        ans:=i-1;
        break;
      end;
    end;
  end;
  write(ans);
end.