{$apptype console}
var
  a,b,rrr:array[1..2,1..40001]of smallint;
  n,m,i,tt1,tt2,lb1,lb2,mt,mmr,tmp,tmp2,tmp3,cnt,rcnt:longint;
  nav,van,t,ff,mr,pre,cl,u,t1,t2,sc,sc2,w,u2:array[1..40001]of smallint;
function more(i,j:longint):boolean;
begin
  more:=(a[1,i]>a[1,j]);
end;
procedure swap(b,c:longint);
var
  d:longint;
begin
  d:=a[1,b];
  a[1,b]:=a[1,c];
  a[1,c]:=d;
  d:=a[2,b];
  a[2,b]:=a[2,c];
  a[2,c]:=d;
end;
procedure he_up(a:longint);
begin
  while true do begin
    if a=1 then exit;
    if not more(a,a div 2) then exit;
    swap(a,a div 2);
    a:=a div 2;
  end;
end;
procedure he_do(e:longint);
begin
  while true do begin
    if e*2>cnt then exit else
      if e*2=cnt then begin
        if more(e*2,e) then begin
          swap(e*2,e);
          e:=e*2;
        end else exit;
      end else begin
        if more(e*2,e*2+1) then begin
          if more(e*2,e) then begin
            swap(e*2,e);
            e:=e*2;
          end else exit;
        end else begin
          if more(e*2+1,e) then begin
            swap(e*2+1,e);
            e:=e*2+1;
          end else exit;
        end;
      end;
  end;
end;
procedure add(t1,t2:longint);
begin
  inc(cnt);
  a[1,cnt]:=t1;
  a[2,cnt]:=t2;
  he_up(cnt);
end;
procedure dfs(v:longint);
var
  i:longint;
begin
  if u[v]<>0 then exit;
  u[v]:=-1;
  for i:=nav[v] to nav[v+1]-1 do dfs(a[2,i]);
  inc(mt);
  t[mt]:=v;
end;
procedure sfd(v:longint);
var
  i:longint;
begin
  if mr[v]<>0 then exit;
  mr[v]:=mmr;
  pre[mmr]:=v;
  for i:=van[v] to van[v+1]-1 do sfd(b[2,i]);
end;
function tryclc(v,tmr:longint):longint;
var
  i:longint;
begin
  tryclc:=0;
  if (tmr<>mr[v]) then begin
    if u2[mr[v]]<>0 then exit;
   end else if u[v]<>0 then exit;
  u[v]:=1;
  u2[mr[v]]:=1;
  if t2[mr[v]]=0 then begin
    if ff[mr[v]]=0 then begin
      cl[mr[v]]:=mr[v];
      ff[mr[v]]:=1;
      tryclc:=mr[v];
    end;
    exit;
  end;
  if cl[mr[v]]<>0 then exit;
  for i:=nav[v] to nav[v+1]-1 do begin
    cl[mr[v]]:=tryclc(a[2,i],mr[v]);
    if cl[mr[v]]<>0 then begin
      tryclc:=cl[mr[v]];
      exit;
    end;
  end;
end;
procedure tadd(a,b:longint);
begin
  inc(rcnt);
  rrr[1,rcnt]:=a;
  rrr[2,rcnt]:=b;
end;
begin
  readln(n,m);
  for i:=1 to m do begin
    readln(tt1,tt2);
    add(tt2,tt1);
  end;
  for i:=1 to m do begin
    swap(1,cnt);
    dec(cnt);
    he_do(1);
  end;
  for i:=1 to m do
    if nav[a[1,i]]=0 then nav[a[1,i]]:=i;
  nav[n+1]:=m+1;
  for i:=n downto 1 do
    if nav[i]=0 then nav[i]:=nav[i+1];
  b:=a;
  van:=nav;
  for i:=1 to m do add(b[2,i],b[1,i]);
  for i:=1 to m do begin
    swap(1,cnt);
    dec(cnt);
    he_do(1);
  end;
  fillchar(nav,sizeof(nav),0);
  for i:=1 to m do
    if nav[a[1,i]]=0 then nav[a[1,i]]:=i;
  nav[n+1]:=m+1;
  for i:=n downto 1 do
   if nav[i]=0 then nav[i]:=nav[i+1];
  for i:=1 to n do dfs(i);
  for i:=1 to n do begin
    if mr[t[n-i+1]]=0 then inc(mmr);
    sfd(t[n-i+1]);
  end;
  if mmr=1 then begin
    writeln(0);
    halt(0);
  end;
  for i:=1 to m do begin
    if mr[a[1,i]]<>mr[a[2,i]] then t2[mr[a[1,i]]]:=1;
    if mr[a[1,i]]<>mr[a[2,i]] then t1[mr[a[2,i]]]:=1;
  end;
  lb1:=1;
  lb2:=1;
  for i:=1 to mmr do begin
    if t1[i]=0 then lb1:=i;
    if t2[i]=0 then lb2:=i;
  end;
  fillchar(u,sizeof(u),0);
  for i:=1 to mmr do
    if t1[i]=0 then tryclc(pre[i],mr[pre[i]]);
  tmp:=0;
  tmp2:=0;
  tmp3:=0;
  for i:=1 to mmr do
    if t1[i]=0 then begin
      if (cl[i]<>0) then begin
        inc(tmp);
        sc[tmp]:=i;
      end else begin
        inc(tmp2);
        sc2[tmp2]:=i;
      end;
    end;
  for i:=1 to tmp do begin
    tadd(pre[cl[sc[i mod tmp+1]]],pre[sc[i]]);
    w[cl[sc[i mod tmp+1]]]:=1;
  end;
  for i:=1 to mmr do
    if (t2[i]=0)and(w[i]=0) then begin
      if tmp3<tmp2 then begin
        inc(tmp3);
        w[i]:=1;
        tadd(pre[i],pre[sc2[tmp3]]);
      end else begin
        w[i]:=1;
        tadd(pre[i],pre[lb1]);
      end;
    end;
  for i:=tmp3+1 to tmp2 do
    tadd(pre[lb2],pre[sc2[i]]);
  writeln(rcnt);
  for i:=1 to rcnt do writeln(rrr[1,i],' ',rrr[2,i]);
end.