type
  stud=record
    im:string[8];
    kol,sum:longint;
  end;
var
  cls:array[1..1000] of stud;
  i,j,n,max,mark:integer;
  s:boolean;
  str:string;
  f,g:text;
  buf:stud;
begin
  assign(f,'input.txt');
  reset(f);
  readln(f,n);
  max:=0;
  for i:=1 to n do begin
    readln(f,str);
    readln(f,mark);
    s:=false;
    for j:=1 to max do begin
      if str=cls[j].im then begin
        inc(cls[j].kol);
        inc(cls[j].sum,mark);
        s:=true;
      end;
    end;
    if s=false then begin
      inc(max);
      cls[max].im:=str;
      cls[max].kol:=1;
      cls[max].sum:=mark;
    end;
  end;
  close(f);
  for i:=1 to max-1 do
    for j:=1 to max-1 do
      if cls[j].im>cls[j+1].im then begin
        buf:=cls[j];
        cls[j]:=cls[j+1];
        cls[j+1]:=buf;
      end;
  assign(g,'output.txt');
  rewrite(g);
  for i:=1 to max do writeln(g,cls[i].im,' ',trunc(cls[i].sum/cls[i].kol));
  close(g);
end.