{$APPTYPE CONSOLE}
type
  tlist=^list;
  list=record
    x:longint;
    next:tlist;
  end;
var
  i,n,k,s1,s2,s3,stack,code,num:longint;
  op,numst,ch,s:string;
  head:array of tlist;
Procedure Push(var t:tlist;q:longint);
var
  curr:tlist;
begin
  new(curr);
  curr^.x:=q;
  curr^.next:=t;
  t:=curr;
end;
Function Pop(var t:tlist):longint;
var
  curr:tlist;
begin
  curr:=t;
  Pop:=t^.x;
  t:=curr^.next;
  Dispose(curr);
end;
Function Top(t:tlist):longint;
begin
  Top:=t^.x;
end;
begin
  readln(n,k);
  SetLength(head,n+1);
  for i:=1 to k do begin
    readln(s);
    s1:=pos('(',s);
    op:=copy(s,1,s1-1);
    if op='PUSH' then begin
      s2:=pos(',',s);
      s3:=pos(')',s);
      numst:=copy(s,s1+1,s2-s1-1);
      ch:=copy(s,s2+1,s3-s2-1);
      val(numst,stack,code);
      val(ch,num,code);
      Push(head[stack],num);
    end;
    if op='POP' then begin
      s2:=pos(')',s);
      numst:=copy(s,s1+1,s2-s1-1);
      val(numst,stack,code);
      write(Pop(head[stack]),' ');
    end;
    if op='TOP' then begin
      s2:=pos(')',s);
      numst:=copy(s,s1+1,s2-s1-1);
      val(numst,stack,code);
      write(Top(head[stack]),' ');
    end;
  end;
end.