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
  ClientHeight = 215
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
    AlignWithMargins = True
    Left = 20
    Top = 5
    Width = 550
    Height = 205
    Margins.Left = 20
    Margins.Top = 5
    Margins.Right = 20
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
        ColumnSpan = 2
        Control = ButtonOK
        Row = 2
      end>
    RowCollection = <
      item
        SizeStyle = ssAbsolute
        Value = 80.000000000000000000
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
    ExplicitLeft = 0
    ExplicitTop = 0
    ExplicitWidth = 590
    ExplicitHeight = 260
    object LabelPrompt: TLabel
      AlignWithMargins = True
      Left = 5
      Top = 5
      Width = 540
      Height = 70
      Margins.Left = 5
      Margins.Top = 5
      Margins.Right = 5
      Margins.Bottom = 5
      Align = alClient
      Alignment = taCenter
      Caption = 'LabelPrompt'
      WordWrap = True
      ExplicitWidth = 117
      ExplicitHeight = 30
    end
    object ComboBoxPick: TComboBox
      AlignWithMargins = True
      Left = 5
      Top = 85
      Width = 540
      Height = 38
      Margins.Left = 5
      Margins.Top = 5
      Margins.Right = 5
      Margins.Bottom = 5
      Align = alClient
      Style = csDropDownList
      TabOrder = 0
      ExplicitTop = 142
      ExplicitWidth = 580
    end
    object ButtonOK: TButton
      AlignWithMargins = True
      Left = 5
      Top = 130
      Width = 540
      Height = 68
      Margins.Left = 5
      Margins.Top = 5
      Margins.Right = 5
      Margins.Bottom = 5
      Align = alClient
      Caption = #1054#1073#1088#1072#1090#1080
      ModalResult = 1
      TabOrder = 1
      ExplicitTop = 187
      ExplicitWidth = 580
    end
  end
end
