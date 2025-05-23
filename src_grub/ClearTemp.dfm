object FormClearTempDir: TFormClearTempDir
  Left = 0
  Top = 0
  Margins.Left = 5
  Margins.Top = 5
  Margins.Right = 5
  Margins.Bottom = 5
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'MicroClean'
  ClientHeight = 588
  ClientWidth = 636
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -21
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poOwnerFormCenter
  OnShow = FormShow
  PixelsPerInch = 168
  TextHeight = 30
  object Label2: TLabel
    Left = 10
    Top = 507
    Width = 179
    Height = 30
    Margins.Left = 5
    Margins.Top = 5
    Margins.Right = 5
    Margins.Bottom = 5
    Caption = #1047#1085#1072#1081#1076#1077#1085#1085#1086' '#1092#1072#1081#1083#1110#1074':'
  end
  object Label3: TLabel
    Left = 10
    Top = 547
    Width = 179
    Height = 30
    Margins.Left = 5
    Margins.Top = 5
    Margins.Right = 5
    Margins.Bottom = 5
    Caption = #1042#1080#1076#1072#1083#1077#1085#1085#1086' '#1092#1072#1081#1083#1110#1074':'
  end
  object Label4: TLabel
    Left = 221
    Top = 507
    Width = 60
    Height = 30
    Margins.Left = 5
    Margins.Top = 5
    Margins.Right = 5
    Margins.Bottom = 5
    Caption = 'Label4'
  end
  object Label5: TLabel
    Left = 221
    Top = 547
    Width = 60
    Height = 30
    Margins.Left = 5
    Margins.Top = 5
    Margins.Right = 5
    Margins.Bottom = 5
    Caption = 'Label5'
  end
  object Button_Clean: TButton
    Left = 322
    Top = 507
    Width = 304
    Height = 70
    Margins.Left = 5
    Margins.Top = 5
    Margins.Right = 5
    Margins.Bottom = 5
    Caption = #1054#1095#1080#1089#1090#1080#1090#1080' '#1090#1080#1084#1095#1072#1089#1086#1074#1110' '#1092#1072#1081#1083#1080
    TabOrder = 0
    OnClick = Button_CleanClick
  end
  object Memo_LOG: TMemo
    Left = 10
    Top = 10
    Width = 616
    Height = 487
    Margins.Left = 5
    Margins.Top = 5
    Margins.Right = 5
    Margins.Bottom = 5
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -21
    Font.Name = 'Consolas'
    Font.Style = []
    ParentFont = False
    ReadOnly = True
    ScrollBars = ssVertical
    TabOrder = 1
    WordWrap = False
  end
end
