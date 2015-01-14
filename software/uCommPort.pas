unit uCommPort;



interface
Uses Windows,dialogs,SysUtils,Classes,StrUtils;
type
  //определим тип TComThread - наследника класса TThread
  TCommThread = class(TThread)
  private
    //процедура, занимающаяся опросом порта
    procedure QueryPort;
  protected
    //переопределим метод запуска потока
    procedure Execute; override;
  end;
  procedure PortInit;
  function  ScanComPort:String;
  procedure CloseComm;
  procedure StartComThread;
  Var
    RxBuf: array[0..255] of Byte;
    BufLen:integer;
    RxString:string;
    hPort: THandle;
    ComName:string;
    busi:boolean=false;
    Ready:boolean=false;
    CommThread:TCommThread;
    RXC:boolean=false;
implementation

Uses ComPort;




procedure PortInit;
  var
    ct: TCommTimeouts;
    dcb: TDCB;
begin
   //ShowMessage('PortInit'+inttostr(com));
   if not Ready and (not busi) and (hPort=0) then Begin
   busi:=True;
   hPort := CreateFile(PChar(ComName),GENERIC_READ or GENERIC_WRITE,
      FILE_SHARE_READ or FILE_SHARE_WRITE,nil, OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL, 0);    //FILE_ATTRIBUTE_NORMAL
   if hPort <> INVALID_HANDLE_VALUE then Ready:=True;
   SetupComm(hPort, 2048, 2048);
   GetCommState(hPort, dcb);
   dcb.BaudRate := CBR_19200;
   dcb.StopBits := 0;
   dcb.Parity := 0;
   dcb.ByteSize := 8;
   SetCommState(hPort, dcb);
   GetCommTimeouts(hPort, ct);
   ct.ReadTotalTimeoutConstant := 10;
   ct.ReadIntervalTimeout := 10;
   ct.ReadTotalTimeoutMultiplier := 1;
   ct.WriteTotalTimeoutMultiplier := 10;
   ct.WriteTotalTimeoutConstant := 10;
   SetCommTimeouts(hPort, ct);
   busi:=False;
   End;

end;
function  ScanComPort:String;{опрос существующих портов}
var
  hnd:THandle;
  i: integer;
begin
  for i := 0 to 31 do {цикл опроса}
  begin {пробуем получить дескриптор порта}
    hnd := CreateFile(PChar('COM' + IntToStr(i + 1)),
      GENERIC_READ,
      0,
      nil,
      OPEN_EXISTING, FILE_FLAG_OVERLAPPED, 0);
    if hnd <> INVALID_HANDLE_VALUE then {если порт есть то добавить в список}
      Result:=Result+('COM' + IntToStr(i + 1))+#13;
    CloseHandle(hnd); {закрыть дескриптор}
    end;
  end;






procedure CloseComm;
begin
  if hPort <> 0 then
    CloseHandle(hPort);
    hPort:=0;
end;

procedure StartComThread;
begin {StartComThread} //инициализация нашего потока
  CommThread := TCommThread.Create(False);  //пытаемся инициализировать поток
  if CommThread = nil then begin  {Nil}//проверяем получилось или нет
    SysErrorMessage(GetLastError);  //ошибка, все выключаем и выходим
    Exit;
    end;  {Nil}
  end; {StartComThread}

{ TCommThread }

procedure TCommThread.Execute;
begin
  //inherited;
  repeat
    QueryPort; //процедура опроса порта будет производиться пока поток не будет прекращен
  until Terminated;
end;

procedure TCommThread.QueryPort;
  var
    ComStat: TComStat;
    Buf : array[0..255] of Char;
    dwError,dwRead,i: DWord;
    position: Integer;
    tmp:string;
begin
  ClearCommError(hPort, dwError, @ComStat);
  //if not ClearCommError(hPort, dwError, @ComStat) then
  //  raise Exception.Create('Error clearing port');
  dwRead := ComStat.cbInQue;
  if dwRead>0 Then Begin
    ReadFile(hPort,Buf,SizeOf(Buf),dwRead,Nil);
    tmp:='';
    for i := 0 to dwRead-1 do Begin
      RxBuf[BufLen+i]:=Ord(Buf[i]);
      tmp:=tmp+IntToHex(ord(Buf[i]),2)+' ';
      End;
    //Form9.Memo1.Text:=Form9.Memo1.Text;
    Form9.Memo1.Text:=ReplaceStr(Form9.Memo1.Text+tmp,' 0D 0A',#13#10);
    BufLen:=dwRead;

    //Form9.Memo2.Lines.Add('Resive '+IntToStr(dwRead)+' Bytes >'+string(Buf));
    //Form9.Memo2.Lines.Add('Buffer '+IntToStr(BufLen)+' Bytes');
    End;
end;


end.
