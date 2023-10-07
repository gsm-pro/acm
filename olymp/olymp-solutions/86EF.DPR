{$apptype console}
Var
  n,i:longint;
  s:string;
Function IntToBin(n:longint):string;
var
  i:byte;
  z:string;
begin
  z:='';
  for i:=31 downto 1 do begin
    if odd(n) then z:=z+'1' else z:=z+'0';
    n:=n shr 1;
    if n=0 then break;
  end;
  IntToBin:=z;
end;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  if (n and 1=0) then write('No solution') else
    if (n=1) then write(0) else begin
      s:=IntToBin(n);
      writeln(length(s)-1);
      for i:=length(s) downto 2 do if s[i]='1' then write('2 ') else write('1 ');
    end;
end.