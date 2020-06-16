{$apptype console}
Const
  MaxSize=101;
  MaxK=101;
Type
  TDir=(_Left,_Right,_Up,_Down);
  TPosition=Record Y,X:LongInt; End;
Const
  DirChar:Array[TDir]Of Char='WENS';
  DirDY:Array[TDir]Of LongInt=(0,0,-1,1);
  DirDX:Array[TDir]Of LongInt=(-1,1,0,0);
  Opposite:Array[TDir]Of TDir=(_Right,_Left,_Down,_Up);
  SaveChar='D';
Var
  Height,Width,K,ResTime:LongInt;
  Lab:Array[0..MaxSize+1,0..MaxSize+1]Of Boolean;
  Soldier,Saving:Array[1..MaxK]Of TPosition;
  Len:Array[1..MaxK,1..MaxK]Of LongInt;
  How:Array[1..MaxK,1..MaxSize,1..MaxSize]Of TDir;
  WFrHead,WFrTail:LongInt;
  Got:Array[1..MaxSize,1..MaxSize]Of LongInt;
  WFront:Array[0..MaxSize*MaxSize]Of TPosition;
  IsSol:Boolean;
  SolState,SolPair,SavPair:Array[1..MaxK]Of LongInt;
  PFront:Array[0..MaxK]Of LongInt;
  PFrHead,PFrTail:LongInt;
  Prev:Array[0..MaxK]Of LongInt;
Procedure _In;
Var
  I,J,A:LongInt;
Begin
  FillChar(Lab,SizeOf(Lab),False);
  ReSet(Input,'input.txt');
  Read(Width,Height);
  K:=0;
  For I:=1 To Height Do
    For J:=1 To Width Do Begin
      Read(A);
      Case A Of
        0:Lab[I][J]:=True;
        1:Lab[I][J]:=False;
        2:Begin
          Lab[I][J]:=True;
          Inc(K);
          Saving[K].Y:=I;
          Saving[K].X:=J;
        End;
      End;
    End;
  For I:=1 To K Do
    Read(Soldier[I].X,Soldier[I].Y);
End;
Procedure FillWays;
Var
  SIndex,I,J:LongInt;
  Cur,Next:TPosition;
  CDir:TDir;
Begin
  For SIndex:=1 To K Do Begin
    For I:=1 To Height Do
      For J:=1 To Width Do
        Got[I][J]:=-1;
    WFrHead:=1;
    WFrTail:=0;
    WFront[0]:=Saving[SIndex];
    Got[WFront[0].Y,WFront[0].X]:=0;
    While WFrTail<WFrHead Do Begin
      Cur:=WFront[WFrTail];
      Inc(WFrTail);
      For CDir:=Low(CDir) To High(CDir) Do Begin
        Next.X:=Cur.X+DirDX[CDir];
        Next.Y:=Cur.Y+DirDY[CDir];
        If Lab[Next.Y,Next.X] And (Got[Next.Y,Next.X]<0) Then Begin
          Got[Next.Y,Next.X]:=Got[Cur.Y,Cur.X]+1;
          WFront[WFrHead]:=Next;
          Inc(WFrHead);
          How[SIndex,Next.Y,Next.X]:=Opposite[CDir];
        End;
      End;
    End;
    For I:=1 To K Do
      Len[I][SIndex]:=Got[Soldier[I].Y,Soldier[I].X];
  End;
End;
Function FindPairs(MaxLen:LongInt):Boolean;
Var
  I,J,JJ,Cur,CSav,NSav:LongInt;
  Found:Boolean;
Begin
  FillChar(SavPair,SizeOf(SavPair),0);
  JJ:=1;
  Cur:=1;
  For I:=1 To K Do Begin
    SolPair[I]:=0;
    FillChar(Prev,SizeOf(Prev),0);
    PFrHead:=1;
    PFrTail:=0;
    PFront[0]:=I;
    Prev[I]:=I;
    Found:=False;
    While (PFrTail<PFrHead) And Not Found Do Begin
      Cur:=PFront[PFrTail];
      Inc(PFrTail);
      For J:=1 To K Do If (Len[Cur][J]>=0) And (Len[Cur][J]<=MaxLen) Then
        If SavPair[J]=0 Then Begin
          Found:=True;
          JJ:=J;
          Break;
        End Else If Prev[SavPair[J]]=0 Then Begin
          Prev[SavPair[J]]:=Cur;
          PFront[PFrHead]:=SavPair[J];
          Inc(PFrHead);
        End;
    End;
    If Not Found Then Begin
      FindPairs:=False;
      Exit;
    End;
    CSav:=JJ;
    Repeat
      NSav:=SolPair[Cur];
      SolPair[Cur]:=CSav;
      SavPair[CSav]:=Cur;
      Cur:=Prev[Cur];
      CSav:=NSav;
    Until CSav=0;
  End;
  FindPairs:=True;
End;
Procedure Solve;
Var
  I,J,Min,Max,Middle:LongInt;
Begin
  IsSol:=False;
  FillWays;
  Min:=MaxLongInt;
  Max:=-MaxLongInt;
  For I:=1 To K Do
    For J:=1 To K Do
      If Len[I][J]>=0 Then Begin
        If Len[I][J]>Max Then Max:=Len[I][J];
        If Len[I][J]<Min Then Min:=Len[I][J];
      End;
  If Min=MaxLongInt Then Exit;
  If Not FindPairs(Max) Then Exit;
  Dec(Min);
  While Max-Min>1 Do Begin
    Middle:=(Min+Max) Div 2;
    If FindPairs(Middle) Then
      Max:=Middle
    Else
      Min:=Middle;
  End;
  IsSol:=True;
  ResTime:=Max+3;
  FindPairs(Max);
End;
Procedure _Out;
Var
  I,J:LongInt;
  First:Boolean;
  Dir:TDir;
Begin
  ReWrite(Output,'output.txt');
  If IsSol Then Begin
    WriteLn(ResTime);
    FillChar(SolState,SizeOf(SolState),0);
    For I:=1 To ResTime Do Begin
      First:=True;
      For J:=1 To K Do
        If (SolState[J]=0) And ((Soldier[J].X<>Saving[SolPair[J]].X) Or
           (Soldier[J].Y<>Saving[SolPair[J]].Y)) Then Begin
          If First Then First:=False Else Write(' ');
          Dir:=How[SolPair[J],Soldier[J].Y,Soldier[J].X];
          Write(J,' ',DirChar[Dir]);
          Soldier[J].Y:=Soldier[J].Y+DirDY[Dir];
          Soldier[J].X:=Soldier[J].X+DirDX[Dir];
        End Else Begin
          If SolState[J]<3 Then Begin
            If First Then First:=False Else Write(' ');
            Write(J,' ',SaveChar);
            Inc(SolState[J]);
          End;
        End;
      WriteLn;
    End;
  End Else WriteLn('0');
End;
Begin
  _In;
  Solve;
  _Out;
End.