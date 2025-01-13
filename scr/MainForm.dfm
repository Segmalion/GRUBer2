object Form1: TForm1
  Left = 0
  Top = 0
  Margins.Left = 5
  Margins.Top = 5
  Margins.Right = 5
  Margins.Bottom = 5
  Anchors = []
  Caption = 'GRUBer'
  ClientHeight = 1132
  ClientWidth = 1544
  Color = clBtnFace
  Constraints.MinHeight = 600
  Constraints.MinWidth = 737
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -21
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poDesigned
  PixelsPerInch = 168
  TextHeight = 30
  object GridPanelMain: TGridPanel
    Left = 0
    Top = 0
    Width = 1544
    Height = 1132
    Margins.Left = 5
    Margins.Top = 5
    Margins.Right = 5
    Margins.Bottom = 5
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
        Value = 53.000000000000000000
      end>
    TabOrder = 0
    object GridPanel1: TGridPanel
      Left = 1
      Top = 1
      Width = 1542
      Height = 1077
      Margins.Left = 5
      Margins.Top = 5
      Margins.Right = 5
      Margins.Bottom = 5
      Align = alClient
      Anchors = []
      BevelOuter = bvNone
      ColumnCollection = <
        item
          SizeStyle = ssAbsolute
          Value = 700.000000000000000000
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
      Padding.Left = 5
      Padding.Top = 5
      Padding.Right = 5
      Padding.Bottom = 5
      RowCollection = <
        item
          Value = 100.000000000000000000
        end
        item
          SizeStyle = ssAbsolute
          Value = 88.000000000000000000
        end
        item
          SizeStyle = ssAuto
        end>
      TabOrder = 0
      ExplicitLeft = 2
      ExplicitTop = 2
      ExplicitWidth = 1540
      ExplicitHeight = 1076
      object ProgressBar1: TProgressBar
        Left = 10
        Top = 989
        Width = 1522
        Height = 78
        Margins.Left = 5
        Margins.Top = 5
        Margins.Right = 5
        Margins.Bottom = 5
        Align = alClient
        Smooth = True
        MarqueeInterval = 1
        Step = 1
        TabOrder = 0
        ExplicitLeft = 11
        ExplicitWidth = 1519
        ExplicitHeight = 77
      end
      object PageControl1: TPageControl
        Left = 10
        Top = 10
        Width = 690
        Height = 969
        Margins.Left = 5
        Margins.Top = 5
        Margins.Right = 5
        Margins.Bottom = 5
        ActivePage = TabGRUBer
        Align = alClient
        Constraints.MaxHeight = 1050
        MultiLine = True
        ParentShowHint = False
        ShowHint = False
        TabOrder = 1
        object TabGRUBer: TTabSheet
          Margins.Left = 5
          Margins.Top = 5
          Margins.Right = 5
          Margins.Bottom = 5
          Caption = 'GRUBer'
          object GridPanel2: TGridPanel
            Left = 0
            Top = 0
            Width = 682
            Height = 924
            Margins.Left = 5
            Margins.Top = 5
            Margins.Right = 5
            Margins.Bottom = 5
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
            Padding.Left = 2
            Padding.Top = 2
            Padding.Right = 2
            Padding.Bottom = 2
            RowCollection = <
              item
                Value = 74.999914283850400000
              end
              item
                SizeStyle = ssAbsolute
                Value = 53.000000000000000000
              end
              item
                SizeStyle = ssAbsolute
                Value = 88.000000000000000000
              end
              item
                Value = 25.000000000000000000
              end
              item
                SizeStyle = ssAuto
              end>
            TabOrder = 0
            ExplicitWidth = 676
            ExplicitHeight = 915
            DesignSize = (
              682
              924)
            object GroupBox1: TGroupBox
              AlignWithMargins = True
              Left = 9
              Top = 9
              Width = 393
              Height = 570
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Caption = #1044#1072#1085#1110' '#1087#1086' '#1040#1056#1052
              TabOrder = 0
              ExplicitWidth = 388
              ExplicitHeight = 565
              object GridPanel5: TGridPanel
                Left = 2
                Top = 32
                Width = 389
                Height = 536
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
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
                Padding.Left = 2
                Padding.Top = 2
                Padding.Right = 2
                Padding.Bottom = 2
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
                ExplicitLeft = 4
                ExplicitTop = 30
                ExplicitWidth = 381
                ExplicitHeight = 532
                DesignSize = (
                  389
                  536)
                object Label1: TLabel
                  AlignWithMargins = True
                  Left = 9
                  Top = 20
                  Width = 65
                  Height = 30
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = [akLeft]
                  Caption = #1053#1086#1084#1077#1088
                  Font.Charset = DEFAULT_CHARSET
                  Font.Color = clWindowText
                  Font.Height = -21
                  Font.Name = 'Segoe UI'
                  Font.Style = []
                  ParentFont = False
                  ExplicitTop = 21
                end
                object Label2: TLabel
                  AlignWithMargins = True
                  Left = 9
                  Top = 86
                  Width = 91
                  Height = 30
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = [akLeft]
                  Caption = #1055#1110#1076#1088#1086#1079#1076#1110#1083
                  ExplicitTop = 94
                end
                object Label3: TLabel
                  AlignWithMargins = True
                  Left = 9
                  Top = 219
                  Width = 91
                  Height = 30
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = [akLeft]
                  Caption = #1050#1072#1090#1077#1075#1086#1088#1110#1103
                  ExplicitTop = 233
                end
                object Label4: TLabel
                  AlignWithMargins = True
                  Left = 9
                  Top = 419
                  Width = 84
                  Height = 30
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = [akLeft]
                  Caption = #1042#1110#1076#1087#1086#1074#1110#1076'.'
                  ExplicitTop = 442
                end
                object Label5: TLabel
                  AlignWithMargins = True
                  Left = 9
                  Top = 485
                  Width = 94
                  Height = 30
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = [akLeft]
                  Caption = #1050#1086#1084#1077#1085#1090#1072#1088
                  ExplicitTop = 512
                end
                object EditNumber: TNumberBox
                  Left = 149
                  Top = 16
                  Width = 225
                  Height = 38
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = [akLeft, akTop, akRight, akBottom]
                  MaxValue = 9999.000000000000000000
                  MaxLength = 3
                  TabOrder = 0
                  SpinButtonOptions.ButtonWidth = 30
                  SpinButtonOptions.Placement = nbspCompact
                  UseMouseWheel = True
                  OnChange = EditNumberChange
                end
                object EditPartition: TComboBox
                  Left = 149
                  Top = 90
                  Width = 225
                  Height = 38
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = [akLeft, akTop, akRight, akBottom]
                  DropDownCount = 11
                  TabOrder = 1
                  Text = #1041#1077#1079' '#1074#1110#1076#1076#1110#1083#1091
                  OnChange = EditPartitionChange
                end
                object EditCategory: TComboBox
                  Left = 149
                  Top = 223
                  Width = 225
                  Height = 38
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Style = csDropDownList
                  Anchors = [akLeft, akTop, akRight, akBottom]
                  ItemIndex = 0
                  TabOrder = 3
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
                  Left = 9
                  Top = 153
                  Width = 95
                  Height = 30
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = [akLeft]
                  Caption = #1050#1083#1072#1089' '#1040#1056#1052
                  ExplicitTop = 163
                end
                object EditArmClass: TComboBox
                  Left = 149
                  Top = 156
                  Width = 225
                  Height = 38
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Style = csDropDownList
                  Anchors = [akLeft, akTop, akRight, akBottom]
                  DropDownCount = 15
                  ItemIndex = 0
                  TabOrder = 2
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
                  Left = 9
                  Top = 286
                  Width = 128
                  Height = 30
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = [akLeft]
                  Caption = #1051#1110#1094'. Windows'
                  ExplicitTop = 302
                end
                object EditLicWin: TComboBox
                  Left = 149
                  Top = 289
                  Width = 225
                  Height = 38
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
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
                  Left = 9
                  Top = 352
                  Width = 99
                  Height = 30
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = [akLeft]
                  Caption = #1051#1110#1094'. Office'
                  ExplicitTop = 373
                end
                object EditLicOffice: TComboBox
                  Left = 149
                  Top = 356
                  Width = 225
                  Height = 38
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
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
                  Left = 149
                  Top = 415
                  Width = 225
                  Height = 38
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = []
                  TabOrder = 6
                  OnChange = EditResponChange
                  ExplicitTop = 444
                end
                object EditComent: TMemo
                  Left = 149
                  Top = 479
                  Width = 225
                  Height = 42
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = []
                  ScrollBars = ssVertical
                  TabOrder = 7
                  WordWrap = False
                  OnChange = EditComentChange
                  OnDblClick = EditComentDblClick
                  ExplicitLeft = 144
                  ExplicitTop = 476
                end
              end
            end
            object BtnGruberDirOpen: TButton
              AlignWithMargins = True
              Left = 9
              Top = 646
              Width = 393
              Height = 74
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Caption = #1042#1110#1076#1082#1088#1080#1090#1080' '#1090#1077#1082#1091' '#1079' '#1075#1088#1072#1073#1086#1084
              Enabled = False
              TabOrder = 1
              OnClick = BtnGruberDirOpenClick
              ExplicitTop = 641
              ExplicitWidth = 388
              ExplicitHeight = 73
            end
            object BtnParserOpen: TButton
              AlignWithMargins = True
              Left = 416
              Top = 646
              Width = 257
              Height = 74
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Caption = 'GRUBer-Parser'
              Enabled = False
              TabOrder = 2
              OnClick = BtnParserOpenClick
              ExplicitLeft = 411
              ExplicitTop = 641
              ExplicitWidth = 256
              ExplicitHeight = 73
            end
            object GridPanel3: TGridPanel
              Left = 411
              Top = 4
              Width = 267
              Height = 580
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
              ExplicitLeft = 406
              ExplicitWidth = 266
              ExplicitHeight = 575
              object BtnGruberRun: TButton
                AlignWithMargins = True
                Left = 5
                Top = 5
                Width = 257
                Height = 310
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                Align = alClient
                Caption = #1047#1072#1087#1091#1089#1082' GRUBer'
                TabOrder = 0
                OnClick = BtnGruberRunClick
                ExplicitWidth = 256
                ExplicitHeight = 307
              end
              object BtnGruberStop: TButton
                AlignWithMargins = True
                Left = 5
                Top = 325
                Width = 257
                Height = 77
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                Align = alClient
                Caption = #1047#1091#1087#1080#1085#1080#1090#1080' GRUBer'
                DropDownMenu = PopupMenu_StopGrub
                Enabled = False
                Style = bsSplitButton
                TabOrder = 1
                OnClick = BtnGruberStopClick
                ExplicitTop = 322
                ExplicitWidth = 256
              end
              object BtnEsetUpdate: TButton
                AlignWithMargins = True
                Left = 5
                Top = 412
                Width = 257
                Height = 76
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                Align = alClient
                Caption = #1054#1085#1086#1074#1080#1090#1080' ESET'
                Enabled = False
                TabOrder = 2
                OnClick = BtnEsetUpdateClick
                ExplicitTop = 410
                ExplicitWidth = 256
                ExplicitHeight = 75
              end
              object BtnKiberConsolOpen: TButton
                AlignWithMargins = True
                Left = 5
                Top = 498
                Width = 257
                Height = 77
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                Align = alClient
                Caption = #1042#1110#1076#1082#1088#1080#1090#1080' '#1050#1086#1085#1089#1086#1083#1100
                DropDownMenu = PopupMenu_SysTool
                Style = bsSplitButton
                TabOrder = 3
                OnClick = BtnKiberConsolOpenClick
                ExplicitTop = 495
                ExplicitWidth = 256
                ExplicitHeight = 76
              end
            end
            object GroupBox2: TGroupBox
              AlignWithMargins = True
              Left = 9
              Top = 734
              Width = 664
              Height = 181
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Caption = #1030#1085#1092#1086' '#1087#1086' '#1040#1056#1052
              TabOrder = 4
              ExplicitTop = 728
              ExplicitWidth = 658
              ExplicitHeight = 179
              object GridPanel6: TGridPanel
                Left = 2
                Top = 32
                Width = 660
                Height = 147
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
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
                Padding.Bottom = 2
                RowCollection = <
                  item
                    Value = 50.000000000000000000
                  end
                  item
                    Value = 50.000000000000000000
                  end>
                TabOrder = 0
                ExplicitLeft = 4
                ExplicitTop = 30
                ExplicitWidth = 651
                ExplicitHeight = 145
                DesignSize = (
                  660
                  147)
                object Label6: TLabel
                  Left = 12
                  Top = 20
                  Width = 87
                  Height = 30
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = [akTop, akRight, akBottom]
                  Caption = #1057#1077#1088#1110#1081#1085#1080#1082
                  ExplicitLeft = 10
                end
                object ShowSerial: TEdit
                  Left = 107
                  Top = 17
                  Width = 350
                  Height = 35
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = [akLeft, akTop, akRight, akBottom]
                  Font.Charset = DEFAULT_CHARSET
                  Font.Color = clWindowText
                  Font.Height = -23
                  Font.Name = 'Consolas'
                  Font.Style = []
                  ParentFont = False
                  ReadOnly = True
                  TabOrder = 0
                  Text = 'ShowSerial'
                end
                object BtnInfo: TButton
                  Left = 475
                  Top = 13
                  Width = 175
                  Height = 44
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = [akLeft, akTop, akRight, akBottom]
                  Caption = #1030#1053#1060#1054
                  TabOrder = 1
                  OnClick = BtnInfoClick
                end
                object Label8: TLabel
                  Left = 11
                  Top = 92
                  Width = 88
                  Height = 30
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = [akTop, akRight, akBottom]
                  Caption = #1030#1084#39#1103' '#1040#1056#1052
                  ExplicitLeft = 12
                end
                object ShowName: TEdit
                  Left = 107
                  Top = 90
                  Width = 350
                  Height = 35
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = [akLeft, akTop, akRight, akBottom]
                  Font.Charset = DEFAULT_CHARSET
                  Font.Color = clWindowText
                  Font.Height = -23
                  Font.Name = 'Consolas'
                  Font.Style = []
                  ParentFont = False
                  ReadOnly = True
                  TabOrder = 2
                  Text = 'ShowName'
                end
                object BtnLicense: TButton
                  Left = 475
                  Top = 83
                  Width = 175
                  Height = 48
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = [akLeft, akTop, akRight, akBottom]
                  Caption = #1051#1110#1094#1077#1085#1079#1110#1111
                  TabOrder = 3
                  OnClick = BtnLicenseClick
                end
              end
            end
            object EditDirGrubName: TEdit
              AlignWithMargins = True
              Left = 14
              Top = 595
              Width = 654
              Height = 35
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Alignment = taCenter
              Anchors = [akLeft, akRight]
              Color = clWhite
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clBlack
              Font.Height = -23
              Font.Name = 'Consolas'
              Font.Style = [fsBold]
              ParentFont = False
              ReadOnly = True
              TabOrder = 5
              Text = 'EditDirGrubName'
              OnChange = EditDirGrubNameChange
              ExplicitTop = 588
            end
          end
        end
        object Tool: TTabSheet
          Margins.Left = 5
          Margins.Top = 5
          Margins.Right = 5
          Margins.Bottom = 5
          Caption = #1057#1055#1047
          ImageIndex = 2
          object GridPanel7: TGridPanel
            Left = 0
            Top = 0
            Width = 682
            Height = 924
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
                Value = 254.000000000000000000
              end
              item
                SizeStyle = ssAbsolute
                Value = 184.000000000000000000
              end
              item
                SizeStyle = ssAbsolute
                Value = 184.000000000000000000
              end
              item
                Value = 100.000000000000000000
              end>
            TabOrder = 0
            ExplicitWidth = 676
            ExplicitHeight = 915
            DesignSize = (
              682
              924)
            object GroupBox_AppInfo: TGroupBox
              AlignWithMargins = True
              Left = 5
              Top = 5
              Width = 672
              Height = 244
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Caption = #1030#1085#1092#1086#1088#1084#1072#1094#1110#1103' '#1086' '#1055#1050
              TabOrder = 0
              ExplicitWidth = 665
              object GridPanel9: TGridPanel
                Left = 2
                Top = 32
                Width = 668
                Height = 210
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
                ExplicitLeft = 4
                ExplicitTop = 30
                ExplicitWidth = 658
                object BtnApp_HWiNFO: TButton
                  AlignWithMargins = True
                  Left = 5
                  Top = 5
                  Width = 324
                  Height = 60
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Align = alClient
                  Caption = 'HWiNFO'
                  TabOrder = 0
                  OnClick = BtnApp_HWiNFOClick
                  ExplicitWidth = 319
                end
                object BtnApp_procexp: TButton
                  AlignWithMargins = True
                  Left = 339
                  Top = 5
                  Width = 324
                  Height = 60
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Align = alClient
                  Caption = 'Process Explorer'
                  TabOrder = 1
                  OnClick = BtnApp_procexpClick
                  ExplicitLeft = 334
                  ExplicitWidth = 319
                end
                object BtnApp_CPUZ: TButton
                  AlignWithMargins = True
                  Left = 5
                  Top = 75
                  Width = 324
                  Height = 60
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Align = alClient
                  Caption = 'CPU-Z'
                  TabOrder = 2
                  OnClick = BtnApp_CPUZClick
                  ExplicitWidth = 319
                end
                object BtnApp_autoruns: TButton
                  AlignWithMargins = True
                  Left = 339
                  Top = 75
                  Width = 324
                  Height = 60
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Align = alClient
                  Caption = 'AutoRuns'
                  TabOrder = 3
                  OnClick = BtnApp_autorunsClick
                  ExplicitLeft = 334
                  ExplicitWidth = 319
                end
                object BtnApp_GPUZ: TButton
                  AlignWithMargins = True
                  Left = 5
                  Top = 145
                  Width = 324
                  Height = 60
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Align = alClient
                  Caption = 'GPU-Z'
                  TabOrder = 4
                  OnClick = BtnApp_GPUZClick
                  ExplicitWidth = 319
                end
                object BtnApp_tcpview: TButton
                  AlignWithMargins = True
                  Left = 339
                  Top = 145
                  Width = 324
                  Height = 60
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Align = alClient
                  Caption = 'TcpView'
                  TabOrder = 5
                  OnClick = BtnApp_tcpviewClick
                  ExplicitLeft = 334
                  ExplicitWidth = 319
                end
              end
            end
            object GroupBox_AppFille: TGroupBox
              AlignWithMargins = True
              Left = 5
              Top = 259
              Width = 672
              Height = 174
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Caption = #1060#1072#1081#1083#1086#1074#1072' '#1089#1080#1089#1090#1077#1084#1072
              TabOrder = 1
              ExplicitWidth = 665
              ExplicitHeight = 173
              object GridPanel10: TGridPanel
                Left = 2
                Top = 32
                Width = 668
                Height = 140
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
                ExplicitLeft = 4
                ExplicitTop = 30
                ExplicitWidth = 658
                object BtnApp_Total: TButton
                  AlignWithMargins = True
                  Left = 5
                  Top = 5
                  Width = 324
                  Height = 60
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Align = alClient
                  Caption = 'Total Commander'
                  TabOrder = 0
                  OnClick = BtnApp_TotalClick
                  ExplicitWidth = 319
                end
                object BtnApp_Everything: TButton
                  AlignWithMargins = True
                  Left = 339
                  Top = 5
                  Width = 324
                  Height = 60
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Align = alClient
                  Caption = 'Everything'
                  TabOrder = 1
                  OnClick = BtnApp_EverythingClick
                  ExplicitLeft = 334
                  ExplicitWidth = 319
                end
                object BtnApp_3: TButton
                  AlignWithMargins = True
                  Left = 5
                  Top = 75
                  Width = 324
                  Height = 60
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Align = alClient
                  Caption = '...'
                  Enabled = False
                  TabOrder = 2
                  ExplicitWidth = 319
                end
                object BtnApp_4: TButton
                  AlignWithMargins = True
                  Left = 339
                  Top = 75
                  Width = 324
                  Height = 60
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Align = alClient
                  Caption = '...'
                  Enabled = False
                  TabOrder = 3
                  ExplicitLeft = 334
                  ExplicitWidth = 319
                end
              end
            end
            object GroupBox_AppUSB: TGroupBox
              AlignWithMargins = True
              Left = 5
              Top = 443
              Width = 672
              Height = 174
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Caption = 'USB '#1087#1088#1080#1089#1090#1088#1086#1111
              TabOrder = 2
              ExplicitWidth = 665
              ExplicitHeight = 173
              object Button1: TButton
                Left = 280
                Top = 70
                Width = 131
                Height = 44
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                Caption = 'Button1'
                Enabled = False
                TabOrder = 0
              end
            end
            object CheckBox_RunAs: TCheckBox
              Left = 22
              Top = 872
              Width = 637
              Height = 52
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Anchors = [akBottom]
              Caption = #1047#1072#1087#1091#1089#1090#1080#1090#1080' '#1089' '#1087#1088#1072#1074#1072#1084#1080' '#1072#1076#1084#1110#1085#1110#1089#1090#1088#1072#1090#1086#1088#1072
              Checked = True
              State = cbChecked
              TabOrder = 3
              ExplicitLeft = 19
              ExplicitTop = 863
            end
          end
        end
        object TabSettings: TTabSheet
          Margins.Left = 5
          Margins.Top = 5
          Margins.Right = 5
          Margins.Bottom = 5
          Caption = #1053#1072#1083#1072#1096#1090#1091#1074#1072#1085#1103
          ImageIndex = 1
          object GridPanel8: TGridPanel
            Left = 0
            Top = 0
            Width = 682
            Height = 924
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
                Control = GroupBox3
                Row = 0
              end
              item
                Column = 0
                Control = GroupBox4
                Row = 1
              end>
            RowCollection = <
              item
                SizeStyle = ssAbsolute
                Value = 450.000000000000000000
              end
              item
                Value = 100.000000000000000000
              end>
            TabOrder = 0
            ExplicitWidth = 676
            ExplicitHeight = 915
            object GroupBox3: TGroupBox
              AlignWithMargins = True
              Left = 5
              Top = 5
              Width = 672
              Height = 440
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Caption = #1053#1072#1083#1072#1096#1090#1091#1074#1072#1085#1085#1103' GRUBer'#39#1072
              TabOrder = 0
              ExplicitWidth = 665
              object CheckBoxShowLog: TCheckBox
                Left = 397
                Top = 131
                Width = 170
                Height = 30
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                Caption = #1054#1082#1085#1086' '#1083#1086#1075#1091
                TabOrder = 0
                OnClick = CheckBoxShowLogClick
              end
              object CheckBoxDebug: TCheckBox
                Left = 397
                Top = 172
                Width = 221
                Height = 29
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                Caption = #1044#1077#1073#1072#1075'-'#1110#1085#1092#1086
                TabOrder = 1
                OnClick = CheckBoxDebugClick
              end
              object EditGrubUser: TLabeledEdit
                Left = 19
                Top = 67
                Width = 627
                Height = 38
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                EditLabel.Width = 116
                EditLabel.Height = 30
                EditLabel.Margins.Left = 28
                EditLabel.Margins.Top = 28
                EditLabel.Margins.Right = 28
                EditLabel.Margins.Bottom = 28
                EditLabel.Caption = #1050#1086#1088#1080#1089#1090#1091#1074#1072#1095':'
                TabOrder = 2
                Text = ''
                OnChange = EditGrubUserChange
              end
              object CheckBoxAudit: TCheckBox
                Left = 19
                Top = 252
                Width = 368
                Height = 30
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                AllowGrayed = True
                Caption = #1043#1077#1085#1077#1088#1091#1074#1072#1090#1080' '#1092#1072#1081#1083' "audit.html"'
                TabOrder = 3
                OnClick = CheckBoxAuditClick
              end
              object CheckBoxEsetLog: TCheckBox
                Left = 19
                Top = 292
                Width = 368
                Height = 30
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                AllowGrayed = True
                Caption = #1043#1077#1085#1077#1088#1091#1074#1072#1090#1080' '#1092#1072#1081#1083' "esetLog.zip"'
                TabOrder = 4
                OnClick = CheckBoxEsetLogClick
              end
              object CheckBoxOldGrub: TCheckBox
                Left = 19
                Top = 131
                Width = 368
                Height = 30
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                Caption = #1043#1077#1085#1077#1088#1091#1074#1072#1090#1080' '#1086#1089#1085#1086#1074#1085#1110' '#1092#1072#1081#1083#1080#9662' '
                PopupMenu = PopupMenu_mailGrubFile
                TabOrder = 5
                OnClick = CheckBoxOldGrubClick
              end
              object CheckBoxNewGrub: TCheckBox
                Left = 19
                Top = 172
                Width = 368
                Height = 29
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                Caption = #1043#1077#1085#1077#1088#1091#1074#1072#1090#1080' '#1086#1073#1108#1076#1085#1072#1085#1080#1081' '#1110#1085#1092#1086'-'#1092#1072#1081#1083
                TabOrder = 6
                OnClick = CheckBoxNewGrubClick
              end
              object CheckBoxLicense: TCheckBox
                Left = 19
                Top = 212
                Width = 368
                Height = 30
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                Caption = #1043#1077#1085#1077#1088#1091#1074#1072#1090#1080' '#1092#1072#1081#1083' "license.txt"'
                TabOrder = 7
                OnClick = CheckBoxLicenseClick
              end
              object BtnEditPartition: TButton
                Left = 397
                Top = 252
                Width = 249
                Height = 67
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                Caption = #1056#1077#1076#1072#1075#1091#1074#1072#1090#1080' '#1087#1110#1076#1088#1086#1079#1076#1110#1083#1080
                TabOrder = 8
                OnClick = BtnEditPartitionClick
              end
              object CheckBox_ShowEsetUpdate: TCheckBox
                Left = 397
                Top = 212
                Width = 263
                Height = 30
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                Caption = #1054#1082#1085#1086' '#1086#1085#1086#1074#1083#1077#1085#1085#1103' ESET'
                TabOrder = 9
                OnClick = CheckBox_ShowEsetUpdateClick
              end
              object BtnSaveSetteings: TButton
                AlignWithMargins = True
                Left = 19
                Top = 376
                Width = 627
                Height = 51
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                Caption = #1047#1073#1077#1088#1077#1075#1090#1080' '#1085#1072#1083#1072#1096#1090#1091#1074#1072#1085#1085#1103
                TabOrder = 10
                OnClick = BtnSaveSetteingsClick
              end
              object EditPrefixPartition: TEdit
                Left = 291
                Top = 327
                Width = 355
                Height = 38
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                Enabled = False
                TabOrder = 11
                OnChange = EditPrefixPartitionChange
              end
              object CheckBoxPrefixPartition: TCheckBox
                Left = 19
                Top = 333
                Width = 263
                Height = 29
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                Caption = #1055#1088#1077#1092#1110#1082#1089' '#1076#1086' '#1087#1110#1076#1088#1086#1079#1076#1110#1083#1091':'
                TabOrder = 12
                OnClick = CheckBoxPrefixPartitionClick
              end
            end
            object GroupBox4: TGroupBox
              Left = 0
              Top = 450
              Width = 682
              Height = 474
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Caption = #1053#1072#1083#1072#1096#1090#1091#1074#1072#1085#1085#1103' '#1086#1085#1086#1074#1083#1077#1085#1085#1103' ESET ('#1076#1083#1103' '#1087#1086#1090#1086#1095#1085#1086#1075#1086' '#1055#1050')'
              TabOrder = 1
              ExplicitWidth = 676
              ExplicitHeight = 465
              object EditEsetMirrorDir: TLabeledEdit
                Left = 25
                Top = 70
                Width = 355
                Height = 38
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                EditLabel.Width = 137
                EditLabel.Height = 30
                EditLabel.Margins.Left = 28
                EditLabel.Margins.Top = 28
                EditLabel.Margins.Right = 28
                EditLabel.Margins.Bottom = 28
                EditLabel.Caption = #1058#1077#1082#1072' '#1076#1083#1103' '#1073#1072#1079#1080':'
                Enabled = False
                TabOrder = 0
                Text = 'C:\ESET\mirror'
                OnChange = EditEsetMirrorDirChange
              end
              object BtnEditEsetMirrorDir: TButton
                Left = 403
                Top = 42
                Width = 248
                Height = 114
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                Caption = #1047#1084#1110#1085#1080#1090#1080' '#1090#1077#1082#1091
                Enabled = False
                TabOrder = 1
                OnClick = BtnEditEsetMirrorDirClick
              end
              object CheckBoxEsetAutoUpdate: TCheckBox
                Left = 25
                Top = 121
                Width = 355
                Height = 30
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                Caption = #1040#1074#1090#1086'-'#1086#1085#1086#1074#1083#1077#1085#1085#1103' ('#1095#1077#1088#1077#1079' '#1084#1077#1088#1077#1078#1091')'
                Checked = True
                State = cbChecked
                TabOrder = 2
                OnClick = CheckBoxEsetAutoUpdateClick
              end
            end
          end
        end
      end
      object MemoLOG: TMemo
        Left = 710
        Top = 10
        Width = 822
        Height = 969
        Margins.Left = 5
        Margins.Top = 5
        Margins.Right = 5
        Margins.Bottom = 5
        Align = alClient
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -23
        Font.Name = 'Consolas'
        Font.Style = []
        ParentFont = False
        ReadOnly = True
        ScrollBars = ssBoth
        TabOrder = 2
        ExplicitLeft = 711
        ExplicitTop = 11
        ExplicitWidth = 819
        ExplicitHeight = 967
      end
    end
    object StatusBar1: TStatusBar
      Left = 1
      Top = 1078
      Width = 1542
      Height = 53
      Margins.Left = 5
      Margins.Top = 5
      Margins.Right = 5
      Margins.Bottom = 5
      Align = alClient
      Anchors = []
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Segoe UI'
      Font.Style = []
      Panels = <
        item
          BiDiMode = bdLeftToRight
          ParentBiDiMode = False
          Text = ' GRUBer '#1085#1077' '#1079#1072#1087#1091#1089#1082#1072#1074#1089#1103
          Width = 280
        end
        item
          Text = ' '#1041#1072#1079#1080' '#1085#1077' '#1086#1085#1086#1074#1083#1102#1074#1072#1083#1080#1089#1103
          Width = 280
        end
        item
          Alignment = taRightJustify
          Text = 'v.0.0.0.0 '
          Width = 88
        end>
      UseSystemFont = False
      ExplicitLeft = 2
      ExplicitWidth = 1540
    end
  end
  object BtnAboutGruber: TButton
    Left = 658
    Top = 5
    Width = 44
    Height = 41
    Hint = #1055#1088#1086' GRUBer'
    Margins.Left = 5
    Margins.Top = 5
    Margins.Right = 5
    Margins.Bottom = 5
    Align = alCustom
    Caption = '...'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 1
    OnClick = BtnAboutGruberClick
  end
  object DirOpenEsetMirror: TFileOpenDialog
    FavoriteLinks = <>
    FileTypes = <>
    Options = [fdoPickFolders, fdoForceFileSystem, fdoPathMustExist, fdoDontAddToRecent]
    OnFileOkClick = DirOpenEsetMirrorFileOkClick
    Left = 801
    Top = 679
  end
  object PopupMenu_SysTool: TPopupMenu
    Left = 1019
    Top = 483
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
    Left = 799
    Top = 581
  end
  object PopupMenu_StopGrub: TPopupMenu
    Left = 1019
    Top = 679
    object Рass: TMenuItem
      Caption = #1055#1088#1086#1087#1091#1089#1082' '#1082#1088#1086#1082#1091
      OnClick = РassClick
    end
  end
  object PopupMenu_mailGrubFile: TPopupMenu
    AutoLineReduction = maManual
    Left = 1019
    Top = 581
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
      Caption = 'net1.txt && net2.txt'
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
