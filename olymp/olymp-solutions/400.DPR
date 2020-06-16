Var
  n,i:longint;
  s:array[1..130] of string;
begin
  reset(input,'input.txt');
  read(n);
  s[1]:='1';s[2]:='2';s[3]:='2';s[4]:='2';s[5]:='6';
  s[6]:='8';s[7]:='10';s[8]:='18';s[9]:='20';s[10]:='20';
  for i:=11 to 130 do s[i]:=s[i-7]+'8';
  for i:=0 to 15 do s[128-7*i,3]:='0';
  rewrite(output,'output.txt');
  write(s[n]);
end.