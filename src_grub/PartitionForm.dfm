object FormPartition: TFormPartition
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = #1055#1110#1076#1088#1086#1079#1076#1110#1083#1080
  ClientHeight = 476
  ClientWidth = 337
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  FormStyle = fsStayOnTop
  Position = poOwnerFormCenter
  TextHeight = 15
  object GridPanel1: TGridPanel
    Left = 0
    Top = 0
    Width = 337
    Height = 476
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
        Value = 50.000000000000000000
      end>
    TabOrder = 0
    ExplicitWidth = 624
    ExplicitHeight = 441
    object EditPartition: TMemo
      AlignWithMargins = True
      Left = 3
      Top = 3
      Width = 331
      Height = 420
      Align = alClient
      Lines.Strings = (
        'EditPartition')
      ScrollBars = ssBoth
      TabOrder = 0
      ExplicitWidth = 618
      ExplicitHeight = 385
    end
    object ButtonCancel: TButton
      AlignWithMargins = True
      Left = 3
      Top = 429
      Width = 162
      Height = 44
      Align = alClient
      Caption = #1042#1110#1076#1084#1110#1085#1080#1090#1080
      TabOrder = 1
      OnClick = ButtonCancelClick
      ExplicitWidth = 142
    end
    object ButtonSave: TButton
      AlignWithMargins = True
      Left = 171
      Top = 429
      Width = 163
      Height = 44
      Align = alClient
      Caption = #1047#1073#1077#1088#1077#1075#1090#1080
      TabOrder = 2
      OnClick = ButtonSaveClick
      ExplicitLeft = 315
      ExplicitTop = 394
      ExplicitWidth = 306
    end
  end
end
