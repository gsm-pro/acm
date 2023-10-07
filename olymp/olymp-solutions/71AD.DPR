{$apptype console}
var
  s,t,q:string;
  a1,a2,kol:longint;
  ok:boolean;
Function palin(var w:string):boolean;
var
  i:longint;
begin
  for i:=1 to length(w) div 2 do
    if w[i]<>w[length(w)-i+1] then begin
      palin:=false;
      exit;
    end;
  palin:=true;
end;
Procedure rec(w1:string;x,y:longint;w2:string;z,v:longint);
begin
  if kol>50000 then ok:=false;
  if (x>z)or(y>v) then begin
    q:='';
    if x<=z then q:=q+copy(s,x,z-x+1);
    if y<=v then q:=q+copy(t,y,v-y+1);
    q:=w1+q+w2;
    if (length(t+s)=length(q))and(palin(q)) then begin
      write(q);
      halt(0);
    end;
    exit;
  end;
  inc(kol);
  if not ok then exit;
  if x<>z then if s[x]=s[z] then rec(w1+s[x],x+1,y,s[z]+w2,z-1,v);
  if s[x]=t[v] then rec(w1+s[x],x+1,y,t[v]+w2,z,v-1);
  if t[y]=s[z] then rec(w1+t[y],x,y+1,s[z]+w2,z-1,v);
  if y<>v then if t[y]=t[v] then rec(w1+t[y],x,y+1,t[v]+w2,z,v-1);
end;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  ok:=true;
  readln(s);
  readln(t);
  a1:=length(s);
  a2:=length(t);
  kol:=0;
  rec('',1,1,'',a1,a2);
  write(-1);
end.