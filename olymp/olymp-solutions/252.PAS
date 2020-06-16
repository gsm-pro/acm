Var
  f,g:text;
  a,b,k,i,j,n,sum:longint;
  s:string;
  code:integer;
begin
  assign(f,'input.txt');
  reset(f);
  read(f,a,b);
  close(f);
  k:=0;
  for i:=a to b do begin
    str(i,s);
    sum:=0;
    for j:=1 to length(s) do begin
      val(s[j],n,code);
      inc(sum,n);
    end;
    if (i mod sum)=0 then inc(k);
  end;
  assign(g,'output.txt');
  rewrite(g);
  writeln(g,k);
  close(g);
end.