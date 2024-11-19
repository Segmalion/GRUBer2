object FormComent: TFormComent
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMaximize]
  Caption = #1050#1086#1084#1077#1085#1090#1072#1088
  ClientHeight = 511
  ClientWidth = 384
  Color = clBtnFace
  Constraints.MinHeight = 550
  Constraints.MinWidth = 400
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  FormStyle = fsStayOnTop
  Position = poOwnerFormCenter
  OnClose = FormClose
  TextHeight = 15
  object GridPanel1: TGridPanel
    Left = 0
    Top = 0
    Width = 384
    Height = 511
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
      end>
    RowCollection = <
      item
        Value = 100.000000000000000000
      end>
    TabOrder = 0
    ExplicitWidth = 624
    ExplicitHeight = 441
    object EditComent: TMemo
      AlignWithMargins = True
      Left = 3
      Top = 3
      Width = 378
      Height = 505
      Align = alClient
      Lines.Strings = (
        'EditComent')
      ScrollBars = ssBoth
      TabOrder = 0
      ExplicitWidth = 618
      ExplicitHeight = 385
    end
  end
end
