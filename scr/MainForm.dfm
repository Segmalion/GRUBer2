object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 567
  ClientWidth = 864
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object GridPanelMain: TGridPanel
    Left = 0
    Top = 0
    Width = 864
    Height = 567
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
    ExplicitWidth = 862
    ExplicitHeight = 559
    object GridPanel1: TGridPanel
      Left = 1
      Top = 1
      Width = 862
      Height = 535
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
        end>
      TabOrder = 0
      ExplicitWidth = 860
      ExplicitHeight = 527
      object ProgressBar1: TProgressBar
        Left = 6
        Top = 485
        Width = 850
        Height = 44
        Align = alClient
        TabOrder = 0
        ExplicitTop = 477
        ExplicitWidth = 848
      end
      object PageControl1: TPageControl
        Left = 6
        Top = 6
        Width = 394
        Height = 473
        ActivePage = grid
        Align = alClient
        TabOrder = 1
        ExplicitHeight = 465
        object grid: TTabSheet
          Caption = 'GRUBer'
          object GridPanel2: TGridPanel
            Left = 0
            Top = 0
            Width = 386
            Height = 443
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
                Control = GridPanel4
                Row = 1
              end
              item
                Column = 0
                ColumnSpan = 2
                Control = GroupBox2
                Row = 3
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
              end>
            TabOrder = 0
            ExplicitHeight = 435
            object GroupBox1: TGroupBox
              AlignWithMargins = True
              Left = 5
              Top = 5
              Width = 222
              Height = 263
              Align = alClient
              Caption = #1044#1072#1085#1110' '#1087#1086' '#1040#1056#1052
              TabOrder = 0
              ExplicitHeight = 257
              object GridPanel5: TGridPanel
                Left = 2
                Top = 17
                Width = 218
                Height = 244
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
                    Column = 1
                    Control = EditRespon
                    Row = 6
                  end
                  item
                    Column = 0
                    Control = Label5
                    Row = 7
                  end
                  item
                    Column = 1
                    Control = EditComent
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
                  end>
                TabOrder = 0
                ExplicitHeight = 238
                DesignSize = (
                  218
                  244)
                object Label1: TLabel
                  AlignWithMargins = True
                  Left = 5
                  Top = 8
                  Width = 38
                  Height = 15
                  Anchors = [akLeft]
                  Caption = #1053#1086#1084#1077#1088
                  ExplicitTop = 13
                end
                object Label2: TLabel
                  AlignWithMargins = True
                  Left = 5
                  Top = 38
                  Width = 32
                  Height = 15
                  Anchors = [akLeft]
                  Caption = #1042#1110#1076#1076#1110#1083
                  ExplicitTop = 53
                end
                object Label3: TLabel
                  AlignWithMargins = True
                  Left = 5
                  Top = 99
                  Width = 52
                  Height = 15
                  Anchors = [akLeft]
                  Caption = #1050#1072#1090#1077#1075#1086#1088#1110#1103
                  ExplicitTop = 93
                end
                object Label4: TLabel
                  AlignWithMargins = True
                  Left = 5
                  Top = 190
                  Width = 48
                  Height = 15
                  Anchors = [akLeft]
                  Caption = #1042#1110#1076#1087#1086#1074#1110#1076'.'
                  ExplicitTop = 128
                end
                object EditRespon: TEdit
                  Left = 82
                  Top = 186
                  Width = 130
                  Height = 23
                  Anchors = [akLeft, akTop, akRight, akBottom]
                  TabOrder = 0
                  OnChange = EditResponChange
                end
                object Label5: TLabel
                  AlignWithMargins = True
                  Left = 5
                  Top = 220
                  Width = 54
                  Height = 15
                  Anchors = [akLeft]
                  Caption = #1050#1086#1084#1077#1085#1090#1072#1088
                  ExplicitTop = 170
                end
                object EditComent: TEdit
                  Left = 82
                  Top = 216
                  Width = 130
                  Height = 23
                  Anchors = [akLeft, akTop, akRight, akBottom]
                  TabOrder = 1
                  OnChange = EditComentChange
                end
                object EditNumber: TNumberBox
                  Left = 82
                  Top = 4
                  Width = 130
                  Height = 23
                  Anchors = [akLeft, akTop, akRight, akBottom]
                  MaxValue = 999.000000000000000000
                  MaxLength = 3
                  TabOrder = 2
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
                  TabOrder = 3
                  Text = #1041#1077#1079' '#1074#1110#1076#1076#1110#1083#1091
                  OnChange = EditPartitionChange
                end
                object EditCategory: TComboBox
                  Left = 82
                  Top = 95
                  Width = 130
                  Height = 23
                  Style = csDropDownList
                  Anchors = [akLeft, akTop, akRight, akBottom]
                  TabOrder = 4
                  OnChange = EditCategoryChange
                end
                object Label7: TLabel
                  AlignWithMargins = True
                  Left = 5
                  Top = 69
                  Width = 55
                  Height = 15
                  Anchors = [akLeft]
                  Caption = #1050#1083#1072#1089' '#1040#1056#1052
                  ExplicitTop = 77
                end
                object EditArmClass: TComboBox
                  Left = 82
                  Top = 65
                  Width = 130
                  Height = 23
                  Style = csDropDownList
                  Anchors = [akLeft, akTop, akRight, akBottom]
                  TabOrder = 5
                  OnChange = EditArmClassChange
                end
              end
            end
            object BtnGruberDirOpen: TButton
              AlignWithMargins = True
              Left = 5
              Top = 306
              Width = 222
              Height = 42
              Align = alClient
              Caption = #1042#1110#1076#1082#1088#1080#1090#1080' '#1090#1077#1082#1091' '#1079' '#1075#1088#1072#1073#1086#1084
              TabOrder = 1
              ExplicitTop = 300
            end
            object BtnParserOpen: TButton
              AlignWithMargins = True
              Left = 235
              Top = 306
              Width = 146
              Height = 42
              Align = alClient
              Caption = 'GRUBer-Parser'
              TabOrder = 2
              ExplicitTop = 300
            end
            object GridPanel3: TGridPanel
              Left = 232
              Top = 2
              Width = 152
              Height = 269
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
              ExplicitHeight = 263
              object BtnGruberRun: TButton
                AlignWithMargins = True
                Left = 3
                Top = 3
                Width = 146
                Height = 142
                Align = alClient
                Caption = #1047#1072#1087#1091#1089#1082' GRUBer'
                TabOrder = 0
                OnClick = BtnGruberRunClick
                ExplicitHeight = 139
              end
              object BtnGruberStop: TButton
                AlignWithMargins = True
                Left = 3
                Top = 151
                Width = 146
                Height = 35
                Align = alClient
                Caption = #1047#1091#1087#1080#1085#1080#1090#1080' GRUBer'
                TabOrder = 1
                ExplicitTop = 148
                ExplicitHeight = 33
              end
              object BtnEsetUpdate: TButton
                AlignWithMargins = True
                Left = 3
                Top = 192
                Width = 146
                Height = 34
                Align = alClient
                Caption = #1054#1085#1086#1074#1080#1090#1080' ESET'
                TabOrder = 2
                ExplicitTop = 187
              end
              object BtnKiberConsolOpen: TButton
                AlignWithMargins = True
                Left = 3
                Top = 232
                Width = 146
                Height = 34
                Align = alClient
                Caption = #1042#1110#1076#1082#1088#1080#1090#1080' '#1050#1086#1085#1089#1086#1083#1100
                TabOrder = 3
                ExplicitTop = 227
                ExplicitHeight = 33
              end
            end
            object GridPanel4: TGridPanel
              Left = 2
              Top = 273
              Width = 382
              Height = 28
              Align = alClient
              BevelOuter = bvNone
              ColumnCollection = <
                item
                  SizeStyle = ssAbsolute
                  Value = 25.000000000000000000
                end
                item
                  Value = 100.000000000000000000
                end>
              ControlCollection = <
                item
                  Column = 0
                  Control = CheckBox1
                  Row = 0
                end
                item
                  Column = 1
                  Control = EditDirGrubName
                  Row = 0
                end>
              RowCollection = <
                item
                  Value = 100.000000000000000000
                end>
              TabOrder = 4
              ExplicitTop = 267
              DesignSize = (
                382
                28)
              object CheckBox1: TCheckBox
                AlignWithMargins = True
                Left = 3
                Top = 3
                Width = 19
                Height = 22
                Align = alClient
                Alignment = taLeftJustify
                DoubleBuffered = True
                ParentDoubleBuffered = False
                TabOrder = 0
              end
              object EditDirGrubName: TEdit
                Left = 28
                Top = 2
                Width = 350
                Height = 23
                Alignment = taCenter
                Anchors = [akLeft, akTop, akRight, akBottom]
                TabOrder = 1
                Text = 'EditDirGrubName'
                OnChange = EditDirGrubNameChange
              end
            end
            object GroupBox2: TGroupBox
              AlignWithMargins = True
              Left = 5
              Top = 356
              Width = 376
              Height = 82
              Align = alClient
              Caption = #1030#1085#1092#1086' '#1087#1086' '#1040#1056#1052
              TabOrder = 5
              ExplicitTop = 350
              ExplicitHeight = 80
              object GridPanel6: TGridPanel
                Left = 2
                Top = 17
                Width = 372
                Height = 63
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
                ExplicitHeight = 61
                DesignSize = (
                  372
                  63)
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
                end
                object Label8: TLabel
                  Left = 6
                  Top = 38
                  Width = 50
                  Height = 15
                  Anchors = [akTop, akRight, akBottom]
                  Caption = #1030#1084#39#1103' '#1040#1056#1052
                  ExplicitLeft = 3
                end
                object ShowName: TEdit
                  Left = 59
                  Top = 34
                  Width = 200
                  Height = 23
                  Anchors = [akLeft, akTop, akRight, akBottom]
                  ReadOnly = True
                  TabOrder = 2
                  Text = 'ShowName'
                end
                object BtnLicense: TButton
                  Left = 267
                  Top = 33
                  Width = 100
                  Height = 25
                  Anchors = [akLeft, akTop, akRight, akBottom]
                  Caption = #1051#1110#1094#1077#1085#1079#1110#1111
                  TabOrder = 3
                end
              end
            end
          end
        end
        object Налаштування: TTabSheet
          Caption = #1053#1072#1083#1072#1096#1090#1091#1074#1072#1085#1085#1103
          ImageIndex = 1
          object CheckBoxDebug: TCheckBox
            Left = 3
            Top = 423
            Width = 126
            Height = 17
            Caption = 'Debug Log Info'
            TabOrder = 0
            OnClick = CheckBoxDebugClick
          end
        end
      end
      object MemoLOG: TMemo
        Left = 406
        Top = 6
        Width = 450
        Height = 473
        Align = alClient
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Fira Code'
        Font.Style = []
        ParentFont = False
        ReadOnly = True
        ScrollBars = ssBoth
        TabOrder = 2
        ExplicitWidth = 448
        ExplicitHeight = 465
      end
    end
    object StatusBar1: TStatusBar
      Left = 1
      Top = 536
      Width = 862
      Height = 30
      Align = alClient
      Anchors = []
      Panels = <
        item
          Text = '123'
          Width = 50
        end
        item
          Text = '321'
          Width = 50
        end
        item
          Alignment = taRightJustify
          Text = 'GRUBer 0.2 '
          Width = 50
        end>
      ExplicitTop = 528
      ExplicitWidth = 860
    end
  end
end
