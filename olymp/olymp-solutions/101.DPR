{$APPTYPE CONSOLE}
const
  N=5;
Var
  paint:array[1..N,1..N] of longint;
  start:string;
Procedure OutData;
Var
  i,j,k:LongInt;
begin
  if paint[1,1]=0 then writeln('0') else begin
    for k:=1 to N*N do
      for i:=1 to N do
        for j:=1 to N do
          if paint[i,j]=k then
            write(chr(ord('A')+i-1),chr(ord('0')+j));
    end;
  halt;
end;
procedure obhod(u,v,cur:longint);
begin
  if cur=N*N+1 then OutData;
  if (u<1) or (u>N) then exit;
  if (v<1) or (v>N) then exit;
  if paint[u,v]<>0 then exit;
  paint[u,v]:=cur;
  obhod(u-2,v-1,cur+1);
  obhod(u-1,v-2,cur+1);
  obhod(u+2,v-1,cur+1);
  obhod(u+1,v-2,cur+1);
  obhod(u-2,v+1,cur+1);
  obhod(u-1,v+2,cur+1);
  obhod(u+2,v+1,cur+1);
  obhod(u+1,v+2,cur+1);
  paint[u,v]:=0;
end;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  readln(start);
  fillchar(paint,sizeof(paint),0);
  if not odd(ord(start[1])+ord(start[2])) then
    obhod(ord(start[1])-ord('A')+1,ord(start[2])-ord('0'),1);
  OutData;
end.