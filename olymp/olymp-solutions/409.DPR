{$APPTYPE CONSOLE}
Var
  f,g:text;
  x,y,r:longint;
Function Nod(a,b:longint):longint;
label
  lb;
var
  r:longint;
begin
  lb:
  r:=a mod b;
  if r=0 then begin
    Nod:=b;
    exit;
  end else begin
    a:=b;
    b:=r;
    goto lb;
  end;
end;
begin
  assign(f,'input.txt');
  reset(f);
  read(f,x,y);
  close(f);
  assign(g,'output.txt');
  rewrite(g);
  r:=0;
  if Nod(x,y)<>1 then begin
    writeln(g,'-1');
    close(g);
    halt;
  end;
  while (x<>1)or(y<>1) do begin
    if (x=1)and(y<>1) then begin
      inc(r,y-1);
      break;
    end;
    if (y=1)and(x<>1) then begin
      inc(r,x-1);
      break;
    end;    
    if x>y then begin
      inc(r,x div y);
      x:=x mod y;
      continue;
    end;
    if x<y then begin
      inc(r,y div x);
      y:=y mod x;
      continue;
    end;
  end;
  writeln(g,r);
  close(g);
end.