{$apptype console}
{$M 50000000,50000000}
const
  HIGH=20;
  pmax=100;
  nmax=30;
  NOP:set of char=['a'..'z','0'..'9','=','(',')'];
type
  int=integer;
  real=extended;
  optype=(_absent,_unary,_binary);
  tptr=^ttree;
  ttree=record
    oper:char;
    l,r:tptr;
    finVar:char;
   finValue:int;
  end;
  ttable=array[-1..pmax,-1..pmax] of int;
var
  n,m,p,ans:int;
  ops:array[1..nmax] of char;
  op:array[#33..#127] of tptr;
  prior:array[#33..#127] of int;
  tp:array[#33..#127] of optype;
  vars:array['a'..'z'] of int;
  inv:array[0..pmax] of int;
  results:array[#33..#127] of ^ttable;
  curChar:char;

procedure init;
begin
  ans:=0;
  prior['+']:=5;
  prior['-']:=5;
  prior['*']:=15;
  prior['/']:=15;
  tp['+']:=_binary;
  tp['-']:=_binary;
  tp['*']:=_binary;
  tp['/']:=_binary;
end;

function isOperation(c:char):boolean;
begin
  isOperation:=not(c in NOP);
end;

function getChar:char;
var
  c:char;
begin
  read(c);
  getChar:=c;
end;

function getNumber(res:int):int;
begin
  repeat
    curChar:=getChar;
    if curChar in ['0'..'9'] then res:=res*10+ord(curChar)-ord('0');
  until not (curChar in ['0'..'9']);
  getNumber:=res;
end;

function rec(level:int):tptr;
var
  res,t,argument:tptr;
  lastOp:char;
begin
  res:=nil;
  lastOp:=#0;
  while not ((curChar=' ')or(ord(curChar)<=32)or(curChar=')')) do begin
    if not IsOperation(curChar) then begin
      if level=HIGH then begin
        new(res);
        res^.oper:=#0;
        if curChar in ['a'..'z'] then begin
          res^.finVar := curChar;
          read(curChar);
        end
        else
        if curChar in ['0'..'9'] then
          res^.finValue:=getNumber(ord(curChar)-ord('0'))
        else
        if curChar='(' then begin
          read(curChar);
          res:=rec(1);
          read(curChar);
        end;
      end else begin
      argument:=rec(level+1);
      if lastOp=#0 then res:=argument else begin
         new(t);
         t^.oper:=lastOp;
         t^.l:=res;
         t^.r:=argument;
         res:=t;
        end;
      end;
    end else begin
      if prior[curChar]=level then begin
        if level=HIGH then begin
          new(res);
          res^.oper:=curChar;
          read(curchar);
          res^.l:=rec(level);
        end else begin
          lastOp:=curChar;
          read (curChar);
        end;
      end else begin
        if tp[curChar]=_unary then begin
          argument:=rec(level+1);
          if lastOp=#0 then res:=argument else begin
            new(t);
            t^.oper:=lastOp;
            t^.l:=res;
            t^.r:=argument;
            res:=t;
          end;
        end else break;
      end;
    end;
  end;
  rec:=res;
end;

function parse(level:int):int;
var
  res,argument:int;
  lastOp:char;
begin
  res:=0;
  lastOp:=#0;
  while not((curChar=' ')or(ord(curChar)<=32)or(curChar=')')) do begin
    if not IsOperation(curChar) then begin
      if level=HIGH then begin
        if curChar in ['a'..'z'] then begin
          res:=vars[curChar];
          curChar:=getchar;
        end else
          if curChar in ['0'..'9'] then res:=getNumber(ord(curChar)-ord('0'))
            else
              if curChar='(' then begin
                curChar:=getChar;
                res:=parse(1);
                curChar:=getChar;
              end;
      end else begin
        argument:=parse(level+1);
        if lastOp=#0 then res:=argument
                     else res:=results[lastOp]^[res][argument];
      end;
    end else begin
      if prior[curChar]=level then begin
        if level=HIGH then begin
          lastOp:=curChar;
          curChar:=getChar;
          argument:=parse(level);
          res:=results[lastOp]^[argument][0]
        end else begin
          lastOp:=curChar;
          curChar:=getChar;
        end;
      end else begin
        if tp[curChar]=_unary then begin
          argument:=parse(level+1);
          if lastOp=#0 then res:=argument
                       else res:=results[lastOp]^[res][argument];
        end else break;
      end;
    end;
  end;
  parse:=res;
end;

procedure readUnary(number:int);
var c,_:char;
begin
  repeat
    read(c);
  until not(c=' ');
  read(_);
  read(_);
  prior[c]:=HIGH;
  tp[c]:=_unary;
  read(curChar);
  op[c]:=rec(1);
  readln;
  ops[number]:=c;
end;

procedure readBinary(number:int);
var
  c,_:char;
  pr:int;
begin
  read(pr);
  repeat
    read(c);
  until not(c=' ');
  read(c);
  read(_);
  read(_);
  prior[c]:=pr;
  tp[c]:=_binary;
  read(curChar);
  op[c]:=rec(1);
  readln;
  ops[number]:=c;
end;

procedure readVariable;
var c,_:char;
begin
 read(c);
 read(_);
 readln(vars[c]);
end;

procedure readdata;
var
  i:int;
  c:char;
begin
  readln(p);
  readln(n);
  for i:=1 to n do begin
    read(c);
    if c='U' then readUnary(i)
             else readBinary(i);
  end;
  readln(m);
  for i:=1 to m do readVariable;
end;

function power(a:int;k:int):int;
var
  res:int;
begin
  res:=1;
  while k>0 do begin
    if k and 1=1 then begin
      res:=(res*a) mod p;
      dec(k);
    end else begin
      a:=a*a mod p;
      k:=k shr 1;
    end;
  end;
  power:=res;
end;

function calc(p:tptr):int;
begin
  if p^.oper=#0 then begin
    if not (p^.finVar=#0) then calc:=vars[p^.finVar]
                          else calc:=p^.finValue;
  end else begin
    if tp[p^.oper]=_unary then calc:=results[p^.oper]^[calc(p^.l),0]
                               else calc:=results[p^.oper]^[calc(p^.l),calc(p^.r)];
  end;
end;

procedure solve;
var
  i,arg1,arg2 :int;
begin
  for i:=1 to p-1 do inv[i]:=power(i,p-2);
  inv[0]:=-1;
  new(results['+']);
  new(results['-']);
  new(results['*']);
  new(results['/']);
  for arg1:=-1 to p-1 do
    for arg2:=-1 to p-1 do begin
    if not(arg1=-1) and not(arg2=-1) then begin
      results['+'][arg1][arg2]:=(arg1+arg2) mod p;
      results['-'][arg1][arg2]:=(arg1-arg2+p) mod p;
      results['*'][arg1][arg2]:=(arg1*arg2) mod p;
      if arg2>0 then results['/'][arg1][arg2]:=(arg1*inv[arg2]) mod p
                else results['/'][arg1][arg2]:=-1;
    end else begin
      results['+'][arg1][arg2]:=-1;
      results['-'][arg1][arg2]:=-1;
      results['*'][arg1][arg2]:=-1;
      results['/'][arg1][arg2]:=-1;
     end;
  end;
  for i:=1 to n do begin
    new(results[ops[i]]);
    fillchar(results[ops[i]]^,sizeof(results[ops[i]]^),0);
    if tp[ops[i]]=_binary then
      for arg1:=-1 to p-1 do
        for arg2:=-1 to p-1 do begin
          vars['a']:=arg1;
          vars['b']:=arg2;
          if (arg1>-1)and(arg2>-1) then results[ops[i]]^[arg1][arg2]:=calc(op[ops[i]])
                                   else results[ops[i]]^[arg1][arg2]:=-1;
        end
    else
      for arg1:=-1 to p-1 do begin
        vars['a']:=arg1;
        if arg1>=0 then results[ops[i]]^[arg1][0]:=calc(op[ops[i]])
                   else results[ops[i]]^[arg1][0]:=-1;
      end;
  end;
  curChar:=getChar;
  ans:=parse(1);
end;

begin
  init;
  readdata;
  solve;
  write(ans);
end.