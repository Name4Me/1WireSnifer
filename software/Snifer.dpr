program Snifer;

uses
  Forms,
  ComPort in 'ComPort.pas' {Form9},
  uCommPort in 'uCommPort.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.MainFormOnTaskbar := True;
  Application.CreateForm(TForm9, Form9);
  Application.Run;
end.
