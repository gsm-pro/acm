var
  x,d:extended;
  a:longint;
  s:string;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(s);
  val(s,x,a);
  if x=1 then begin
    write('1 1');
    exit;
  end;
  a:=1;
  while (a<=999) do begin
    inc(a);
    d:=(ln(x))/(ln(a));
    if (abs(d-round(d))<1e-15)and(d<=1000) then begin
      write(a,' ',d:0:0);
      a:=1111;
    end;
  end;
end.