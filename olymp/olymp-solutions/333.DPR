{$APPTYPE CONSOLE}
type
  arr=array[0..3500] of longint;
var
  a:arr;
  n,i,l,r,ans,x,p1,p2:longint;
  f,g:text;
Procedure QSort(left,right:longint;var w:arr);
var
  m,i,j,t:longint;
begin
  m:=w[(left+right) div 2];
  i:=left;
  j:=right;
  repeat
    while w[i]<m do inc(i);
    while w[j]>m do dec(j);
    if i<=j then begin
      t:=w[i];
      w[i]:=w[j];
      w[j]:=t;
      inc(i);
      dec(j);
    end;
  until i>j;
  if j>left then QSort(left,j,w);
  if i<right then QSort(i,right,w);
end;
begin
  assign(f,'input.txt');
  reset(f);
  readln(f,n);
  for i:=1 to n do read(f,a[i]);
  close(f);
  QSort(1,n,a);
  ans:=0;
  for i:=1 to n do begin
    l:=1;
    r:=n;
    while (l<=n)and(r>0) do begin
      if l>=r then break;
      if a[l]+a[r]>a[i] then dec(r) else
      if a[l]+a[r]<a[i] then inc(l) else begin
        if (l=i)or(r=i) then break;
        p1:=1;
        p2:=1;
        for x:=1 to r-1 do if (l+x>=r)or(a[r]+a[l+x]<>a[i]) then break
          else if (l+x<>i)and(r<>i) then inc(p1);
        for x:=1 to r-l do if (r-x<=l)or(a[l]+a[r-x]<>a[i]) then break
          else if (r-x<>i)and(l<>i) then inc(p2);
        inc(ans,p1*p2);
        inc(l,p1);
        dec(r,p1);
      end;
    end;
  end;
  assign(g,'output.txt');
  rewrite(g);
  writeln(g,ans*2);
  close(g);
end.