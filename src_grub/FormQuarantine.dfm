object FormQuarantine: TFormQuarantine
  Left = 0
  Top = 0
  Margins.Left = 5
  Margins.Top = 5
  Margins.Right = 5
  Margins.Bottom = 5
  BorderIcons = [biSystemMenu, biMaximize]
  Caption = #1050#1072#1088#1072#1085#1090#1080#1085' ESET'
  ClientHeight = 736
  ClientWidth = 1016
  Color = clBtnFace
  Constraints.MinHeight = 800
  Constraints.MinWidth = 1040
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -21
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poOwnerFormCenter
  PixelsPerInch = 168
  TextHeight = 30
  object GridPanel1: TGridPanel
    Left = 0
    Top = 0
    Width = 1016
    Height = 736
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
        Control = ListViewQuarantine
        Row = 0
      end
      item
        Column = 0
        Control = LabelInfo
        Row = 1
      end
      item
        Column = 0
        Control = GridPanel2
        Row = 2
      end>
    RowCollection = <
      item
        Value = 100.000000000000000000
      end
      item
        SizeStyle = ssAbsolute
        Value = 50.000000000000000000
      end
      item
        SizeStyle = ssAbsolute
        Value = 80.000000000000000000
      end>
    TabOrder = 0
    ExplicitWidth = 1050
    ExplicitHeight = 750
    object ListViewQuarantine: TListView
      AlignWithMargins = True
      Left = 5
      Top = 5
      Width = 1006
      Height = 596
      Margins.Left = 5
      Margins.Top = 5
      Margins.Right = 5
      Margins.Bottom = 5
      Align = alClient
      Checkboxes = True
      Columns = <
        item
          Caption = #1058#1077#1082#1072
          Width = 220
        end
        item
          Caption = #1053#1072#1079#1074#1072
          Width = 320
        end
        item
          Caption = #1044#1072#1090#1072' '#1089#1090#1074#1086#1088#1077#1085#1085#1103
          Width = 260
        end
        item
          Caption = #1056#1086#1079#1084#1110#1088
          Width = 140
        end>
      GridLines = True
      ReadOnly = True
      RowSelect = True
      TabOrder = 0
      ViewStyle = vsReport
      OnCustomDrawItem = ListViewQuarantineCustomDrawItem
      ExplicitWidth = 1040
      ExplicitHeight = 610
    end
    object LabelInfo: TLabel
      AlignWithMargins = True
      Left = 5
      Top = 606
      Width = 1006
      Height = 50
      Margins.Left = 5
      Margins.Top = 0
      Margins.Right = 5
      Margins.Bottom = 0
      Align = alClient
      Caption = #1047#1085#1072#1081#1076#1077#1085#1086' '#1092#1072#1081#1083#1110#1074': 0'
      ExplicitTop = 620
      ExplicitWidth = 184
      ExplicitHeight = 30
    end
    object GridPanel2: TGridPanel
      Left = 0
      Top = 656
      Width = 1016
      Height = 80
      Margins.Left = 5
      Margins.Top = 5
      Margins.Right = 5
      Margins.Bottom = 5
      Align = alClient
      BevelOuter = bvNone
      ColumnCollection = <
        item
          Value = 25.000000000000000000
        end
        item
          Value = 25.000000000000000000
        end
        item
          Value = 25.000000000000000000
        end
        item
          Value = 25.000000000000000000
        end>
      ControlCollection = <
        item
          Column = 0
          Control = ButtonSelectAll
          Row = 0
        end
        item
          Column = 1
          Control = ButtonDelete
          Row = 0
        end
        item
          Column = 2
          Control = ButtonRefresh
          Row = 0
        end
        item
          Column = 3
          Control = ButtonClose
          Row = 0
        end>
      RowCollection = <
        item
          Value = 100.000000000000000000
        end>
      TabOrder = 1
      ExplicitTop = 670
      ExplicitWidth = 1050
      object ButtonSelectAll: TButton
        AlignWithMargins = True
        Left = 5
        Top = 5
        Width = 244
        Height = 70
        Margins.Left = 5
        Margins.Top = 5
        Margins.Right = 5
        Margins.Bottom = 5
        Align = alClient
        Caption = #1042#1110#1076#1084#1110#1090#1080#1090#1080' '#1074#1089#1110
        TabOrder = 0
        OnClick = ButtonSelectAllClick
        ExplicitWidth = 252
      end
      object ButtonDelete: TButton
        AlignWithMargins = True
        Left = 259
        Top = 5
        Width = 244
        Height = 70
        Margins.Left = 5
        Margins.Top = 5
        Margins.Right = 5
        Margins.Bottom = 5
        Align = alClient
        Caption = #1042#1080#1076#1072#1083#1080#1090#1080' '#1087#1086#1079#1085#1072#1095#1077#1085#1110
        TabOrder = 1
        OnClick = ButtonDeleteClick
        ExplicitLeft = 267
        ExplicitWidth = 253
      end
      object ButtonRefresh: TButton
        AlignWithMargins = True
        Left = 513
        Top = 5
        Width = 244
        Height = 70
        Margins.Left = 5
        Margins.Top = 5
        Margins.Right = 5
        Margins.Bottom = 5
        Align = alClient
        Caption = #1054#1085#1086#1074#1080#1090#1080
        TabOrder = 2
        OnClick = ButtonRefreshClick
        ExplicitLeft = 530
        ExplicitWidth = 252
      end
      object ButtonClose: TButton
        AlignWithMargins = True
        Left = 767
        Top = 5
        Width = 244
        Height = 70
        Margins.Left = 5
        Margins.Top = 5
        Margins.Right = 5
        Margins.Bottom = 5
        Align = alClient
        Caption = #1047#1072#1082#1088#1080#1090#1080
        TabOrder = 3
        OnClick = ButtonCloseClick
        ExplicitLeft = 792
        ExplicitWidth = 253
      end
    end
  end
end
