{$APPTYPE CONSOLE}
var
  n,m,i,j,w,t:longint;
  a,b,s:string;
  z:array[0..500,0..500] of boolean;
begin
  readln(t);
  for w:=1 to t do begin
    fillchar(z,sizeof(z),false);
    readln(a);
    readln(b);
    readln(s);
    n:=length(a);   
    m:=length(b);
    if n+m<>length(s) then begin
      writeln('No');
      continue;
    end;
    for i:=0 to n+1 do
      for j:=0 to m+1 do begin
        z[i,j]:=(i=0)and(j=0);
        z[i,j]:=((i>0)and(z[i-1,j])and(a[i]=s[i+j]))or(z[i,j]);
        z[i,j]:=((j>0)and(z[i,j-1])and(b[j]=s[i+j]))or(z[i,j]);
      end;
    if z[n,m] then writeln('Yes') else writeln('No');
  end;
end.