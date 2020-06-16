{$APPTYPE CONSOLE}
var
  s:array[1..10] of ansistring;
  i,j,n,kol:longint;
Function Eq(a,b:string):boolean;
var
  i,t:longint;
  v:ansistring;
  w:boolean;
begin
  if length(a)>length(b) then begin
    Eq:=False;
    exit;
  end;
  if pos(a,b)<>0 then begin
    Eq:=True;
    exit;
  end;
  for i:=1 to length(b)-length(a)+1 do begin
    v:=copy(b,i,length(a));
    w:=True;
    for t:=1 to length(v) do begin
      if (v[t]='?')or(a[t]='?') then continue;
      if v[t]<>a[t] then begin
        w:=False;
        break;
      end;
    end;
    if w then begin
      Eq:=True;
      exit;
    end;
  end;
  Eq:=False;
end;
begin
  readln(n);
  for i:=1 to n do readln(s[i]);
  kol:=0;
  for i:=1 to n do
    for j:=i+1 to n do
      if (Eq(s[i],s[j]))or(Eq(s[j],s[i])) then inc(kol);
  write(kol);    
end.