{$apptype console}
const
  maxN=40;
  maxV=maxN*maxN*4;
  maxL=30000;
  pushMultiplier=$30000;
  inf=maxlongint;
  di:array[1..4] of longint=(1,-1,0,0);
  dj:array[1..4] of longint=(0,0,1,-1);
  cmd:array[1..4] of char=('s','n','e','w');
type
  TVertex=record
    exists,flag,stop:boolean;
    d:longint;
    prevI,prevJ,prevK:longint;
  end;
  TPos=record
    i,j:longint;
  end;
  TVertices=array[0..maxN+1,0..maxN+1,1..4] of TVertex;
var
  n,m,ansLen,bi,bj,yi,yj,ti,tj:longint;
  f:array[-1..maxN+2,-1..maxN+2] of char;
  hlp:array[1..maxN,1..maxN,1..4,1..4] of longint;
  v:TVertices;
  mrk:array[0..maxN+1,0..maxN+1] of longint;
  answer:array[1..maxL] of char;
  ok:boolean;
function BuildPath(i0,j0,i1,j1:longint;mode:longint;var s:string;var c:longint):boolean;
label found;
var
  i,j,k,ii,jj,head,tail:longint;
  q:array[1..maxV] of TPos;
begin
  fillchar(mrk,sizeof(mrk),0);
  mrk[i0,j0]:=-1;
  head:=1;
  tail:=1;
  q[1].i:=i0;
  q[1].j:=j0;
  while head>=tail do begin
    i:=q[tail].i;
    j:=q[tail].j;
    if f[i,j]='.' then begin
      if (i=i1)and(j=j1) then goto found;
      for k:=1 to 4 do begin
        ii:=i+di[k];
        jj:=j+dj[k];
        if mrk[ii,jj]=0 then begin
          mrk[ii,jj]:=k;
          inc(head);
          q[head].i:=ii;
          q[head].j:=jj;
        end;
      end;
    end;
    inc(tail);
  end;
  s:='';
  c:=0;
  BuildPath:=false;
  exit;
  found:
  s:='';
  c:=0;
  i:=i1;
  j:=j1;
  if (mode=1) then
    while mrk[i,j]<>-1 do begin
      s:=cmd[mrk[i,j]]+s;
      ii:=i-di[mrk[i,j]];
      jj:=j-dj[mrk[i,j]];
      i:=ii;
      j:=jj;
    end;
  if (mode=2) then
    while mrk[i,j]<>-1 do begin
      inc(c);
      ii:=i-di[mrk[i,j]];
      jj:=j-dj[mrk[i,j]];
      i:=ii;
      j:=jj;
    end;
  BuildPath:=true;
end;
procedure BuildHelper;
var
  i,j,i1,j1,i2,j2,k,l,c:longint;
  s:string;
  flag:boolean;
begin
  for i:=1 to n do
    for j:=1 to m do
      for k:=1 to 4 do
        for l:=1 to 4 do begin
          hlp[i,j,k,l]:=-1;
          if f[i,j]='.' then begin
            i1:=i+di[k];
            j1:=j+dj[k];
            i2:=i+di[l];
            j2:=j+dj[l];
            if f[i1,j1]<>'.' then continue;
            if f[i2,j2]<>'.' then continue;
            f[i,j]:='B';
            flag:=BuildPath(i1,j1,i2,j2,2,s,c);
            f[i,j]:='.';
            if flag then hlp[i,j,k,l]:=c;
          end;
        end;
end;
procedure InitVertices;
var
  i,j,k,ii,jj,c:longint;
  s:string;
  flag:boolean;
begin
  fillchar(v,sizeof(v),false);
  for i:=1 to n do
    for j:=1 to m do
      for k:=1 to 4 do begin
        v[i,j,k].exists:=false;
        v[i,j,k].flag:=true;
        ii:=i+di[k];
        jj:=j+dj[k];
        if f[ii,jj]<>'.' then continue;
        v[i,j,k].exists:=true;
        v[i,j,k].flag:=false;
        v[i,j,k].d:=inf;
        v[i,j,k].stop:=false;
        f[bi,bj]:='B';
        flag:=BuildPath(yi,yj,ii,jj,2,s,c);
        f[bi,bj]:='.';
        if (i=bi)and(j=bj)and flag then begin
          v[i,j,k].d:=c;
          v[i,j,k].stop:=true;
        end;
      end;
