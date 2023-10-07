var
  f,g:text;
  s:string;
  i,j,l,t,k,w:longint;
begin
  assign(f,'input.txt');
  reset(f);
  readln(f,k);
  readln(f,s);
  close(f);
  assign(g,'output.txt');
  rewrite(g);
  w:=length(s);
  for i:=1 to k do begin
    for l:=1 to w do begin
      for j:=1 to i do write(g,s[l]);
      for t:=1 to k-i do write(g,'~' );
    end;
    writeln(g);
  end;
  close(g);
end.