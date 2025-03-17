object FormDirExist: TFormDirExist
  Left = 0
  Top = 0
  Margins.Left = 5
  Margins.Top = 5
  Margins.Right = 5
  Margins.Bottom = 5
  BorderIcons = []
  BorderStyle = bsDialog
  Caption = 'GRUBer'
  ClientHeight = 163
  ClientWidth = 667
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -21
  Font.Name = 'Segoe UI'
  Font.Style = []
  FormStyle = fsStayOnTop
  Position = poMainFormCenter
  PixelsPerInch = 168
  TextHeight = 30
  object GridPanel1: TGridPanel
    Left = 0
    Top = 0
    Width = 667
    Height = 163
    Margins.Left = 5
    Margins.Top = 5
    Margins.Right = 5
    Margins.Bottom = 5
    Align = alClient
    BevelOuter = bvNone
    ColumnCollection = <
      item
        Value = 100.000000000000000000
      end>
    ControlCollection = <
      item
        Column = 0
        Control = Label1
        Row = 1
      end
      item
        Column = 0
        Control = ShowDir
        Row = 0
      end
      item
        Column = 0
        Control = GridPanel2
        Row = 2
      end>
    RowCollection = <
      item
        SizeStyle = ssAbsolute
        Value = 61.000000000000000000
      end
      item
        SizeStyle = ssAbsolute
        Value = 44.000000000000000000
      end
      item
        Value = 100.000000000000000000
      end>
    TabOrder = 0
    DesignSize = (
      667
      163)
    object Label1: TLabel
      Left = 149
      Top = 68
      Width = 368
      Height = 30
      Margins.Left = 5
      Margins.Top = 5
      Margins.Right = 5
      Margins.Bottom = 5
      Anchors = []
      Caption = #1044#1072#1085#1072' '#1090#1077#1082#1072' '#1074#1078#1077' '#1110#1089#1085#1091#1077'!!! '#1055#1077#1088#1077#1079#1072#1087#1080#1089#1072#1090#1080'? '
      ExplicitLeft = 154
      ExplicitTop = 70
    end
    object ShowDir: TEdit
      Left = 62
      Top = 11
      Width = 543
      Height = 38
      Margins.Left = 5
      Margins.Top = 5
      Margins.Right = 5
      Margins.Bottom = 5
      Alignment = taCenter
      Anchors = [akLeft, akTop, akRight, akBottom]
      Enabled = False
      ReadOnly = True
      TabOrder = 0
      Text = 'ShowDir'
    end
    object GridPanel2: TGridPanel
      Left = 0
      Top = 105
      Width = 667
      Height = 58
      Margins.Left = 5
      Margins.Top = 5
      Margins.Right = 5
      Margins.Bottom = 5
      Align = alClient
      BevelOuter = bvNone
      ColumnCollection = <
        item
          Value = 33.391688719083700000
        end
        item
          Value = 33.391688719083700000
        end
        item
          Value = 33.216622561832620000
        end>
      ControlCollection = <
        item
          Column = 0
          Control = ButtonCancel
          Row = 0
        end
        item
          Column = 1
          Control = ButtonOpen
          Row = 0
        end
        item
          Column = 2
          Control = ButtonOK
          Row = 0
        end>
      RowCollection = <
        item
          Value = 100.000000000000000000
        end>
      TabOrder = 1
      DesignSize = (
        667
        58)
      object ButtonCancel: TButton
        Left = 6
        Top = 7
        Width = 210
        Height = 44
        Margins.Left = 5
        Margins.Top = 5
        Margins.Right = 5
        Margins.Bottom = 5
        Anchors = []
        Caption = #1042#1110#1076#1084#1110#1085#1072
        TabOrder = 0
        OnClick = ButtonCancelClick
        ExplicitLeft = 5
      end
      object ButtonOpen: TButton
        Left = 229
        Top = 7
        Width = 210
        Height = 44
        Margins.Left = 5
        Margins.Top = 5
        Margins.Right = 5
        Margins.Bottom = 5
        Anchors = []
        Caption = #1042#1110#1076#1082#1088#1080#1090#1080' '#1090#1077#1082#1091
        Enabled = False
        TabOrder = 1
        ExplicitLeft = 228
      end
      object ButtonOK: TButton
        Left = 451
        Top = 7
        Width = 210
        Height = 44
        Margins.Left = 5
        Margins.Top = 5
        Margins.Right = 5
        Margins.Bottom = 5
        Anchors = []
        Caption = #1055#1077#1088#1077#1079#1072#1087#1080#1089#1072#1090#1080
        TabOrder = 2
        OnClick = ButtonOKClick
        ExplicitLeft = 450
      end
    end
  end
end
