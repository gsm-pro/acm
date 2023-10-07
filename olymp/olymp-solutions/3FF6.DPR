{$APPTYPE CONSOLE}
var
  s,w,ans:string;
  i,j,n,r,lt,max_r,kol,v:longint;
  pred,mx,ind:array[1..2500] of word;
  b:array[1..26] of word;
  min_ch:char;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(s);
  n:=length(s);
  for i:=1 to n do begin
    lt:=ord(s[i])-64;
    pred[i]:=b[lt];
    b[lt]:=i;
  end;
  for i:=1 to n do begin
    max_r:=0;
    r:=0;
    for j:=1 to n-i+1 do begin
      if pred[i+j-1]<i then inc(r) else if pred[pred[i+j-1]]<i then dec(r);
      if r>max_r then max_r:=r;
    end;
    mx[i]:=max_r;
  end;
  max_r:=0;
  for i:=1 to n do if mx[i]>max_r then max_r:=mx[i];
  min_ch:='Я';
  for i:=1 to n do if mx[i]=max_r then if s[i]<min_ch then min_ch:=s[i];
  kol:=0;
  for i:=1 to n do if (mx[i]=max_r)and(s[i]=min_ch) then begin
    inc(kol);
    ind[kol]:=i;
  end;
  ans:='Я';
  for v:=1 to kol do begin
    i:=ind[v];
    r:=0;
    for j:=1 to n-i+1 do begin
      if pred[i+j-1]<i then inc(r) else if pred[pred[i+j-1]]<i then dec(r);
      if r=max_r then begin
        w:=copy(s,i,j);
        if w<ans then ans:=w;
        break;
      end;
    end;
  end;
  write(ans);
end.