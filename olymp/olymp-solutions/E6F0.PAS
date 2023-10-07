Var
  f,g:text;
  a,b:array[1..3]of byte;
  i:byte;
begin
  assign(f,'input.txt');
  reset(f);
  for i:=1 to 3 do begin
    read(f,a[i]);
    b[a[i]]:=i;
  end;
  close(f);
  assign(g,'output.txt');
  rewrite(g);
  write(g,b[1],' ',b[2],' ',b[3]);
  close(g);
end.