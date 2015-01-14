unit ComPort;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ExtCtrls, StdCtrls,  IniFiles,StrUtils, uMyMemo;

type
  TForm9 = class(TForm)
    Button1: TButton;
    Button2: TButton;
    Button3: TButton;
    ComboBox1: TComboBox;
    Button4: TButton;
    Button5: TButton;
    Button6: TButton;
    Button8: TButton;
    Button9: TButton;
    GroupBox1: TGroupBox;
    GroupBox2: TGroupBox;
    Button10: TButton;
    Button11: TButton;
    Button12: TButton;
    Button13: TButton;
    Button14: TButton;
    Button15: TButton;
    Button16: TButton;
    Button17: TButton;
    Button7: TButton;
    LabeledEdit1: TLabeledEdit;
    LabeledEdit2: TLabeledEdit;
    LabeledEdit3: TLabeledEdit;
    procedure FormCreate(Sender: TObject);

    procedure Button3Click(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure Button2Click(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure Button6Click(Sender: TObject);
    procedure Memo1DragOver(Sender, Source: TObject; X, Y: Integer;
      State: TDragState; var Accept: Boolean);
    procedure LabeledEdit1DragDrop(Sender, Source: TObject; X, Y: Integer);
    procedure LabeledEdit1DragOver(Sender, Source: TObject; X, Y: Integer;
      State: TDragState; var Accept: Boolean);
  private
    { Private declarations }
  public
    { Public declarations }
  end;
  
var
  Form9: TForm9;
  value:string;
  pck:string;
  MyIni:TIniFile;
implementation

{$R *.dfm}
Uses uCommPort;


procedure TForm9.Button1Click(Sender: TObject);
Var
   nChar:DWORD;
   sByte:Byte;
   s:string;
begin
  with sender as TButton do Begin
    if Caption = 'RESET' Then WriteFile(hPort,#13#10,2,nChar,nil);

    if Caption = 'READ ROM' Then WriteFile(hPort,#51#13#10,3,nChar,nil);            //0x33
    if Caption = 'MATCH ROM' Then WriteFile(hPort,#85#13#10,3,nChar,nil);           //0x55
    if Caption = 'SEARCH ROM' Then WriteFile(hPort,#240#13#10,3,nChar,nil);         //0xF0
    if Caption = 'SKIP ROM' Then WriteFile(hPort,#204#13#10,3,nChar,nil);           //0xCC
    if (Caption = 'WRITE ROM') and (LabeledEdit1.Text<>'') Then Begin               //0x34
      sByte:=52;
      WriteFile(hPort,sByte,1,nChar,nil);
      s:=ReplaceStr(LabeledEdit1.Text,' ','');
      while s<>'' do Begin
        sByte:=StrToInt('$'+Copy(s,1,2));
        WriteFile(hPort,sByte,1,nChar,nil);
        Delete(s,1,2);
        End;
      WriteFile(hPort,#13#10,2,nChar,nil);
      End;
    if (Caption = 'WRITE SCRATCHPAD') and (LabeledEdit3.Text<>'') Then Begin        //0x0F
      sByte:=15;
      WriteFile(hPort,sByte,1,nChar,nil);
      s:=ReplaceStr(LabeledEdit3.Text,' ','');
      while s<>'' do Begin
        sByte:=StrToInt('$'+Copy(s,1,2));
        WriteFile(hPort,sByte,1,nChar,nil);
        Delete(s,1,2);
        End;
      WriteFile(hPort,#13#10,2,nChar,nil);
      End;


    if Caption = 'READ SCRATCHPAD' Then WriteFile(hPort,#170#13#10,3,nChar,nil);    //0xAA
    if Caption = 'COPY SCRATCHPAD' Then WriteFile(hPort,#85#85#13#10,4,nChar,nil);  //0x55
    if Caption = 'READ MEMORY' Then WriteFile(hPort,#240#240#13#10,4,nChar,nil);    //0xF0
    if Caption = 'READ STATUS' Then WriteFile(hPort,#102#13#10,3,nChar,nil);        //0x66
    if (Caption = 'WRITE AP_REG') and (LabeledEdit2.Text<>'') Then Begin            //0x99
      sByte:=153;
      WriteFile(hPort,sByte,1,nChar,nil);
      s:=ReplaceStr(LabeledEdit2.Text,' ','');
      while s<>'' do Begin
        sByte:=StrToInt('$'+Copy(s,1,2));
        WriteFile(hPort,sByte,1,nChar,nil);
        Delete(s,1,2);
        End;
      WriteFile(hPort,#13#10,3,nChar,nil);
      End;


    if Caption = 'READ AP_REG' Then WriteFile(hPort,#195#13#10,3,nChar,nil);        //0xC3
    if Caption = 'COPY AP_REG' Then WriteFile(hPort,#90#13#10,3,nChar,nil);         //0x5A
  End;

end;

procedure TForm9.Button2Click(Sender: TObject);

begin
  PortInit;
  StartComThread;
  Button2.Enabled:=False;
end;

procedure TForm9.Button3Click(Sender: TObject);
begin
    if CommThread<>nil Then Begin
    CommThread.Terminate;
    CloseComm;
    End;
end;

procedure TForm9.Button6Click(Sender: TObject);
begin
  Memo1.Clear;
end;

procedure TForm9.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  if CommThread<>nil Then Begin
    CommThread.Terminate;
    CloseComm;
    End;
  MyIni.WriteString('Main','PortName',ComboBox1.Text);
  Memo1.Lines.SaveToFile('Data.txt');
  if MyIni<>nil then MyIni.Free;
end;

procedure TForm9.FormCreate(Sender: TObject);
Var
  PortName:String;
begin
  MyIni:= TIniFile.Create(GetCurrentDir+'\option.ini');
  PortName:=MyIni.ReadString('Main','PortName','Com1');
  Memo1.Lines.LoadFromFile('Data.txt');

  ComboBox1.Items.Text:=ScanComPort;
  if pos(PortName,ComboBox1.Items.Text)<>0 then
    ComName:=PortName;
  ComboBox1.Text:=ComName;

  Button2.Click;



end;

procedure TForm9.LabeledEdit1DragDrop(Sender, Source: TObject; X, Y: Integer);
begin
  (Sender as TLabeledEdit).Text:=(Source as TMyMemo).SelText;
end;

procedure TForm9.LabeledEdit1DragOver(Sender, Source: TObject; X, Y: Integer;
  State: TDragState; var Accept: Boolean);
begin
Accept := Source is TMyMemo;
end;

procedure TForm9.Memo1DragOver(Sender, Source: TObject; X, Y: Integer;
  State: TDragState; var Accept: Boolean);
begin
Accept := Source is TMyMemo;

end;





end.


