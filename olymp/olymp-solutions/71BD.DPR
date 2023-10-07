{$APPTYPE CONSOLE}
type
  pt=record
    x,y:double;
  end;
Var
  n,i,j:longint;
  z:array[1..6] of pt;
Function P(x1,y1,x2,y2,x3,y3:double):double;
begin
  P:=0.5*abs((x2-x1)*(y3-y1)-(x3-x1)*(y2-y1));
end;
Function ok(a1,a2,a3,a4,a5,a6:longint):boolean;
var
  b:array[0..9] of double;
  l:longint;
begin
  for l:=0 to 9 do b[l]:=0;
  if (P(z[a1].x,z[a1].y,z[a2].x,z[a2].y,z[a3].x,z[a3].y)=0) then begin
    ok:=False;
    exit;
  end;
  b[0]:=P(z[a4].x,z[a4].y,z[a5].x,z[a5].y,z[a6].x,z[a6].y);
  b[1]:=P(z[a1].x,z[a1].y,z[a4].x,z[a4].y,z[a5].x,z[a5].y);
  b[2]:=P(z[a1].x,z[a1].y,z[a5].x,z[a5].y,z[a6].x,z[a6].y);
  b[3]:=P(z[a1].x,z[a1].y,z[a4].x,z[a4].y,z[a6].x,z[a6].y);
  b[4]:=P(z[a2].x,z[a2].y,z[a4].x,z[a4].y,z[a5].x,z[a5].y);
  b[5]:=P(z[a2].x,z[a2].y,z[a5].x,z[a5].y,z[a6].x,z[a6].y);
  b[6]:=P(z[a2].x,z[a2].y,z[a4].x,z[a4].y,z[a6].x,z[a6].y);
  b[7]:=P(z[a3].x,z[a3].y,z[a4].x,z[a4].y,z[a5].x,z[a5].y);
  b[8]:=P(z[a3].x,z[a3].y,z[a5].x,z[a5].y,z[a6].x,z[a6].y);
  b[9]:=P(z[a3].x,z[a3].y,z[a4].x,z[a4].y,z[a6].x,z[a6].y);
  if (b[1]=0)or(b[2]=0)or(b[3]=0)or(b[4]=0)or(b[5]=0)or
     (b[6]=0)or(b[7]=0)or(b[8]=0)or(b[9]=0)then begin
       ok:=False;
       exit;
     end;
  if (abs(b[1]+b[2]+b[3]-b[0])<1e-9)and
     (abs(b[4]+b[5]+b[6]-b[0])<1e-9)and
     (abs(b[7]+b[8]+b[9]-b[0])<1e-9)then ok:=True
                                    else ok:=False;
end;
Begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(n);
  for i:=1 to n do begin
    for j:=1 to 6 do read(z[j].x,z[j].y);
    if ok(1,2,3,4,5,6) or ok(1,2,4,3,5,6) or ok(1,2,5,3,4,6) or
       ok(1,2,6,3,4,5) or ok(1,3,4,2,5,6) or ok(1,3,5,2,4,6) or
       ok(1,3,6,2,4,5) or ok(1,4,5,2,3,6) or ok(1,4,6,2,3,5) or
       ok(1,5,6,2,3,4) or ok(4,5,6,1,2,3) or ok(3,5,6,1,2,4) or
       ok(3,4,6,1,2,5) or ok(3,4,5,1,2,6) or ok(2,5,6,1,3,4) or
       ok(2,4,6,1,3,5) or ok(2,4,5,1,3,6) or ok(2,3,6,1,4,5) or
       ok(2,3,5,1,4,6) or ok(2,3,4,1,5,6) then writeln('YES')
                                          else writeln('NO');
  end;
end.