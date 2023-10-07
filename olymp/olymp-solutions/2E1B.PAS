Var
  i,j,t:longint;
  f,g:text;
  a:array[1..4] of byte;
Begin
  assign(f,'input.txt');
  reset(f);
  readln(f,a[1],a[2],a[3],a[4]);
  close(f);
  for i:=1 to 3 do
    for j:=1 to 3 do
      if a[j]>a[j+1] then begin
        t:=a[j];
        a[j]:=a[j+1];
        a[j+1]:=t;
      end;
  assign(g,'output.txt');
  rewrite(g);
  write(g,a[1]);
  close(g);
End.