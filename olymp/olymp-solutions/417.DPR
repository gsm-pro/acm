{$APPTYPE CONSOLE}
Var
  f,g:text;
  a:array[1..26] of longint;
  v:array[1..50000] of char;
  i,j,n,k:longint;
  c:char;
  w:string[1];
Begin
  assign(f,'input.txt');
  reset(f);
  readln(f,n);
  for i:=1 to n do begin
    read(f,c);
    inc(a[ord(c)-64]);
  end;
  close(f);
  assign(g,'output.txt');
  rewrite(g);
  k:=0;
  for i:=1 to 26 do
    if a[i]>=2 then
      for j:=1 to (a[i] div 2) do begin
        inc(k);
        v[k]:=chr(i+64);
        a[i]:=a[i] mod 2;
      end;
  w:='';
  for i:=1 to 26 do
    if (a[i] mod 2)=1 then begin
      w:=chr(i+64);                   
      break;
    end;
  for i:=1 to k do write(g,v[i]);
  write(g,w);
  for i:=k downto 1 do write(g,v[i]);
  close(g);
End.