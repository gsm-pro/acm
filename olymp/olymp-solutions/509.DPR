begin
  rewrite(output,'output.txt');
  write('struct begin'+#13#10+'{'+#13#10+'#define end ; int main() {'+#13#10+'}'+#13#10+'end.0;'+#13#10+'}');
end.