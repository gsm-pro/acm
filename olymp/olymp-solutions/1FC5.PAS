Var
  g1,g2:text;
  t,p,k,s,l,f:string;
  i:integer;
begin
  assign(g1,'input.txt');
  reset(g1);
  readln(g1,t);
  close(g1);
  for i:=1 to length(t) do
    case t[i] of
      'P':p:=p+'P';
      'K':k:=k+'K';
      'S':s:=s+'S';
      'L':l:=l+'L';
      'F':f:=f+'F';
    end;
  t:=p+k+s+l+f;
  assign(g2,'output.txt');
  rewrite(g2);
  writeln(g2,t);
  close(g2);
end.