{$APPTYPE CONSOLE}
var
  n,i,j,s:longint;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  for i:=1 to n-1 do begin
    s:=i;
    for j:=1 to i+1 do begin
      s:=2*s+1;
      if s>=n then begin
        write(i);
        halt;
      end;
    end;
  end;
  write(0);
end.