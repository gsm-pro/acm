Var
  f,g:text;
  n,i:longint;
Function Prost(n:byte):boolean;
var
  i:byte;
begin
  if n=1 then begin
    Prost:=true;
    exit;
  end;
  if n=2 then begin
    Prost:=False;
    exit;
  end;
  for i:=2 to (n div 2+1) do
    if (n mod i)=0 then begin
      Prost:=true;
      exit;
    end;
  Prost:=false;
end;
begin
  assign(f,'input.txt');
  reset(f);
  readln(f,n);
  close(f);
  assign(g,'output.txt');
  rewrite(g);
  for i:=2 to n-2 do
    if (Prost(i)=False)and(Prost(n-i)=False) then begin
      writeln(g,i,' ',n-i);
      break;
    end;
  close(g);
end.