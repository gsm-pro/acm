{$APPTYPE CONSOLE}
type
  str=string[6];
Var
  x,y,t:str;
  kol,n,i,j:longint;
  w:array[1..720] of str;
Function AddToW(v:string):boolean;
var
  z:boolean;
  i:longint;
begin
  z:=False;
  for i:=1 to kol do if w[i]=v then begin
    z:=True;
    break;
  end;
  if not z then begin
    inc(kol);
    w[kol]:=v;
  end;
  AddToW:=z;
end;
Procedure Rec(v:str);
var
  q:str;
begin
  q:=v[5]+v[2]+v[3]+v[6]+v[4]+v[1];
  if not AddToW(q) then Rec(q);
  q:=v[1]+v[5]+v[6]+v[4]+v[3]+v[2];
  if not AddToW(q) then Rec(q);
  q:=v[1]+v[6]+v[5]+v[4]+v[2]+v[3];
  if not AddToW(q) then Rec(q);
  q:=v[6]+v[2]+v[3]+v[5]+v[1]+v[4];
  if not AddToW(q) then Rec(q);
  q:=v[3]+v[1]+v[4]+v[2]+v[5]+v[6];
  if not AddToW(q) then Rec(q);
  q:=v[2]+v[4]+v[1]+v[3]+v[5]+v[6];
  if not AddToW(q) then Rec(q);
end;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(x);
  readln(y);
  kol:=0;
  AddToW(x);
  Rec(x);
  for i:=1 to kol-1 do
    for j:=1 to kol-1 do
      if w[j]>w[j+1] then begin
        t:=w[j];
        w[j]:=w[j+1];
        w[j+1]:=t;
      end;
  n:=0;
  for i:=1 to kol do if w[i]=y then n:=i;
  write(n);
end.