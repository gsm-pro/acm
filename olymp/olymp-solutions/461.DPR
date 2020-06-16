{$APPTYPE CONSOLE}
Var
  n,i,k,x,j:longint;
  z:array of array of longint;
  s,leaf:string;
Procedure SubtreeTo(x,m:longint);
var
  i:longint;
begin
  if m=0 then s[x]:='0' else s[x]:='1';
  for i:=0 to length(z[x])-1 do SubtreeTo(z[x,i],m);
end;
Function Rec(x:longint):boolean;
var
  len,i,k,j,ind:longint;
  q:boolean;
begin
  Rec:=False;
  len:=length(z[x]);
  if odd(len) then begin
    q:=False;
    for i:=0 to len-1 do
      if Rec(z[x,i]) then begin
        k:=0;
        ind:=0;
        for j:=0 to len-1 do
          if i<>j then begin
            inc(k);
            SubtreeTo(z[x,j],0);
            ind:=j;
            if k=len div 2 then break;
          end;
        for j:=ind+1 to len-1 do
          if i<>j then SubtreeTo(z[x,j],1);
        q:=True;
        break;
      end;
    Rec:=q;
  end else if len<>0 then begin
    Rec:=True;
    for i:=0 to len div 2-1 do SubtreeTo(z[x,i],0);
    for i:=len div 2 to len-1 do SubtreeTo(z[x,i],1);
  end;
end;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  SetLength(z,n+1);
  for i:=1 to n do begin
    read(k);
    SetLength(z[i],k);
    for j:=0 to k-1 do begin
      read(x);
      z[i,j]:=x;
    end;
  end;
  s:=StringOfChar('A',n);
  leaf:=StringOfChar('0',n);
  for i:=1 to n do if length(z[i])=0 then leaf[i]:='1';
  if Rec(1) then begin
    for i:=1 to n do if leaf[i]='1' then write(s[i]);
  end else write('No solution');
end.