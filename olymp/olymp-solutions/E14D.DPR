{$apptype console}
uses math;
const
	maxn=100;
	maxm=100;
var
	n,m,i,j,k,best,bestj:longint;
	a:array[1..maxm] of longint;
	p1,p2:array[1..maxm,1..maxn] of longint;
	c,b,len,from:array [1..maxn,1..maxm] of longint;
procedure _out(i,j:longint);
var
	k:longint;
begin
	if i=0 then exit;
	_out(i-len[i][j],from[i-len[i][j]+1][j]);
	for k:=1 to len[i][j] do write(j,' ');
end;
begin
 	reset(input,'input.txt');
 	rewrite(output,'output.txt');
	read(n,m);
	for i:=1 to m do read(a[i]);
	for i:=1 to m do
		for j:= 1 to n do read(c[j][i]);
	for i:=1 to m do begin
		p1[i][1]:=c[1][i];
		b[1][i]:=c[1][i];
		len[1][i]:=1;
	end;
	for i:=2 to n do begin
		for j:=1 to m do begin
			p2[j][1]:=maxlongint;
			for k:=1 to m do if k<>j then begin
			   	if b[i-1][k]+c[i][j]<p2[j][1] then begin
			   		p2[j][1]:=b[i-1][k]+c[i][j];
			  		from[i][j]:=k;
			  	end;
			end;
			b[i][j]:=p2[j][1];
			len[i][j]:=1;
 			for k:=2 to min(a[j],i) do begin
				p2[j][k]:=p1[j][k-1]+c[i][j];
				if p2[j][k]<b[i][j] then begin
					b[i][j]:=p2[j][k];
					len[i][j]:=k;
				end;
			end;
		end;
    	p1:=p2;
	end;
	best:=maxlongint;
	bestj:=0;
	for j:=1 to m do
		if b[n][j]<best then begin
			best:=b[n][j];
			bestj:=j;
		end;
	writeln(best);
	_out(n,bestj);
end.