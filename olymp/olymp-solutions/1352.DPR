{$apptype console}
var
  s:array[1..6,1..100] of char;
  n,m,k,i,j,l,z:longint;
  eq:array[1..100] of boolean;
  ms:array[1..6] of byte;
  q:array[0..65] of byte;
  w:string;
procedure rec(kk,x:byte);
var
  i,mask,j:byte;
begin
  if kk=z+1 then begin
    fillchar(q,sizeof(q),0);
    for i:=1 to k do begin
      mask:=0;
      for j:=1 to kk-1 do if s[i][ms[j]]='1' then mask:=mask+1 shl j;
      inc(q[mask]);
      if q[mask]>1 then exit;
    end;
    for i:=1 to kk-1 do begin
      for j:=1 to n*m do w:=w+'0';
      for j:=1 to kk-1 do w[ms[j]]:='1';
      writeln(z);
      for j:=1 to n*m do begin
        write(w[j]);
        if j mod n=0 then writeln;
      end;
      halt;
    end;
  end;
  for i:=x to n*m do begin
    if eq[i] then continue;
    ms[kk]:=i;
    rec(kk+1,i+1);
  end;
end;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(m,n,k);
  for i:=1 to k do begin
    for j:=1 to m do begin
      for l:=1 to n do read(s[i][(j-1)*n+l]);
      readln;
    end;
    readln;
  end;
  for i:=1 to n*m do begin
    eq[i]:=true;
    for j:=2 to k do if s[j][i]<>s[j-1][i] then eq[i]:=false;
  end;
  for z:=1 to k-1 do rec(1,1);
end.