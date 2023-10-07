Var
  f,g:text;
  a:array[1..10]of byte;
  code,l,i:integer;
  s:string;
begin
  assign(f,'input.txt');
  reset(f);
  readln(f,s);
  close(f);
  l:=length(s);
  for i:=1 to l do val(s[i],a[i],code);
  for i:=2 to l do begin
    if a[i]-a[i-1]<0 then inc(a[i],10);
    a[i]:=a[i]-a[i-1];
  end;
  assign(g,'output.txt');
  rewrite(g);
  for i:=1 to l do write(g,a[i]);
  close(g);
end.