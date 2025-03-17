object FormDirExist: TFormDirExist
  Left = 0
  Top = 0
  BorderIcons = []
  BorderStyle = bsDialog
  Caption = 'GRUBer'
  ClientHeight = 93
  ClientWidth = 381
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  FormStyle = fsStayOnTop
  Position = poMainFormCenter
  TextHeight = 15
  object GridPanel1: TGridPanel
    Left = 0
    Top = 0
    Width = 381
    Height = 93
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
        Value = 35.000000000000000000
      end
      item
        SizeStyle = ssAbsolute
        Value = 25.000000000000000000
      end
      item
        Value = 100.000000000000000000
      end>
    TabOrder = 0
    ExplicitLeft = 240
    ExplicitTop = 72
    ExplicitWidth = 185
    ExplicitHeight = 41
    DesignSize = (
      381
      93)
    object Label1: TLabel
      Left = 88
      Top = 40
      Width = 205
      Height = 15
      Anchors = []
      Caption = #1044#1072#1085#1072' '#1090#1077#1082#1072' '#1074#1078#1077' '#1110#1089#1085#1091#1077'!!! '#1055#1077#1088#1077#1079#1072#1087#1080#1089#1072#1090#1080'? '
      ExplicitLeft = 105
      ExplicitTop = 15
    end
    object ShowDir: TEdit
      Left = 35
      Top = 6
      Width = 310
      Height = 23
      Alignment = taCenter
      Anchors = [akLeft, akTop, akRight, akBottom]
      Enabled = False
      ReadOnly = True
      TabOrder = 0
      Text = 'ShowDir'
    end
    object GridPanel2: TGridPanel
      Left = 0
      Top = 60
      Width = 381
      Height = 33
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
      ExplicitLeft = 184
      ExplicitTop = 176
      ExplicitWidth = 185
      ExplicitHeight = 41
      DesignSize = (
        381
        33)
      object ButtonCancel: TButton
        Left = 3
        Top = 4
        Width = 120
        Height = 25
        Anchors = []
        Caption = #1042#1110#1076#1084#1110#1085#1072
        TabOrder = 0
        OnClick = ButtonCancelClick
        ExplicitLeft = 57
        ExplicitTop = 90
      end
      object ButtonOpen: TButton
        Left = 130
        Top = 4
        Width = 120
        Height = 25
        Anchors = []
        Caption = #1042#1110#1076#1082#1088#1080#1090#1080' '#1090#1077#1082#1091
        Enabled = False
        TabOrder = 1
        ExplicitLeft = 246
        ExplicitTop = 90
      end
      object ButtonOK: TButton
        Left = 257
        Top = 4
        Width = 120
        Height = 25
        Anchors = []
        Caption = #1055#1077#1088#1077#1079#1072#1087#1080#1089#1072#1090#1080
        TabOrder = 2
        OnClick = ButtonOKClick
        ExplicitLeft = 434
        ExplicitTop = 90
      end
    end
  end
end
