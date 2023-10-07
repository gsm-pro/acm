Var
  f,g:text;
  s,t:string;
  i,k:byte;
  b:boolean;
Begin
  assign(f,'input.txt');
  reset(f);
  read(f,s);
  close(f);
  s:=s+'P';
  t:='';
  b:=False;
  k:=0;
  for i:=1 to length(s)+1 do begin
    if (s[i]='P')and(b=False) then continue;
    if (s[i]='C')and(b=False) then begin
      b:=True;
      continue;
    end;
    if (s[i]='P')and(b=True) then begin
      b:=False;
      t:=t+'1 ';
      inc(k);
      continue;
    end;
    if (s[i]='C')and(b=True) then begin
      b:=False;
      t:=t+'2 ';
      inc(k);
      continue;
    end;
  end;
  assign(g,'output.txt');
  rewrite(g);
  writeln(g,k);
  if k<>0 then writeln(g,t);
  close(g);
End.