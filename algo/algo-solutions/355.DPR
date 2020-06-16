{$APPTYPE CONSOLE}
const
  di:array[1..4] of integer=(-1,1,0,0);
  dj:array[1..4] of integer=(0,0,-1,1);
  pr:array[1..4] of integer=(2,1,4,3);
  let:array[1..4] of char='DURL';
  MaxN=100;
  MaxLen=MaxN*MaxN*3;
var
  a:array[0..MaxN+1,0..MaxN+1,0..1] of integer;
  from:array[1..MaxN,1..MaxN,0..1] of byte;
  si,sj,i,j,k,i0,j0,n,m:integer;
  ch:char;
procedure move(i,j,k,l:integer;var ii,jj,kk:integer);
begin
  ii:=i+di[l];jj:=j+dj[l];
  kk:=k;
  if (i=i0)and(j<j0)and(l=1) then kk:=1-kk;
  if (i=i0-1)and(j<j0)and(l=2) then kk:=1-kk;
end;
procedure search;
var
  q:array[1..MaxN*MaxN*2] of record
    i,j,k:byte;
  end;
  i,j,k,ii,jj,kk,b:integer;
  cl:integer;
  l,r:integer;
begin
  q[1].i:=si;
  q[1].j:=sj;
  q[1].k:=0;
  l:=1;r:=1;
  while l<=r do begin
    i:=q[l].i;
    j:=q[l].j;
    k:=q[l].k;
    cl:=a[i,j,k];
    inc(l);
    for b:=1 to 4 do begin
      move(i,j,k,b,ii,jj,kk);
      if a[ii,jj,kk]>cl+1 then begin
        a[ii,jj,kk]:=cl+1;
        from[ii,jj,kk]:=b;
        inc(r);
        q[r].i:=ii;
        q[r].j:=jj;
        q[r].k:=kk;
      end;
    end;
  end;
end;
begin
  readln(n,m);
  fillchar(a,sizeof(a),255);
  for i:=1 to n do begin
    for j:=1 to m do begin
      read(ch);
      case ch of
        '.':begin
          a[i,j,0]:=MaxLen;
          a[i,j,1]:=MaxLen;
        end;
        '&':begin
          a[i,j,0]:=0;
          a[i,j,1]:=MaxLen;
          from[i,j,0]:=0;
          si:=i;
          sj:=j;
        end;
        'Z':begin
          i0:=i;
          j0:=j;
        end;
      end;
    end;
    readln;
  end;
  search;
  if a[si,sj,1]<MaxLen then begin
    i:=si;
    j:=sj;
    k:=1;
    repeat
      if from[i,j,k]=0 then break;
      write(let[from[i,j,k]]);
      move(i,j,k,pr[from[i,j,k]],i,j,k);
    until false;
  end else writeln('Impossible');
end.