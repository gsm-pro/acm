{$apptype console}
type
  PBor=^TBor;
  TBor=record
    s,l,r:longint;
    p:array[0..1] of PBor;
  end;
procedure add(var ab:PBor;const a:array of byte;l,r:longint);
var
  t,tv,i:longint;
  x:PBor;
begin
  if ab=nil then begin
    new(ab);
    ab^.l:=l;
    ab^.r:=r;
    for i:=0 to 1 do ab^.p[i]:=nil;
    exit;
  end;
  t:=l;
  tv:=ab^.l;
  while (tv<=ab^.r)and(t<=r)and(a[t]=a[tv]) do begin
    inc(t);
    inc(tv);
  end;
  if (tv>ab^.r) then begin
    if t>r then exit;
    add(ab^.p[a[t]],a,t,r);
  end else begin
    if t>r then exit;
    new(x);
    x^.l:=ab^.l;
    x^.r:=tv-1;
    x^.p[a[tv]]:=ab;
    ab^.l:=tv;
    ab:=x;
    new(x);
    ab^.p[a[t]]:=x;
    x^.l:=t;
    x^.r:=r;
    for i:=0 to 1 do x^.p[i]:=nil;
  end;
end;
var
  ab,bb,r:PBor;
  na,nb,i,k:longint;
  a,b:array[0..4002] of byte;
  sa,sb:string;
procedure inter(var r,ab,bb:PBor);
var
  ta,tb,i:longint;
  x:PBor;
begin
  if (ab=nil)or(bb=nil) then begin
    r:=nil;
    exit;
  end;
  ta:=ab^.l;
  tb:=bb^.l;
  while (ta<=ab^.r)and(tb<=bb^.r)and(a[ta]=b[tb]) do begin
    inc(ta);
    inc(tb);
  end;
  if (ta>ab^.r)and(tb>bb^.r) then begin
    new(r);
    r^.l:=ab^.l;
    r^.r:=ab^.r;
    for i:=0 to 1 do inter(r^.p[i],ab^.p[i],bb^.p[i]);
    exit;
  end;
  if (tb<=bb^.r) then begin
    new(x);
    x^.l:=bb^.l;
    x^.r:=tb-1;
    x^.p[b[tb]]:=bb;
    x^.p[(b[tb]+1) mod 2]:=nil;
    bb^.l:=tb;
    bb:=x;
  end;
  if (ta<=ab^.r) then begin
    new(x);
    x^.l:=ab^.l;
    x^.r:=ta-1;
    x^.p[a[ta]]:=ab;
    x^.p[(a[ta]+1) mod 2]:=nil;
    ab^.l:=ta;
    ab:=x;
  end;
  new(r);
  r^.l:=ab^.l;
  r^.r:=ab^.r;
  for i:=0 to 1 do inter(r^.p[i],ab^.p[i],bb^.p[i]);
  exit;
end;
procedure count(var b:PBor);
var
  s,i:longint;
begin
  if b=nil then exit;
  s:=0;
  for i:=0 to 1 do
    if b^.p[i]<>nil then begin
      count(b^.p[i]);
      inc(s,b^.p[i]^.s);
    end;
  b^.s:=s+b^.r-b^.l+1;
end;
procedure _out(b:PBor;k:longint);
var
  i:longint;
begin
  i:=b^.l;
  while (i<=b^.r)and(k>0) do begin
    write(chr(a[i]+ord('0')));
    inc(i);
    dec(k);
  end;
  if (k>0) then
    for i:=0 to 1 do
      if (b^.p[i]<>nil) then begin
        if (b^.p[i]^.s>=k) then begin
          _out(b^.p[i],k);
          exit;
        end;
        dec(k,b^.p[i]^.s);
      end;
end;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(sa);
  na:=length(sa);
  for i:=1 to na do a[i]:=ord(sa[i])-ord('0');
  readln(sb);
  nb:=length(sb);
  for i:=1 to nb do b[i]:=ord(sb[i])-ord('0');
  readln(k);
  new(ab);
  ab^.l:=1;
  ab^.r:=0;
  for i:=0 to 1 do ab^.p[i]:=nil;
  for i:=1 to na do add(ab,a,i,na);
  new(bb);
  bb^.l:=1;
  bb^.r:=0;
  for i:=0 to 1 do bb^.p[i]:=nil;
  for i:=1 to nb do add(bb,b,i,nb);
  inter(r,ab,bb);
  count(r);
  _out(r,k);
end.