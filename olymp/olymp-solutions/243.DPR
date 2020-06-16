{$APPTYPE CONSOLE}
const
  nmax=300;
var
  n,ans,i:longint;
  s:string;
  lf,rg:array[1..nmax] of longint;
  log:array[1..nmax,1..nmax] of longint;
  col:array[1..nmax] of char;
function rec(l,r:longint):longint;
var
  mid:longint;
begin
  if l>r then begin
    Result:=0;
    exit;
  end;
  if log[l,r]>0 then begin
    Result:=log[l,r];
    exit;
  end;
  if l=r then Result:=1
           else begin
    if s[l]=s[r] then begin
      Result:=rec(l+1,r);
      if Result>rec(l,r-1) then Result:=rec(l,r-1);
    end else Result:=r-l+1;
    for mid:=l to r-1 do
      if rec(l,mid)+rec(mid+1,r)<Result then
        Result:=rec(l,mid)+rec(mid+1,r);
      log[l,r]:=Result;
    end;
  end;
procedure printans(l,r:longint;dir:longint);
var
  mid,pans,z:longint;
begin
  if l>r then exit;
  if l=r then begin
    inc(ans);
    lf[ans]:=l;
    rg[ans]:=r;
    col[ans]:=s[l];
  end else begin
    if s[l]=s[r] then begin
      if rec(l+1,r)<rec(l,r-1) then begin
        pans:=ans+1;
        printans(l+1,r,2);
        lf[pans]:=l;
      end else begin
        pans:=ans+1;
        printans(l,r-1,1);
        rg[pans]:=r;
      end;
    end else begin
      z:=rec(l,r);
      for mid:=l to r-1 do
        if rec(l,mid)+rec(mid+1,r)=z then begin
          if dir=1 then begin
            printans(l,mid,1);
            printans(mid+1,r,2);
          end else begin
            printans(mid+1,r,2);
            printans(l,mid,1);
          end;
          break;
        end;
    end;
  end;
end;
begin
  reset(input,'input.txt');
  readln(n);
  readln(s);
  ans:=rec(1,n);
  rewrite(output,'output.txt');
  writeln(ans);
  ans:=0;
  printans(1,length(s),1);
  for i:=1 to ans do writeln(lf[i],' ',rg[i],' ',col[i]);
end.