end;
procedure FindMin;
var
  i,j,k,ii,jj,kk,min:longint;
begin
  repeat
    min:=inf;
    ii:=0;
    jj:=0;
    kk:=0;
    for i:=1 to n do
      for j:=1 to m do
        for k:=1 to 4 do
          if v[i,j,k].exists and not v[i,j,k].flag and
             (v[i,j,k].d<min) then begin
            min:=v[i,j,k].d;
            ii:=i;
            jj:=j;
            kk:=k;
          end;
    if min=inf then break;
    for k:=1 to 4 do
      if hlp[ii,jj,kk,k]<>-1 then
        if v[ii,jj,k].d>v[ii,jj,kk].d+hlp[ii,jj,kk,k] then begin
          v[ii,jj,k].d:=v[ii,jj,kk].d+hlp[ii,jj,kk,k];
          v[ii,jj,k].prevI:=ii;
          v[ii,jj,k].prevJ:=jj;
          v[ii,jj,k].prevK:=kk;
        end;
    i:=ii-di[kk];
    j:=jj-dj[kk];
    if v[i,j,kk].exists and (v[i,j,kk].d>v[ii,jj,kk].d+1) then begin
      v[i,j,kk].d:=v[ii,jj,kk].d+pushMultiplier;
      v[i,j,kk].prevI:=ii;
      v[i,j,kk].prevJ:=jj;
      v[i,j,kk].prevK:=kk;
    end;
    v[ii,jj,kk].flag:=true;
  until false;
end;
procedure PutCh(ch:char);
begin
  inc(ansLen);
  answer[ansLen]:=ch;
end;
procedure PutStr(var s:string);
var
  i:longint;
begin
  for i:=length(s) downto 1 do PutCh(s[i]);
end;
procedure BuildAnswer;
var
  i,j,k,pi,pj,pk,min,c:longint;
  s:string;
begin
  min:=inf;
  j:=0;
  for i:=1 to 4 do
    if v[ti,tj,i].exists and (v[ti,tj,i].d<min) then begin
      j:=i;
      min:=v[ti,tj,i].d;
    end;
  if min=inf then begin
    ok:=false;
    exit;
  end;
  ok:=true;
  ansLen:=0;
  k:=j;
  i:=ti;
  j:=tj;
  while not v[i,j,k].stop do begin
    pi:=v[i,j,k].prevI;
    pj:=v[i,j,k].prevJ;
    pk:=v[i,j,k].prevK;
    if (i=pi)and(j=pj) then begin
      f[i,j]:='B';
      BuildPath(i+di[pk],j+dj[pk],i+di[k],j+dj[k],1,s,c);
      PutStr(s);
      f[i,j]:='.';
    end else begin
      if pi<i then PutCh('S');
      if pi>i then PutCh('N');
      if pj<j then PutCh('E');
      if pj>j then PutCh('W');
    end;
    i:=pi;
    j:=pj;
    k:=pk;
  end;
  f[bi,bj]:='B';
  BuildPath(yi,yj,i+di[k],j+dj[k],1,s,c);
  PutStr(s);
end;
procedure Solve;
begin
  BuildHelper;
  InitVertices;
  FindMin;
  BuildAnswer;
end;
procedure ReadData;
var
  i,j:longint;
  s:string;
begin
  fillchar(f,sizeof(f),'X');
  readln(n,m);
  for i:=1 to n do begin
    readln(s);
    for j:=1 to m do begin
      f[i,j]:=s[j];
      if s[j]='B' then begin
        bi:=i;
        bj:=j;
        f[i,j]:='.';
      end;
      if s[j]='Y' then begin
        yi:=i;
        yj:=j;
        f[i,j]:='.';
      end;
      if s[j]='T' then begin
        ti:=i;
        tj:=j;
        f[i,j]:='.';
      end;
    end;
  end;
end;
procedure WriteData;
var
  i:longint;
begin
  if ok then begin
    writeln('YES');
    for i:=ansLen downto 1 do write(answer[i]);
  end else
    writeln('NO');
end;
begin
  reset(input,'input.txt');
  ReadData;
  Solve;
  rewrite(output,'output.txt');
  WriteData;
end.