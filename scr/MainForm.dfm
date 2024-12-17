object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'GRUBer'
  ClientHeight = 561
  ClientWidth = 1008
  Color = clBtnFace
  Constraints.MinHeight = 600
  Constraints.MinWidth = 421
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poDesigned
  TextHeight = 15
  object GridPanelMain: TGridPanel
    Left = 0
    Top = 0
    Width = 1008
    Height = 561
    Align = alClient
    ColumnCollection = <
      item
        Value = 100.000000000000000000
      end>
    ControlCollection = <
      item
        Column = 0
        Control = GridPanel1
        Row = 0
      end
      item
        Column = 0
        Control = StatusBar1
        Row = 1
      end>
    RowCollection = <
      item
        Value = 100.000000000000000000
      end
      item
        SizeStyle = ssAbsolute
        Value = 30.000000000000000000
      end>
    TabOrder = 0
    ExplicitWidth = 1006
    ExplicitHeight = 553
    object GridPanel1: TGridPanel
      Left = 1
      Top = 1
      Width = 1006
      Height = 529
      Align = alClient
      Anchors = []
      BevelOuter = bvNone
      ColumnCollection = <
        item
          SizeStyle = ssAbsolute
          Value = 400.000000000000000000
        end
        item
          Value = 100.000000000000000000
        end>
      ControlCollection = <
        item
          Column = 0
          ColumnSpan = 2
          Control = ProgressBar1
          Row = 1
        end
        item
          Column = 0
          Control = PageControl1
          Row = 0
        end
        item
          Column = 1
          Control = MemoLOG
          Row = 0
        end>
      Padding.Left = 3
      Padding.Top = 3
      Padding.Right = 3
      Padding.Bottom = 3
      RowCollection = <
        item
          Value = 100.000000000000000000
        end
        item
          SizeStyle = ssAbsolute
          Value = 50.000000000000000000
        end
        item
          SizeStyle = ssAuto
        end>
      TabOrder = 0
      ExplicitWidth = 1004
      ExplicitHeight = 521
      object ProgressBar1: TProgressBar
        Left = 6
        Top = 479
        Width = 994
        Height = 44
        Align = alClient
        Smooth = True
        MarqueeInterval = 1
        Step = 1
        TabOrder = 0
        ExplicitTop = 471
        ExplicitWidth = 992
      end
      object PageControl1: TPageControl
        Left = 6
        Top = 6
        Width = 394
        Height = 467
        ActivePage = СПЗ
        Align = alClient
        Constraints.MaxHeight = 600
        TabOrder = 1
        ExplicitHeight = 459
        object TabGRUBer: TTabSheet
          Caption = 'GRUBer'
          object GridPanel2: TGridPanel
            Left = 0
            Top = 0
            Width = 386
            Height = 437
            Align = alClient
            BevelOuter = bvNone
            BevelWidth = 10
            ColumnCollection = <
              item
                Value = 60.000000000000000000
              end
              item
                Value = 40.000000000000000000
              end>
            ControlCollection = <
              item
                Column = 0
                Control = GroupBox1
                Row = 0
              end
              item
                Column = 0
                Control = BtnGruberDirOpen
                Row = 2
              end
              item
                Column = 1
                Control = BtnParserOpen
                Row = 2
              end
              item
                Column = 1
                Control = GridPanel3
                Row = 0
              end
              item
                Column = 0
                ColumnSpan = 2
                Control = GroupBox2
                Row = 3
              end
              item
                Column = 0
                ColumnSpan = 2
                Control = EditDirGrubName
                Row = 1
              end>
            Padding.Left = 1
            Padding.Top = 1
            Padding.Right = 1
            Padding.Bottom = 1
            RowCollection = <
              item
                Value = 74.999914283850400000
              end
              item
                SizeStyle = ssAbsolute
                Value = 30.000000000000000000
              end
              item
                SizeStyle = ssAbsolute
                Value = 50.000000000000000000
              end
              item
                Value = 25.000000000000000000
              end
              item
                SizeStyle = ssAuto
              end>
            TabOrder = 0
            ExplicitHeight = 429
            DesignSize = (
              386
              437)
            object GroupBox1: TGroupBox
              AlignWithMargins = True
              Left = 5
              Top = 5
              Width = 222
              Height = 258
              Align = alClient
              Caption = #1044#1072#1085#1110' '#1087#1086' '#1040#1056#1052
              TabOrder = 0
              ExplicitHeight = 252
              object GridPanel5: TGridPanel
                Left = 2
                Top = 17
                Width = 218
                Height = 239
                Align = alClient
                BevelOuter = bvNone
                ColumnCollection = <
                  item
                    Value = 35.070387044319030000
                  end
                  item
                    Value = 64.929612955680980000
                  end>
                ControlCollection = <
                  item
                    Column = 0
                    Control = Label1
                    Row = 0
                  end
                  item
                    Column = 0
                    Control = Label2
                    Row = 1
                  end
                  item
                    Column = 0
                    Control = Label3
                    Row = 3
                  end
                  item
                    Column = 0
                    Control = Label4
                    Row = 6
                  end
                  item
                    Column = 0
                    Control = Label5
                    Row = 7
                  end
                  item
                    Column = 1
                    Control = EditNumber
                    Row = 0
                  end
                  item
                    Column = 1
                    Control = EditPartition
                    Row = 1
                  end
                  item
                    Column = 1
                    Control = EditCategory
                    Row = 3
                  end
                  item
                    Column = 0
                    Control = Label7
                    Row = 2
                  end
                  item
                    Column = 1
                    Control = EditArmClass
                    Row = 2
                  end
                  item
                    Column = 0
                    Control = Label9
                    Row = 4
                  end
                  item
                    Column = 1
                    Control = EditLicWin
                    Row = 4
                  end
                  item
                    Column = 0
                    Control = Label10
                    Row = 5
                  end
                  item
                    Column = 1
                    Control = EditLicOffice
                    Row = 5
                  end
                  item
                    Column = 1
                    Control = EditRespon
                    Row = 6
                  end
                  item
                    Column = 1
                    Control = EditComent
                    Row = 7
                  end>
                Padding.Left = 1
                Padding.Top = 1
                Padding.Right = 1
                Padding.Bottom = 1
                RowCollection = <
                  item
                    Value = 12.500000000000000000
                  end
                  item
                    Value = 12.500000000000000000
                  end
                  item
                    Value = 12.500000000000000000
                  end
                  item
                    Value = 12.500000000000000000
                  end
                  item
                    Value = 12.500000000000000000
                  end
                  item
                    Value = 12.500000000000000000
                  end
                  item
                    Value = 12.500000000000000000
                  end
                  item
                    Value = 12.500000000000000000
                  end
                  item
                    SizeStyle = ssAuto
                  end>
                TabOrder = 0
                ExplicitHeight = 233
                DesignSize = (
                  218
                  239)
                object Label1: TLabel
                  AlignWithMargins = True
                  Left = 5
                  Top = 8
                  Width = 38
                  Height = 15
                  Anchors = [akLeft]
                  Caption = #1053#1086#1084#1077#1088
                  Font.Charset = DEFAULT_CHARSET
                  Font.Color = clWindowText
                  Font.Height = -12
                  Font.Name = 'Segoe UI'
                  Font.Style = []
                  ParentFont = False
                end
                object Label2: TLabel
                  AlignWithMargins = True
                  Left = 5
                  Top = 38
                  Width = 53
                  Height = 15
                  Anchors = [akLeft]
                  Caption = #1055#1110#1076#1088#1086#1079#1076#1110#1083
                end
                object Label3: TLabel
                  AlignWithMargins = True
                  Left = 5
                  Top = 97
                  Width = 52
                  Height = 15
                  Anchors = [akLeft]
                  Caption = #1050#1072#1090#1077#1075#1086#1088#1110#1103
                  ExplicitTop = 93
                end
                object Label4: TLabel
                  AlignWithMargins = True
                  Left = 5
                  Top = 186
                  Width = 48
                  Height = 15
                  Anchors = [akLeft]
                  Caption = #1042#1110#1076#1087#1086#1074#1110#1076'.'
                  ExplicitTop = 128
                end
                object Label5: TLabel
                  AlignWithMargins = True
                  Left = 5
                  Top = 215
                  Width = 54
                  Height = 15
                  Anchors = [akLeft]
                  Caption = #1050#1086#1084#1077#1085#1090#1072#1088
                  ExplicitTop = 170
                end
                object EditNumber: TNumberBox
                  Left = 82
                  Top = 4
                  Width = 130
                  Height = 23
                  Anchors = [akLeft, akTop, akRight, akBottom]
                  MaxValue = 9999.000000000000000000
                  MaxLength = 3
                  TabOrder = 0
                  SpinButtonOptions.Placement = nbspCompact
                  UseMouseWheel = True
                  OnChange = EditNumberChange
                end
                object EditPartition: TComboBox
                  Left = 82
                  Top = 34
                  Width = 130
                  Height = 23
                  Anchors = [akLeft, akTop, akRight, akBottom]
                  DropDownCount = 11
                  TabOrder = 1
                  Text = #1041#1077#1079' '#1074#1110#1076#1076#1110#1083#1091
                  OnChange = EditPartitionChange
                end
                object EditCategory: TComboBox
                  Left = 82
                  Top = 93
                  Width = 130
                  Height = 23
                  Style = csDropDownList
                  Anchors = [akLeft, akTop, akRight, akBottom]
                  ItemIndex = 0
                  TabOrder = 2
                  Text = #1054#1089#1086#1073#1080#1089#1090#1080#1081
                  OnChange = EditCategoryChange
                  Items.Strings = (
                    #1054#1089#1086#1073#1080#1089#1090#1080#1081
                    #1053#1058' '#1073#1077#1079' '#1087#1110#1076#1082#1083#1102#1095#1077#1085#1103
                    #1053#1058' '#1079' "'#1030#1085#1090#1077#1088#1085#1077#1090'"'
                    #1053#1058' '#1079' "'#1044#1085#1110#1087#1088#1086'"'
                    #1044#1057#1050
                    #1058#1072#1108#1084#1085#1086
                    #1062#1110#1083#1082#1086#1084' '#1058#1072#1108#1084#1085#1086)
                end
                object Label7: TLabel
                  AlignWithMargins = True
                  Left = 5
                  Top = 67
                  Width = 55
                  Height = 15
                  Anchors = [akLeft]
                  Caption = #1050#1083#1072#1089' '#1040#1056#1052
                  ExplicitTop = 77
                end
                object EditArmClass: TComboBox
                  Left = 82
                  Top = 63
                  Width = 130
                  Height = 23
                  Style = csDropDownList
                  Anchors = [akLeft, akTop, akRight, akBottom]
                  DropDownCount = 15
                  ItemIndex = 0
                  TabOrder = 3
                  Text = #1041#1077#1079' '#1082#1083#1072#1089#1091
                  OnChange = EditArmClassChange
                  Items.Strings = (
                    #1041#1077#1079' '#1082#1083#1072#1089#1091
                    #1040#1057'-1'
                    #1040#1057'-2'
                    #1040#1057'-3')
                end
                object Label9: TLabel
                  AlignWithMargins = True
                  Left = 5
                  Top = 127
                  Width = 73
                  Height = 15
                  Anchors = [akLeft]
                  Caption = #1051#1110#1094'. Windows'
                  ExplicitTop = 129
                end
                object EditLicWin: TComboBox
                  Left = 82
                  Top = 123
                  Width = 130
                  Height = 23
                  Style = csDropDownList
                  Anchors = [akLeft, akTop, akRight, akBottom]
                  ItemIndex = 0
                  TabOrder = 4
                  Text = #1053#1077' '#1074#1082#1072#1079#1072#1085#1086
                  OnChange = EditLicWinChange
                  Items.Strings = (
                    #1053#1077' '#1074#1082#1072#1079#1072#1085#1086
                    #1040#1082#1090#1080#1074#1086#1074#1072#1085#1072
                    #1053#1077' '#1072#1082#1090#1080#1074#1086#1074#1072#1085#1072
                    'KMS')
                end
                object Label10: TLabel
                  AlignWithMargins = True
                  Left = 5
                  Top = 156
                  Width = 56
                  Height = 15
                  Anchors = [akLeft]
                  Caption = #1051#1110#1094'. Office'
                  ExplicitTop = 159
                end
                object EditLicOffice: TComboBox
                  Left = 82
                  Top = 152
                  Width = 130
                  Height = 23
                  Style = csDropDownList
                  Anchors = [akLeft, akTop, akRight, akBottom]
                  ItemIndex = 0
                  TabOrder = 5
                  Text = #1053#1077' '#1074#1082#1072#1079#1072#1085#1086
                  OnChange = EditLicOfficeChange
                  Items.Strings = (
                    #1053#1077' '#1074#1082#1072#1079#1072#1085#1086
                    #1040#1082#1090#1080#1074#1086#1074#1072#1085#1072
                    #1053#1077' '#1072#1082#1090#1080#1074#1086#1074#1072#1085#1072
                    'KMS'
                    #1055#1054' '#1074#1110#1076#1089#1091#1090#1085#1077)
                end
                object EditRespon: TEdit
                  Left = 82
                  Top = 182
                  Width = 130
                  Height = 23
                  Anchors = []
                  TabOrder = 6
                  OnChange = EditResponChange
                  ExplicitTop = 177
                end
                object EditComent: TMemo
                  Left = 82
                  Top = 211
                  Width = 130
                  Height = 23
                  Anchors = []
                  ScrollBars = ssVertical
                  TabOrder = 7
                  WordWrap = False
                  OnChange = EditComentChange
                  OnDblClick = EditComentDblClick
                  ExplicitTop = 206
                end
              end
            end
            object BtnGruberDirOpen: TButton
              AlignWithMargins = True
              Left = 5
              Top = 301
              Width = 222
              Height = 42
              Align = alClient
              Caption = #1042#1110#1076#1082#1088#1080#1090#1080' '#1090#1077#1082#1091' '#1079' '#1075#1088#1072#1073#1086#1084
              Enabled = False
              TabOrder = 1
              OnClick = BtnGruberDirOpenClick
              ExplicitTop = 295
            end
            object BtnParserOpen: TButton
              AlignWithMargins = True
              Left = 235
              Top = 301
              Width = 146
              Height = 42
              Align = alClient
              Caption = 'GRUBer-Parser'
              Enabled = False
              TabOrder = 2
              OnClick = BtnParserOpenClick
              ExplicitTop = 295
            end
            object GridPanel3: TGridPanel
              Left = 232
              Top = 2
              Width = 152
              Height = 264
              Align = alClient
              BevelOuter = bvNone
              ColumnCollection = <
                item
                  Value = 100.000000000000000000
                end>
              ControlCollection = <
                item
                  Column = 0
                  Control = BtnGruberRun
                  Row = 0
                end
                item
                  Column = 0
                  Control = BtnGruberStop
                  Row = 1
                end
                item
                  Column = 0
                  Control = BtnEsetUpdate
                  Row = 2
                end
                item
                  Column = 0
                  Control = BtnKiberConsolOpen
                  Row = 3
                end>
              RowCollection = <
                item
                  Value = 55.139659955102150000
                end
                item
                  Value = 14.953446681632620000
                end
                item
                  Value = 14.953446681632620000
                end
                item
                  Value = 14.953446681632620000
                end>
              TabOrder = 3
              ExplicitHeight = 258
              object BtnGruberRun: TButton
                AlignWithMargins = True
                Left = 3
                Top = 3
                Width = 146
                Height = 140
                Align = alClient
                Caption = #1047#1072#1087#1091#1089#1082' GRUBer'
                TabOrder = 0
                OnClick = BtnGruberRunClick
                ExplicitLeft = 1
              end
              object BtnGruberStop: TButton
                AlignWithMargins = True
                Left = 3
                Top = 149
                Width = 146
                Height = 33
                Align = alClient
                Caption = #1047#1091#1087#1080#1085#1080#1090#1080' GRUBer'#9662
                Enabled = False
                PopupMenu = PopupMenu_StopGrub
                TabOrder = 1
                OnClick = BtnGruberStopClick
                ExplicitWidth = 62
              end
              object BtnEsetUpdate: TButton
                AlignWithMargins = True
                Left = 3
                Top = 188
                Width = 146
                Height = 34
                Align = alClient
                Caption = #1054#1085#1086#1074#1080#1090#1080' ESET'
                Enabled = False
                TabOrder = 2
                OnClick = BtnEsetUpdateClick
                ExplicitTop = 184
                ExplicitHeight = 32
              end
              object BtnKiberConsolOpen: TButton
                AlignWithMargins = True
                Left = 3
                Top = 228
                Width = 146
                Height = 33
                Align = alClient
                Caption = #1042#1110#1076#1082#1088#1080#1090#1080' '#1050#1086#1085#1089#1086#1083#1100#9662
                PopupMenu = PopupMenu_SysTool
                TabOrder = 3
                OnClick = BtnKiberConsolOpenClick
                ExplicitTop = 222
              end
            end
            object GroupBox2: TGroupBox
              AlignWithMargins = True
              Left = 5
              Top = 351
              Width = 376
              Height = 81
              Align = alClient
              Caption = #1030#1085#1092#1086' '#1087#1086' '#1040#1056#1052
              TabOrder = 4
              ExplicitTop = 345
              ExplicitHeight = 79
              object GridPanel6: TGridPanel
                Left = 2
                Top = 17
                Width = 372
                Height = 62
                Align = alClient
                BevelOuter = bvNone
                ColumnCollection = <
                  item
                    Value = 14.971599345010720000
                  end
                  item
                    Value = 55.651767104141970000
                  end
                  item
                    Value = 29.376633550847310000
                  end>
                ControlCollection = <
                  item
                    Column = 0
                    Control = Label6
                    Row = 0
                  end
                  item
                    Column = 1
                    Control = ShowSerial
                    Row = 0
                  end
                  item
                    Column = 2
                    Control = BtnInfo
                    Row = 0
                  end
                  item
                    Column = 0
                    Control = Label8
                    Row = 1
                  end
                  item
                    Column = 1
                    Control = ShowName
                    Row = 1
                  end
                  item
                    Column = 2
                    Control = BtnLicense
                    Row = 1
                  end>
                Padding.Bottom = 1
                RowCollection = <
                  item
                    Value = 50.000000000000000000
                  end
                  item
                    Value = 50.000000000000000000
                  end>
                TabOrder = 0
                ExplicitHeight = 60
                DesignSize = (
                  372
                  62)
                object Label6: TLabel
                  Left = 5
                  Top = 7
                  Width = 51
                  Height = 15
                  Anchors = [akTop, akRight, akBottom]
                  Caption = #1057#1077#1088#1110#1081#1085#1080#1082
                  ExplicitLeft = 3
                end
                object ShowSerial: TEdit
                  Left = 59
                  Top = 3
                  Width = 200
                  Height = 23
                  Anchors = [akLeft, akTop, akRight, akBottom]
                  Font.Charset = DEFAULT_CHARSET
                  Font.Color = clWindowText
                  Font.Height = -13
                  Font.Name = 'Consolas'
                  Font.Style = []
                  ParentFont = False
                  ReadOnly = True
                  TabOrder = 0
                  Text = 'ShowSerial'
                end
                object BtnInfo: TButton
                  Left = 267
                  Top = 2
                  Width = 100
                  Height = 25
                  Anchors = [akLeft, akTop, akRight, akBottom]
                  Caption = #1030#1053#1060#1054
                  TabOrder = 1
                  OnClick = BtnInfoClick
                end
                object Label8: TLabel
                  Left = 6
                  Top = 37
                  Width = 50
                  Height = 15
                  Anchors = [akTop, akRight, akBottom]
                  Caption = #1030#1084#39#1103' '#1040#1056#1052
                  ExplicitLeft = 3
                end
                object ShowName: TEdit
                  Left = 59
                  Top = 33
                  Width = 200
                  Height = 23
                  Anchors = [akLeft, akTop, akRight, akBottom]
                  Font.Charset = DEFAULT_CHARSET
                  Font.Color = clWindowText
                  Font.Height = -13
                  Font.Name = 'Consolas'
                  Font.Style = []
                  ParentFont = False
                  ReadOnly = True
                  TabOrder = 2
                  Text = 'ShowName'
                end
                object BtnLicense: TButton
                  Left = 267
                  Top = 32
                  Width = 100
                  Height = 25
                  Anchors = [akLeft, akTop, akRight, akBottom]
                  Caption = #1051#1110#1094#1077#1085#1079#1110#1111
                  TabOrder = 3
                  OnClick = BtnLicenseClick
                end
              end
            end
            object EditDirGrubName: TEdit
              AlignWithMargins = True
              Left = 6
              Top = 271
              Width = 374
              Height = 23
              Alignment = taCenter
              Anchors = [akLeft, akRight]
              Color = clWhite
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -13
              Font.Name = 'Consolas'
              Font.Style = [fsBold]
              ParentFont = False
              ReadOnly = True
              TabOrder = 5
              Text = 'EditDirGrubName'
              OnChange = EditDirGrubNameChange
              ExplicitTop = 265
            end
          end
        end
        object TabSettings: TTabSheet
          Caption = #1053#1072#1083#1072#1096#1090#1091#1074#1072#1085#1103
          ImageIndex = 1
          object GridPanel8: TGridPanel
            Left = 0
            Top = 0
            Width = 386
            Height = 437
            Align = alClient
            BevelOuter = bvNone
            ColumnCollection = <
              item
                Value = 100.000000000000000000
              end>
            ControlCollection = <
              item
                Column = 0
                Control = GroupBox3
                Row = 0
              end
              item
                Column = 0
                Control = BtnSaveSetteings
                Row = 1
              end
              item
                Column = 0
                Control = GroupBox4
                Row = 2
              end>
            RowCollection = <
              item
                SizeStyle = ssAbsolute
                Value = 210.000000000000000000
              end
              item
                SizeStyle = ssAbsolute
                Value = 35.000000000000000000
              end
              item
                Value = 100.000000000000000000
              end>
            TabOrder = 0
            object GroupBox3: TGroupBox
              AlignWithMargins = True
              Left = 3
              Top = 3
              Width = 380
              Height = 204
              Align = alClient
              Caption = #1053#1072#1083#1072#1096#1090#1091#1074#1072#1085#1085#1103' GRUBer'#39#1072
              TabOrder = 0
              object CheckBoxShowLog: TCheckBox
                Left = 227
                Top = 75
                Width = 97
                Height = 17
                Caption = #1054#1082#1085#1086' '#1083#1086#1075#1091
                TabOrder = 0
                OnClick = CheckBoxShowLogClick
              end
              object CheckBoxDebug: TCheckBox
                Left = 227
                Top = 98
                Width = 126
                Height = 17
                Caption = #1044#1077#1073#1072#1075'-'#1110#1085#1092#1086
                TabOrder = 1
                OnClick = CheckBoxDebugClick
              end
              object EditGrubUser: TLabeledEdit
                Left = 11
                Top = 38
                Width = 358
                Height = 23
                EditLabel.Width = 67
                EditLabel.Height = 15
                EditLabel.Caption = #1050#1086#1088#1080#1089#1090#1091#1074#1072#1095':'
                TabOrder = 2
                Text = ''
                OnChange = EditGrubUserChange
              end
              object CheckBoxAudit: TCheckBox
                Left = 11
                Top = 144
                Width = 210
                Height = 17
                AllowGrayed = True
                Caption = #1043#1077#1085#1077#1088#1091#1074#1072#1090#1080' '#1092#1072#1081#1083' "audit.html"'
                TabOrder = 3
                OnClick = CheckBoxAuditClick
              end
              object CheckBoxEsetLog: TCheckBox
                Left = 11
                Top = 167
                Width = 210
                Height = 17
                AllowGrayed = True
                Caption = #1043#1077#1085#1077#1088#1091#1074#1072#1090#1080' '#1092#1072#1081#1083' "esetLog.zip"'
                TabOrder = 4
                OnClick = CheckBoxEsetLogClick
              end
              object CheckBoxOldGrub: TCheckBox
                Left = 11
                Top = 75
                Width = 210
                Height = 17
                Caption = #1043#1077#1085#1077#1088#1091#1074#1072#1090#1080' '#1086#1089#1085#1086#1074#1085#1110' '#1092#1072#1081#1083#1080#9662' '
                PopupMenu = PopupMenu_mailGrubFile
                TabOrder = 5
                OnClick = CheckBoxOldGrubClick
              end
              object CheckBoxNewGrub: TCheckBox
                Left = 11
                Top = 98
                Width = 210
                Height = 17
                Caption = #1043#1077#1085#1077#1088#1091#1074#1072#1090#1080' '#1086#1073#1108#1076#1085#1072#1085#1080#1081' '#1110#1085#1092#1086'-'#1092#1072#1081#1083
                TabOrder = 6
                OnClick = CheckBoxNewGrubClick
              end
              object CheckBoxLicense: TCheckBox
                Left = 11
                Top = 121
                Width = 210
                Height = 17
                Caption = #1043#1077#1085#1077#1088#1091#1074#1072#1090#1080' '#1092#1072#1081#1083' "license.txt"'
                TabOrder = 7
                OnClick = CheckBoxLicenseClick
              end
              object BtnEditPartition: TButton
                Left = 227
                Top = 167
                Width = 142
                Height = 25
                Caption = #1056#1077#1076#1072#1075#1091#1074#1072#1090#1080' '#1087#1110#1076#1088#1086#1079#1076#1110#1083#1080
                TabOrder = 8
                OnClick = BtnEditPartitionClick
              end
              object CheckBox_ShowEsetUpdate: TCheckBox
                Left = 227
                Top = 121
                Width = 150
                Height = 17
                Caption = #1054#1082#1085#1086' '#1086#1085#1086#1074#1083#1077#1085#1085#1103' ESET'
                TabOrder = 9
                OnClick = CheckBox_ShowEsetUpdateClick
              end
            end
            object BtnSaveSetteings: TButton
              AlignWithMargins = True
              Left = 3
              Top = 213
              Width = 380
              Height = 29
              Align = alClient
              Caption = #1047#1073#1077#1088#1077#1075#1090#1080' '#1085#1072#1083#1072#1096#1090#1091#1074#1072#1085#1085#1103
              TabOrder = 1
              OnClick = BtnSaveSetteingsClick
            end
            object GroupBox4: TGroupBox
              Left = 0
              Top = 245
              Width = 386
              Height = 192
              Align = alClient
              Caption = #1053#1072#1083#1072#1096#1090#1091#1074#1072#1085#1085#1103' '#1086#1085#1086#1074#1083#1077#1085#1085#1103' ESET ('#1076#1083#1103' '#1087#1086#1090#1086#1095#1085#1086#1075#1086' '#1055#1050')'
              TabOrder = 2
              object EditEsetMirrorDir: TLabeledEdit
                Left = 14
                Top = 40
                Width = 203
                Height = 23
                EditLabel.Width = 77
                EditLabel.Height = 15
                EditLabel.Caption = #1058#1077#1082#1072' '#1076#1083#1103' '#1073#1072#1079#1080':'
                Enabled = False
                TabOrder = 0
                Text = 'C:\ESET\mirror'
                OnChange = EditEsetMirrorDirChange
              end
              object BtnEditEsetMirrorDir: TButton
                Left = 230
                Top = 24
                Width = 142
                Height = 65
                Caption = #1047#1084#1110#1085#1080#1090#1080' '#1090#1077#1082#1091
                Enabled = False
                TabOrder = 1
                OnClick = BtnEditEsetMirrorDirClick
              end
              object CheckBoxEsetAutoUpdate: TCheckBox
                Left = 14
                Top = 69
                Width = 203
                Height = 17
                Caption = #1040#1074#1090#1086'-'#1086#1085#1086#1074#1083#1077#1085#1085#1103' ('#1095#1077#1088#1077#1079' '#1084#1077#1088#1077#1078#1091')'
                Checked = True
                State = cbChecked
                TabOrder = 2
                OnClick = CheckBoxEsetAutoUpdateClick
              end
            end
          end
        end
        object СПЗ: TTabSheet
          Caption = #1057#1055#1047
          ImageIndex = 2
          object GridPanel7: TGridPanel
            Left = 0
            Top = 0
            Width = 386
            Height = 437
            Align = alClient
            BevelOuter = bvNone
            ColumnCollection = <
              item
                Value = 100.000000000000000000
              end>
            ControlCollection = <
              item
                Column = 0
                Control = GroupBox_AppInfo
                Row = 0
              end
              item
                Column = 0
                Control = GroupBox_AppFille
                Row = 1
              end
              item
                Column = 0
                Control = GroupBox_AppUSB
                Row = 2
              end
              item
                Column = 0
                Control = CheckBox_RunAs
                Row = 3
              end>
            RowCollection = <
              item
                SizeStyle = ssAbsolute
                Value = 145.000000000000000000
              end
              item
                SizeStyle = ssAbsolute
                Value = 105.000000000000000000
              end
              item
                SizeStyle = ssAbsolute
                Value = 105.000000000000000000
              end
              item
                Value = 100.000000000000000000
              end>
            TabOrder = 0
            DesignSize = (
              386
              437)
            object GroupBox_AppInfo: TGroupBox
              AlignWithMargins = True
              Left = 3
              Top = 3
              Width = 380
              Height = 139
              Align = alClient
              Caption = #1030#1085#1092#1086#1088#1084#1072#1094#1110#1103' '#1086' '#1055#1050
              TabOrder = 0
              object GridPanel9: TGridPanel
                Left = 2
                Top = 17
                Width = 376
                Height = 120
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
                    Control = BtnApp_HWiNFO
                    Row = 0
                  end
                  item
                    Column = 1
                    Control = BtnApp_procexp
                    Row = 0
                  end
                  item
                    Column = 0
                    Control = BtnApp_CPUZ
                    Row = 1
                  end
                  item
                    Column = 1
                    Control = BtnApp_autoruns
                    Row = 1
                  end
                  item
                    Column = 0
                    Control = BtnApp_GPUZ
                    Row = 2
                  end
                  item
                    Column = 1
                    Control = BtnApp_tcpview
                    Row = 2
                  end>
                RowCollection = <
                  item
                    Value = 33.367017709749370000
                  end
                  item
                    Value = 33.300000000000000000
                  end
                  item
                    Value = 33.332982290250640000
                  end>
                TabOrder = 0
                object BtnApp_HWiNFO: TButton
                  AlignWithMargins = True
                  Left = 3
                  Top = 3
                  Width = 182
                  Height = 34
                  Align = alClient
                  Caption = 'HWiNFO'
                  TabOrder = 0
                  OnClick = BtnApp_HWiNFOClick
                end
                object BtnApp_procexp: TButton
                  AlignWithMargins = True
                  Left = 191
                  Top = 3
                  Width = 182
                  Height = 34
                  Align = alClient
                  Caption = 'Process Explorer'
                  TabOrder = 1
                  OnClick = BtnApp_procexpClick
                end
                object BtnApp_CPUZ: TButton
                  AlignWithMargins = True
                  Left = 3
                  Top = 43
                  Width = 182
                  Height = 34
                  Align = alClient
                  Caption = 'CPU-Z'
                  TabOrder = 2
                  OnClick = BtnApp_CPUZClick
                end
                object BtnApp_autoruns: TButton
                  AlignWithMargins = True
                  Left = 191
                  Top = 43
                  Width = 182
                  Height = 34
                  Align = alClient
                  Caption = 'AutoRuns'
                  TabOrder = 3
                  OnClick = BtnApp_autorunsClick
                end
                object BtnApp_GPUZ: TButton
                  AlignWithMargins = True
                  Left = 3
                  Top = 83
                  Width = 182
                  Height = 34
                  Align = alClient
                  Caption = 'GPU-Z'
                  TabOrder = 4
                  OnClick = BtnApp_GPUZClick
                end
                object BtnApp_tcpview: TButton
                  AlignWithMargins = True
                  Left = 191
                  Top = 83
                  Width = 182
                  Height = 34
                  Align = alClient
                  Caption = 'TcpView'
                  TabOrder = 5
                  OnClick = BtnApp_tcpviewClick
                end
              end
            end
            object GroupBox_AppFille: TGroupBox
              AlignWithMargins = True
              Left = 3
              Top = 148
              Width = 380
              Height = 99
              Align = alClient
              Caption = #1060#1072#1081#1083#1086#1074#1072' '#1089#1080#1089#1090#1077#1084#1072
              TabOrder = 1
              object GridPanel10: TGridPanel
                Left = 2
                Top = 17
                Width = 376
                Height = 80
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
                    Control = BtnApp_Total
                    Row = 0
                  end
                  item
                    Column = 1
                    Control = BtnApp_Everything
                    Row = 0
                  end
                  item
                    Column = 0
                    Control = BtnApp_3
                    Row = 1
                  end
                  item
                    Column = 1
                    Control = BtnApp_4
                    Row = 1
                  end>
                RowCollection = <
                  item
                    Value = 50.000000000000000000
                  end
                  item
                    Value = 50.000000000000000000
                  end>
                TabOrder = 0
                object BtnApp_Total: TButton
                  AlignWithMargins = True
                  Left = 3
                  Top = 3
                  Width = 182
                  Height = 34
                  Align = alClient
                  Caption = 'Total Commander'
                  TabOrder = 0
                  OnClick = BtnApp_TotalClick
                end
                object BtnApp_Everything: TButton
                  AlignWithMargins = True
                  Left = 191
                  Top = 3
                  Width = 182
                  Height = 34
                  Align = alClient
                  Caption = 'Everything'
                  TabOrder = 1
                  OnClick = BtnApp_EverythingClick
                end
                object BtnApp_3: TButton
                  AlignWithMargins = True
                  Left = 3
                  Top = 43
                  Width = 182
                  Height = 34
                  Align = alClient
                  Caption = '...'
                  Enabled = False
                  TabOrder = 2
                end
                object BtnApp_4: TButton
                  AlignWithMargins = True
                  Left = 191
                  Top = 43
                  Width = 182
                  Height = 34
                  Align = alClient
                  Caption = '...'
                  Enabled = False
                  TabOrder = 3
                end
              end
            end
            object GroupBox_AppUSB: TGroupBox
              AlignWithMargins = True
              Left = 3
              Top = 253
              Width = 380
              Height = 99
              Align = alClient
              Caption = 'USB '#1087#1088#1080#1089#1090#1088#1086#1111
              TabOrder = 2
              object Button1: TButton
                Left = 160
                Top = 40
                Width = 75
                Height = 25
                Caption = 'Button1'
                TabOrder = 0
              end
            end
            object CheckBox_RunAs: TCheckBox
              Left = 11
              Top = 407
              Width = 364
              Height = 30
              Anchors = [akBottom]
              Caption = #1047#1072#1087#1091#1089#1090#1080#1090#1080' '#1089' '#1087#1088#1072#1074#1072#1084#1080' '#1072#1076#1084#1110#1085#1110#1089#1090#1088#1072#1090#1086#1088#1072
              Checked = True
              State = cbChecked
              TabOrder = 3
            end
          end
        end
      end
      object MemoLOG: TMemo
        Left = 406
        Top = 6
        Width = 594
        Height = 467
        Align = alClient
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Consolas'
        Font.Style = []
        ParentFont = False
        ReadOnly = True
        ScrollBars = ssBoth
        TabOrder = 2
        ExplicitWidth = 592
        ExplicitHeight = 459
      end
    end
    object StatusBar1: TStatusBar
      Left = 1
      Top = 530
      Width = 1006
      Height = 30
      Align = alClient
      Anchors = []
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Segoe UI'
      Font.Style = []
      Panels = <
        item
          BiDiMode = bdLeftToRight
          ParentBiDiMode = False
          Text = ' GRUBer '#1085#1077' '#1079#1072#1087#1091#1089#1082#1072#1074#1089#1103
          Width = 160
        end
        item
          Text = ' '#1041#1072#1079#1080' '#1085#1077' '#1086#1085#1086#1074#1083#1102#1074#1072#1083#1080#1089#1103
          Width = 160
        end
        item
          Alignment = taRightJustify
          Text = 'v.0.0.0.0 '
          Width = 50
        end>
      UseSystemFont = False
      ExplicitTop = 522
      ExplicitWidth = 1004
    end
  end
  object DirOpenEsetMirror: TFileOpenDialog
    FavoriteLinks = <>
    FileTypes = <>
    Options = [fdoPickFolders, fdoForceFileSystem, fdoPathMustExist, fdoDontAddToRecent]
    OnFileOkClick = DirOpenEsetMirrorFileOkClick
    Left = 465
    Top = 385
  end
  object PopupMenu_SysTool: TPopupMenu
    Left = 585
    Top = 385
    object Perfmon: TMenuItem
      Caption = #1052#1086#1085#1110#1090#1086#1088' '#1089#1090#1072#1073#1110#1083#1100#1085#1086#1089#1090#1110
      OnClick = PerfmonClick
    end
    object MsConfig: TMenuItem
      Caption = 'MsConfig'
      OnClick = MsConfigClick
    end
    object sysdmCpl: TMenuItem
      Caption = #1042#1083#1072#1089#1090#1080#1074#1086#1089#1090#1110' '#1089#1080#1089#1090#1077#1084#1110
      OnClick = sysdmCplClick
    end
  end
  object Taskbar1: TTaskbar
    TaskBarButtons = <>
    ProgressState = Normal
    ProgressMaxValue = 100
    TabProperties = []
    Left = 673
    Top = 385
  end
  object PopupMenu_StopGrub: TPopupMenu
    Left = 585
    Top = 329
    object Рass: TMenuItem
      Caption = #1055#1088#1086#1087#1091#1089#1090#1080#1090#1080' '#1096#1072#1075
      OnClick = РassClick
    end
  end
  object PopupMenu_mailGrubFile: TPopupMenu
    AutoLineReduction = maManual
    Left = 585
    Top = 273
    object ComentTxt: TMenuItem
      Caption = 'coment.txt'
      Checked = True
      OnClick = ComentTxtClick
    end
    object InfoTxt: TMenuItem
      Caption = 'info.txt'
      Checked = True
      OnClick = InfoTxtClick
    end
    object NetTxt: TMenuItem
      Caption = 'net1.txt & net2.txt'
      Checked = True
      OnClick = NetTxtClick
    end
    object UsbTxt: TMenuItem
      Caption = 'usb.txt'
      Checked = True
      OnClick = UsbTxtClick
    end
  end
end
