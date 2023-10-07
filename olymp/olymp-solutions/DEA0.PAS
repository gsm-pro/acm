Var
  f,g:text;
  s,t:string;
  k,i,z,m:longint;
  l:byte;
  a,b:array[1..2000]of longint;
Function GetD(z:longint):longint;
var
  i,s,k:longint;
begin
  k:=0;
  s:=trunc(sqrt(z));
  for i:=1 to s do if (z mod i)=0 then inc(k);
  k:=k*2;
  if s*s=z then dec(k);
  GetD:=k;
end;
Procedure Fill;
var
  i,d,k1,k2:longint;
begin
  k1:=1;
  k2:=1;
  a[1]:=2;
  b[1]:=1;
  for i:=3 to 1500 do begin
    d:=GetD(i);
    if d=2 then begin inc(k1);a[k1]:=i;end
           else begin inc(k2);b[k2]:=i;end;
  end;
end;
begin
  assign(f,'input.txt');
  reset(f);
  readln(f,k);
  readln(f,s);
  close(f);
  Fill;
  l:=length(s);
  for z:=1 to k do begin
    t:='';
    for i:=1 to l do t:=t+' ';
    m:=0;
    for i:=1 to l do
      if a[i]<=l then begin
        t[a[i]]:=s[i];
        inc(m);
      end else break;
    for i:=1 to l-m do t[b[i]]:=s[i+m];
    s:=t;
  end;
  assign(g,'output.txt');
  rewrite(g);
  for i:=1 to l do write(g,s[i]);
  close(g);
end.