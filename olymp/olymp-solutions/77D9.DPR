Var
  f,g:text;
  a:array[1..128] of longint;
  i,max:longint;
  c:char;
Begin
  assign(f,'input.txt');
  reset(f);
  while not eof(f) do begin
    read(f,c);
    inc(a[ord(c)]);
  end;
  close(f);
  max:=0;
  for i:=65 to 90 do if a[i]+a[i+32]>max then max:=a[i]+a[i+32];
  assign(g,'output.txt');
  rewrite(g);
  for i:=65 to 90 do if a[i]+a[i+32]=max then write(g,chr(i));
  close(g);
End.