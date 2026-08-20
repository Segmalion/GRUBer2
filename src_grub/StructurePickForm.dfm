object FormStructurePick: TFormStructurePick
  Left = 0
  Top = 0
  Margins.Left = 5
  Margins.Top = 5
  Margins.Right = 5
  Margins.Bottom = 5
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = #1042#1080#1073#1110#1088' '#1089#1090#1088#1091#1082#1090#1091#1088#1080
  ClientHeight = 260
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
    Height = 260
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
        Control = LabelPrompt
        Row = 0
      end
      item
        Column = 0
        ColumnSpan = 2
        Control = ComboBoxPick
        Row = 1
      end
      item
        Column = 0
        Control = ButtonCancel
        Row = 2
      end
      item
        Column = 1
        Control = ButtonOK
        Row = 2
      end>
    RowCollection = <
      item
        SizeStyle = ssAbsolute
        Value = 137.000000000000000000
      end
      item
        SizeStyle = ssAbsolute
        Value = 45.000000000000000000
      end
      item
        SizeStyle = ssAbsolute
        Value = 78.000000000000000000
      end>
    TabOrder = 0
    object LabelPrompt: TLabel
      AlignWithMargins = True
      Left = 5
      Top = 5
      Width = 580
      Height = 127
      Margins.Left = 5
      Margins.Top = 5
      Margins.Right = 5
      Margins.Bottom = 5
      Align = alClient
      Caption = 'LabelPrompt'
      WordWrap = True
    end
    object ComboBoxPick: TComboBox
      AlignWithMargins = True
      Left = 5
      Top = 142
      Width = 580
      Height = 35
      Margins.Left = 5
      Margins.Top = 5
      Margins.Right = 5
      Margins.Bottom = 5
      Align = alClient
      Style = csDropDownList
      TabOrder = 0
    end
    object ButtonCancel: TButton
      AlignWithMargins = True
      Left = 5
      Top = 192
      Width = 281
      Height = 68
      Margins.Left = 5
      Margins.Top = 5
      Margins.Right = 5
      Margins.Bottom = 5
      Align = alClient
      Caption = #1042#1110#1076#1084#1110#1085#1072
      ModalResult = 2
      TabOrder = 1
    end
    object ButtonOK: TButton
      AlignWithMargins = True
      Left = 296
      Top = 192
      Width = 289
      Height = 68
      Margins.Left = 5
      Margins.Top = 5
      Margins.Right = 5
      Margins.Bottom = 5
      Align = alClient
      Caption = #1054#1073#1088#1072#1090#1080
      ModalResult = 1
      TabOrder = 2
    end
  end
end
