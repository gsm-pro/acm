{$APPTYPE CONSOLE}
var
  t,px,py,pz,vx,vy,vz,ux,uy,uz,u,d:double;
begin
  reset(input,'input.txt');
  rewrite(output,'output.txt');
  read(px,py,pz,vx,vy,vz,u);
  d:=4*(px*vx+py*vy+pz*vz)*(px*vx+py*vy+pz*vz)-
     4*(vx*vx+vy*vy+vz*vz-u*u)*(px*px+py*py+pz*pz);
  t:=(-2*(px*vx+py*vy+pz*vz)-sqrt(d))/(2*(vx*vx+vy*vy+vz*vz-u*u));
  ux:=px/t+vx;
  uy:=py/t+vy;
  uz:=pz/t+vz;
  write(ux:0:2,' ',uy:0:2,' ',uz:0:2);
end.