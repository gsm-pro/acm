Var
  f,g:text;
  s:string;
  i,l,k:byte;
  b:boolean;
begin
  assign(f,'input.txt');
  reset(f);
  readln(f,s);
  l:=length(s);
  close(f);
  k:=0;
  b:=True;
  for i:=1 to l do begin
    if s[i] in ['A','E','I','O','U'] then begin
      inc(k);
      b:=True;
    end else
    if (s[i]='Y')and(b=False) then begin
      inc(k);
      b:=True;
    end else
    if (s[i]='Y')and(b=True) then b:=False
                             else b:=False;
  end;
  assign(g,'output.txt');
  rewrite(g);
  writeln(g,k,' ',l-k);
  close(g);
end.