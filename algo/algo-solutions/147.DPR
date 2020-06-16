{$APPTYPE CONSOLE}
type
  tlist=^list;
  list=record
    x:longint;
    next:tlist;
  end;
var
  i,n,k,s1,s2,s3,queue,code,num:longint;
  op,numst,ch,s:string;
  head,tail:array of tlist;
Procedure Push(var h:tlist;var t:tlist;q:longint);
var
  curr:tlist;
begin
  new(curr);
  curr^.x:=q;
  curr^.next:=NIL;
  if (h=NIL)and(t=NIL) then begin
    t:=curr;
    h:=curr;
  end else begin
    t^.next:=curr;
    t:=curr;
  end;
end;
Function Pop(var h:tlist;var t:tlist):longint;
var
  curr:tlist;
begin
  curr:=h;
  Pop:=curr^.x;
  h:=curr^.next;
  if h=NIL then t:=NIL;
  Dispose(curr);
end;
Function Top(h:tlist):longint;
begin
  Top:=h^.x;
end;
begin
  readln(n,k);
  SetLength(head,n+1);
  SetLength(tail,n+1);
  for i:=1 to k do begin
    readln(s);
    s1:=pos('(',s);
    op:=copy(s,1,s1-1);
    if op='PUSH' then begin
      s2:=pos(',',s);
      s3:=pos(')',s);
      numst:=copy(s,s1+1,s2-s1-1);
      ch:=copy(s,s2+1,s3-s2-1);
      val(numst,queue,code);
      val(ch,num,code);
      Push(head[queue],tail[queue],num);
    end;
    if op='POP' then begin
      s2:=pos(')',s);
      numst:=copy(s,s1+1,s2-s1-1);
      val(numst,queue,code);
      write(Pop(head[queue],tail[queue]),' ');
    end;
    if op='TOP' then begin
      s2:=pos(')',s);
      numst:=copy(s,s1+1,s2-s1-1);
      val(numst,queue,code);
      write(Top(head[queue]),' ');
    end;
  end;
end.