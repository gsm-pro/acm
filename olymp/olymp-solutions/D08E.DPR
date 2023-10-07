{$APPTYPE CONSOLE}
var
  s:string;
  n,l,a,b,ans,i,j:longint;
  f,g:text;
  x:array[1..15,1..15] of longint;
begin
  assign(f,'input.txt');
  reset(f);
  readln(f,n);
  readln(f,s);
  close(f);
  for i:=1 to 15 do begin
    x[i,1]:=1;
    x[1,i]:=1;
  end;
  for i:=2 to 15 do
    for j:=2 to 15 do x[i,j]:=x[i-1,j]+x[i,j-1];
  l:=length(s);
  ans:=0;
  for a:=1 to n do
    for b:=a to a+l-1 do begin
      if b>n then break;
      if a=b then inc(ans)
             else inc(ans,x[l-(b-a),b-a+1]);
    end;         
  assign(g,'output.txt');
  rewrite(g);
  writeln(g,ans);
  close(g);
end.