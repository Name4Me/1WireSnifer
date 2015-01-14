object Form9: TForm9
  Left = 0
  Top = 0
  Caption = '1Wire'
  ClientHeight = 432
  ClientWidth = 847
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  DesignSize = (
    847
    432)
  PixelsPerInch = 96
  TextHeight = 13
  object Button2: TButton
    Left = 159
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Open Com'
    TabOrder = 0
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 240
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Close Com'
    TabOrder = 1
    OnClick = Button3Click
  end
  object ComboBox1: TComboBox
    Left = 8
    Top = 8
    Width = 145
    Height = 21
    TabOrder = 2
  end
  object Button6: TButton
    Left = 460
    Top = 53
    Width = 75
    Height = 25
    Anchors = [akTop, akRight]
    Caption = 'Clear'
    TabOrder = 3
    OnClick = Button6Click
  end
  object GroupBox1: TGroupBox
    Left = 541
    Top = 8
    Width = 298
    Height = 97
    Anchors = [akTop, akRight]
    Caption = 'ROM CMD'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlue
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    Padding.Left = 10
    Padding.Top = 20
    Padding.Right = 10
    Padding.Bottom = 10
    ParentFont = False
    TabOrder = 4
    object Button1: TButton
      Left = 13
      Top = 23
      Width = 75
      Height = 25
      Caption = 'READ ROM'
      TabOrder = 0
      OnClick = Button1Click
    end
    object Button10: TButton
      Left = 13
      Top = 54
      Width = 75
      Height = 25
      Caption = 'SEARCH ROM'
      TabOrder = 1
      OnClick = Button1Click
    end
    object Button11: TButton
      Left = 94
      Top = 23
      Width = 75
      Height = 25
      Caption = 'MATCH ROM'
      TabOrder = 2
      OnClick = Button1Click
    end
    object Button12: TButton
      Left = 94
      Top = 54
      Width = 75
      Height = 25
      Caption = 'SKIP ROM'
      TabOrder = 3
      OnClick = Button1Click
    end
    object Button8: TButton
      Left = 210
      Top = 23
      Width = 75
      Height = 25
      Caption = 'RESET'
      TabOrder = 4
      OnClick = Button1Click
    end
    object Button7: TButton
      Left = 210
      Top = 54
      Width = 75
      Height = 25
      Caption = 'WRITE ROM'
      TabOrder = 5
      OnClick = Button1Click
    end
  end
  object GroupBox2: TGroupBox
    Left = 541
    Top = 111
    Width = 298
    Height = 154
    Anchors = [akTop, akRight]
    Caption = 'RAM CMD'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlue
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    Padding.Left = 10
    Padding.Top = 20
    Padding.Right = 10
    Padding.Bottom = 10
    ParentFont = False
    TabOrder = 5
    object Button4: TButton
      Left = 13
      Top = 23
      Width = 132
      Height = 25
      Caption = 'WRITE SCRATCHPAD'
      TabOrder = 0
      OnClick = Button1Click
    end
    object Button5: TButton
      Left = 13
      Top = 54
      Width = 132
      Height = 25
      Caption = 'READ SCRATCHPAD'
      TabOrder = 1
      OnClick = Button1Click
    end
    object Button9: TButton
      Left = 13
      Top = 85
      Width = 132
      Height = 25
      Caption = 'COPY SCRATCHPAD'
      TabOrder = 2
      OnClick = Button1Click
    end
    object Button13: TButton
      Left = 13
      Top = 116
      Width = 132
      Height = 25
      Caption = 'READ MEMORY'
      TabOrder = 3
      OnClick = Button1Click
    end
    object Button14: TButton
      Left = 151
      Top = 23
      Width = 132
      Height = 25
      Caption = 'READ STATUS'
      TabOrder = 4
      OnClick = Button1Click
    end
    object Button15: TButton
      Left = 151
      Top = 54
      Width = 132
      Height = 25
      Caption = 'WRITE AP_REG'
      TabOrder = 5
      OnClick = Button1Click
    end
    object Button16: TButton
      Left = 151
      Top = 85
      Width = 132
      Height = 25
      Caption = 'READ AP_REG'
      TabOrder = 6
      OnClick = Button1Click
    end
    object Button17: TButton
      Left = 151
      Top = 116
      Width = 132
      Height = 25
      Caption = 'COPY AP_REG'
      TabOrder = 7
      OnClick = Button1Click
    end
  end
  object LabeledEdit1: TLabeledEdit
    Left = 8
    Top = 48
    Width = 145
    Height = 21
    EditLabel.Width = 23
    EditLabel.Height = 13
    EditLabel.Caption = 'ROM'
    TabOrder = 6
    OnDragDrop = LabeledEdit1DragDrop
    OnDragOver = LabeledEdit1DragOver
  end
  object LabeledEdit2: TLabeledEdit
    Left = 159
    Top = 48
    Width = 145
    Height = 21
    EditLabel.Width = 20
    EditLabel.Height = 13
    EditLabel.Caption = 'APR'
    TabOrder = 7
    OnDragDrop = LabeledEdit1DragDrop
    OnDragOver = LabeledEdit1DragOver
  end
  object LabeledEdit3: TLabeledEdit
    Left = 8
    Top = 84
    Width = 527
    Height = 21
    Anchors = [akLeft, akTop, akRight]
    EditLabel.Width = 22
    EditLabel.Height = 13
    EditLabel.Caption = 'RAM'
    TabOrder = 8
    OnDragDrop = LabeledEdit1DragDrop
    OnDragOver = LabeledEdit1DragOver
  end
end
