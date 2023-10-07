{$APPTYPE CONSOLE}
Var
  n,d,i,s,p1,p2:word;
Function Q(x:word):word;
begin
  if x>n then Q:=0 else Q:=x;
end;
Begin
  reset(input,'input.txt');
  read(n);
  rewrite(output,'output.txt');
  if n mod 4=0 then d:=0 else d:=4-n mod 4;
  if n=1 then d:=1;
  s:=n+d+1;
  p1:=n+d;
  p2:=2;
  for i:=1 to (n+d)div 2 do
    if odd(i) then begin
      writeln((i+1)div 2,' ',i mod 2,' ',Q(p1),' ',Q(s-p1));
      dec(p1,2);
    end else begin
      writeln((i+1)div 2,' ',i mod 2+2,' ',Q(p2),' ',Q(s-p2));
      inc(p2,2);
    end;  
end.