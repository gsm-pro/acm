{$APPTYPE CONSOLE}
Const
  MaxL=301;
  MaxR=301;
Var
  NL,NR,I,Num,J,A,Amount,NRes,P,Q:LongInt;
  OutL:Array[1..MaxL,1..MaxR]Of LongInt;
  ML,MR,Prev,Res,NOutL:Array[1..MaxL]Of LongInt;
  Queue:Array[0..MaxL]Of LongInt;
Procedure TryImproving(NumL:LongInt);
Var
  Cur,I,A,B:LongInt;
Label Lab;
Begin
  FillChar(Prev,SizeOf(Prev),0);
  If NumL=0 Then Begin
    P:=0;
    Q:=0;
    For I:=1 To NL Do If ML[I]=0 Then Begin
      Queue[P]:=I;
      Prev[I]:=I;
      Inc(P);
    End;
  End Else Begin
    P:=1;
    Q:=0;
    Queue[0]:=NumL;
    Prev[NumL]:=NumL;
  End;
  Cur:=0;
  A:=0;
  While Q<P Do Begin
    Cur:=Queue[Q];
    Inc(Q);
    For I:=1 To NOutL[Cur] Do Begin
      A:=OutL[Cur,I];
      B:=MR[A];
      If B=0 Then Goto Lab;
      If Prev[B]=0 Then Begin
        Prev[B]:=Cur;
        Queue[P]:=B;
        Inc(P);
      End;
    End;
  End;
  Exit;
Lab:
  Repeat
    B:=ML[Cur];
    ML[Cur]:=A;
    MR[A]:=Cur;
    A:=B;
    Cur:=Prev[Cur];
  Until A=0;
  Inc(Amount);
End;
Procedure Solve;
Var
  I:LongInt;
Begin
  NRes:=0;
  Amount:=0;
  FillChar(ML,SizeOf(ML),0);
  FillChar(MR,SizeOf(MR),0);
  For I:=1 To NL Do
    TryImproving(I);
  TryImproving(0);
  NRes:=P;
  For I:=1 To NRes Do
    Res[I]:=Queue[I-1];
End;
Begin
  ReSet(Input,'input.txt');
  Read(NL,NR);
  For I:=1 To NL Do Begin
    Read(Num);
    For J:=1 To Num Do Begin
      Read(A);
      Inc(NOutL[I]);
      OutL[I,NOutL[I]]:=A;
    End;
  End;
  Solve();
  ReWrite(Output,'output.txt');
  WriteLn(NRes);
  For I:=1 To NRes Do Begin
    If I>1 Then Write(' ');
    Write(Res[I]);
  End;
End.