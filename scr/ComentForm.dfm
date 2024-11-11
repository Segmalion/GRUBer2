object FormComent: TFormComent
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = #1050#1086#1084#1077#1085#1090#1072#1088'...'
  ClientHeight = 441
  ClientWidth = 624
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
    Width = 624
    Height = 441
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
        Control = EditComent
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
    ExplicitLeft = 320
    ExplicitTop = 160
    ExplicitWidth = 185
    ExplicitHeight = 41
    object EditComent: TMemo
      AlignWithMargins = True
      Left = 3
      Top = 3
      Width = 618
      Height = 385
      Align = alClient
      Lines.Strings = (
        'EditComent')
      ScrollBars = ssBoth
      TabOrder = 0
    end
    object ButtonCancel: TButton
      AlignWithMargins = True
      Left = 3
      Top = 394
      Width = 306
      Height = 44
      Align = alClient
      Caption = #1042#1110#1076#1084#1110#1085#1080#1090#1080
      TabOrder = 1
      OnClick = ButtonCancelClick
      ExplicitLeft = 272
      ExplicitTop = 208
      ExplicitWidth = 75
      ExplicitHeight = 25
    end
    object ButtonSave: TButton
      AlignWithMargins = True
      Left = 315
      Top = 394
      Width = 306
      Height = 44
      Align = alClient
      Caption = #1047#1073#1077#1088#1077#1075#1090#1080
      TabOrder = 2
      OnClick = ButtonSaveClick
      ExplicitLeft = 272
      ExplicitTop = 208
      ExplicitWidth = 75
      ExplicitHeight = 25
    end
  end
end
