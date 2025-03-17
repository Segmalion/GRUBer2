object FormPartition: TFormPartition
  Left = 0
  Top = 0
  Margins.Left = 5
  Margins.Top = 5
  Margins.Right = 5
  Margins.Bottom = 5
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = #1055#1110#1076#1088#1086#1079#1076#1110#1083#1080
  ClientHeight = 833
  ClientWidth = 590
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -21
  Font.Name = 'Segoe UI'
  Font.Style = []
  FormStyle = fsStayOnTop
  Position = poOwnerFormCenter
  PixelsPerInch = 168
  TextHeight = 30
  object GridPanel1: TGridPanel
    Left = 0
    Top = 0
    Width = 590
    Height = 833
    Margins.Left = 5
    Margins.Top = 5
    Margins.Right = 5
    Margins.Bottom = 5
    Align = alClient
    BevelOuter = bvNone
    ColumnCollection = <
      item
        Value = 50.000000000000000000
      end
      item
        Value = 50.000000000000000000
      end>
    ControlCollection = <
      item
        Column = 0
        ColumnSpan = 2
        Control = EditPartition
        Row = 0
      end
      item
        Column = 0
        Control = ButtonCancel
        Row = 1
      end
      item
        Column = 1
        Control = ButtonSave
        Row = 1
      end>
    RowCollection = <
      item
        Value = 100.000000000000000000
      end
      item
        SizeStyle = ssAbsolute
        Value = 88.000000000000000000
      end>
    TabOrder = 0
    object EditPartition: TMemo
      AlignWithMargins = True
      Left = 5
      Top = 5
      Width = 572
      Height = 710
      Margins.Left = 5
      Margins.Top = 5
      Margins.Right = 5
      Margins.Bottom = 5
      Align = alClient
      Lines.Strings = (
        'EditPartition')
      ScrollBars = ssBoth
      TabOrder = 0
    end
    object ButtonCancel: TButton
      AlignWithMargins = True
      Left = 5
      Top = 725
      Width = 281
      Height = 78
      Margins.Left = 5
      Margins.Top = 5
      Margins.Right = 5
      Margins.Bottom = 5
      Align = alClient
      Caption = #1042#1110#1076#1084#1110#1085#1080#1090#1080
      TabOrder = 1
      OnClick = ButtonCancelClick
      ExplicitTop = 751
      ExplicitWidth = 284
      ExplicitHeight = 77
    end
    object ButtonSave: TButton
      AlignWithMargins = True
      Left = 296
      Top = 725
      Width = 281
      Height = 78
      Margins.Left = 5
      Margins.Top = 5
      Margins.Right = 5
      Margins.Bottom = 5
      Align = alClient
      Caption = #1047#1073#1077#1088#1077#1075#1090#1080
      TabOrder = 2
      OnClick = ButtonSaveClick
      ExplicitLeft = 299
      ExplicitTop = 751
      ExplicitWidth = 286
      ExplicitHeight = 77
    end
  end
end
