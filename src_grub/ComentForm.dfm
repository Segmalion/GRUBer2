object FormComent: TFormComent
  Left = 0
  Top = 0
  Margins.Left = 5
  Margins.Top = 5
  Margins.Right = 5
  Margins.Bottom = 5
  BorderIcons = [biSystemMenu, biMaximize]
  Caption = #1050#1086#1084#1077#1085#1090#1072#1088
  ClientHeight = 894
  ClientWidth = 672
  Color = clBtnFace
  Constraints.MinHeight = 550
  Constraints.MinWidth = 400
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -21
  Font.Name = 'Segoe UI'
  Font.Style = []
  FormStyle = fsStayOnTop
  Position = poOwnerFormCenter
  OnClose = FormClose
  PixelsPerInch = 168
  TextHeight = 30
  object GridPanel1: TGridPanel
    Left = 0
    Top = 0
    Width = 672
    Height = 894
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
        Control = EditComent
        Row = 0
      end>
    RowCollection = <
      item
        Value = 100.000000000000000000
      end>
    TabOrder = 0
    object EditComent: TMemo
      AlignWithMargins = True
      Left = 5
      Top = 5
      Width = 666
      Height = 859
      Margins.Left = 5
      Margins.Top = 5
      Margins.Right = 5
      Margins.Bottom = 5
      Align = alClient
      Lines.Strings = (
        'EditComent')
      ScrollBars = ssBoth
      TabOrder = 0
    end
  end
end
