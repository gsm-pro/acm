Var
  f,g:text;
  m,nk:array[1..30001] of byte;
  n,i,a,b,k,code,z:integer;
  s:string[1];
begin
  assign(f,'input.txt');
  reset(f);
  readln(f,n);
  for i:=1 to n do begin
    read(f,s);
    val(s,m[i],code);
  end;
  readln(f,k);
  for i:=1 to k do begin
    read(f,a);
    read(f,b);
    inc(nk[a]);
    inc(nk[b+1]);
  end;
  close(f);
  assign(g,'output.txt');
  rewrite(g);
  z:=0;
  for i:=1 to n do begin
    if nk[i]<>0 then inc(z,nk[i]);
    if (z mod 2)=0 then write(g,m[i])
                   else begin
      if m[i]=1 then write(g,0);
      if m[i]=0 then write(g,1);
    end;
  end;
  close(g);
end.