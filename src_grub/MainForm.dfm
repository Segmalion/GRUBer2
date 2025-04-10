object Form1: TForm1
  Left = 0
  Top = 0
  Margins.Left = 5
  Margins.Top = 5
  Margins.Right = 5
  Margins.Bottom = 5
  Anchors = []
  Caption = 'GRUBer'
  ClientHeight = 1019
  ClientWidth = 1570
  Color = clBtnFace
  Constraints.MinHeight = 621
  Constraints.MinWidth = 425
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -21
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poDesigned
  PixelsPerInch = 168
  TextHeight = 30
  object Label12: TLabel
    Left = 728
    Top = 518
    Width = 71
    Height = 30
    Margins.Left = 5
    Margins.Top = 5
    Margins.Right = 5
    Margins.Bottom = 5
    Caption = 'Label12'
  end
  object GridPanelMain: TGridPanel
    Left = 0
    Top = 0
    Width = 1570
    Height = 1019
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
      Width = 1568
      Height = 964
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
      object ProgressBar1: TProgressBar
        Left = 10
        Top = 876
        Width = 1548
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
      end
      object PageControl1: TPageControl
        Left = 10
        Top = 10
        Width = 690
        Height = 856
        Margins.Left = 5
        Margins.Top = 5
        Margins.Right = 5
        Margins.Bottom = 5
        ActivePage = Tool
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
            Height = 811
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
            DesignSize = (
              682
              811)
            object GroupBox1: TGroupBox
              AlignWithMargins = True
              Left = 9
              Top = 9
              Width = 393
              Height = 485
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Caption = #1044#1072#1085#1110' '#1087#1086' '#1040#1056#1052
              TabOrder = 0
              object GridPanel5: TGridPanel
                Left = 2
                Top = 32
                Width = 389
                Height = 451
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
                    Row = 5
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
                    Column = 1
                    Control = EditRespon
                    Row = 5
                  end
                  item
                    Column = 0
                    ColumnSpan = 2
                    Control = EditComent
                    Row = 6
                    RowSpan = 2
                  end
                  item
                    Column = 0
                    Control = Label18
                    Row = 4
                  end
                  item
                    Column = 1
                    Control = EditPurpose
                    Row = 4
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
                DesignSize = (
                  389
                  451)
                object Label1: TLabel
                  AlignWithMargins = True
                  Left = 9
                  Top = 15
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
                  ExplicitTop = 16
                end
                object Label2: TLabel
                  AlignWithMargins = True
                  Left = 9
                  Top = 71
                  Width = 91
                  Height = 30
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = [akLeft]
                  Caption = #1055#1110#1076#1088#1086#1079#1076#1110#1083
                  ExplicitTop = 79
                end
                object Label3: TLabel
                  AlignWithMargins = True
                  Left = 9
                  Top = 183
                  Width = 91
                  Height = 30
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = [akLeft]
                  Caption = #1050#1072#1090#1077#1075#1086#1088#1110#1103
                  ExplicitTop = 198
                end
                object Label4: TLabel
                  AlignWithMargins = True
                  Left = 9
                  Top = 294
                  Width = 84
                  Height = 30
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = [akLeft]
                  Caption = #1042#1110#1076#1087#1086#1074#1110#1076'.'
                  ExplicitTop = 318
                end
                object EditNumber: TNumberBox
                  Left = 149
                  Top = 11
                  Width = 226
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
                  Top = 67
                  Width = 226
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
                  Top = 179
                  Width = 226
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
                  Top = 127
                  Width = 95
                  Height = 30
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = [akLeft]
                  Caption = #1050#1083#1072#1089' '#1040#1056#1052
                  ExplicitTop = 138
                end
                object EditArmClass: TComboBox
                  Left = 149
                  Top = 123
                  Width = 226
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
                object EditRespon: TEdit
                  Left = 149
                  Top = 290
                  Width = 226
                  Height = 38
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = []
                  TabOrder = 4
                  OnChange = EditResponChange
                end
                object EditComent: TMemo
                  Left = 14
                  Top = 343
                  Width = 361
                  Height = 100
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = []
                  ScrollBars = ssVertical
                  TabOrder = 5
                  WordWrap = False
                  OnChange = EditComentChange
                  OnDblClick = EditComentDblClick
                end
                object Label18: TLabel
                  AlignWithMargins = True
                  Left = 9
                  Top = 238
                  Width = 117
                  Height = 30
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = [akLeft]
                  Caption = #1055#1088#1080#1079#1085#1072#1095#1077#1085#1103
                  ExplicitTop = 258
                end
                object EditPurpose: TEdit
                  Left = 149
                  Top = 234
                  Width = 226
                  Height = 38
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = []
                  TabOrder = 6
                  OnChange = EditPurposeChange
                end
              end
            end
            object BtnGruberDirOpen: TButton
              AlignWithMargins = True
              Left = 9
              Top = 561
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
            end
            object BtnParserOpen: TButton
              AlignWithMargins = True
              Left = 416
              Top = 561
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
            end
            object GridPanel3: TGridPanel
              Left = 411
              Top = 4
              Width = 267
              Height = 495
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
                  Row = 4
                end
                item
                  Column = 0
                  Control = BtnClearPC
                  Row = 3
                end>
              RowCollection = <
                item
                  SizeStyle = ssAbsolute
                  Value = 200.000000000000000000
                end
                item
                  Value = 24.999991078742820000
                end
                item
                  Value = 24.999962061518270000
                end
                item
                  Value = 25.000000000000000000
                end
                item
                  Value = 25.000000000000000000
                end>
              TabOrder = 3
              object BtnGruberRun: TButton
                AlignWithMargins = True
                Left = 5
                Top = 5
                Width = 257
                Height = 190
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                Align = alClient
                Caption = #1047#1072#1087#1091#1089#1082' GRUBer'
                DropDownMenu = PopupMenu_GrubButton
                Style = bsSplitButton
                TabOrder = 0
                OnClick = BtnGruberRunClick
              end
              object BtnGruberStop: TButton
                AlignWithMargins = True
                Left = 5
                Top = 205
                Width = 257
                Height = 64
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
              end
              object BtnEsetUpdate: TButton
                AlignWithMargins = True
                Left = 5
                Top = 279
                Width = 257
                Height = 63
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                Align = alClient
                Caption = #1054#1085#1086#1074#1080#1090#1080' ESET'
                Enabled = False
                TabOrder = 2
                OnClick = BtnEsetUpdateClick
              end
              object BtnKiberConsolOpen: TButton
                AlignWithMargins = True
                Left = 5
                Top = 426
                Width = 257
                Height = 64
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
              end
              object BtnClearPC: TButton
                AlignWithMargins = True
                Left = 5
                Top = 352
                Width = 257
                Height = 64
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                Align = alClient
                Caption = #1054#1095#1080#1089#1090#1082#1072' '#1090#1080#1084'.'#1092#1072#1081#1083#1110#1074
                Enabled = False
                TabOrder = 4
                OnClick = BtnClearPCClick
              end
            end
            object GroupBox2: TGroupBox
              AlignWithMargins = True
              Left = 9
              Top = 649
              Width = 664
              Height = 153
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Caption = #1030#1085#1092#1086' '#1087#1086' '#1040#1056#1052
              TabOrder = 4
              object GridPanel6: TGridPanel
                Left = 2
                Top = 32
                Width = 660
                Height = 119
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                Align = alClient
                BevelOuter = bvNone
                ColumnCollection = <
                  item
                    Value = 17.470910822227080000
                  end
                  item
                    Value = 54.015947787545290000
                  end
                  item
                    Value = 28.513141390227630000
                  end>
                ControlCollection = <
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
                    Column = 1
                    Control = ShowName
                    Row = 1
                  end
                  item
                    Column = 2
                    Control = BtnLicense
                    Row = 1
                  end
                  item
                    Column = 0
                    Control = Button_Serial
                    Row = 0
                  end
                  item
                    Column = 0
                    Control = Button_ChangeNamePC
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
                DesignSize = (
                  660
                  119)
                object ShowSerial: TEdit
                  Left = 118
                  Top = 10
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
                  Left = 478
                  Top = 6
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
                object ShowName: TEdit
                  Left = 118
                  Top = 69
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
                  Left = 478
                  Top = 63
                  Width = 175
                  Height = 47
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = [akLeft, akTop, akRight, akBottom]
                  Caption = #1051#1110#1094#1077#1085#1079#1110#1111
                  TabOrder = 3
                  OnClick = BtnLicenseClick
                end
                object Button_Serial: TButton
                  AlignWithMargins = True
                  Left = 5
                  Top = 5
                  Width = 105
                  Height = 46
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Align = alClient
                  Caption = #1057#1077#1088#1110#1081#1085#1080#1082':'
                  TabOrder = 4
                  OnClick = Button_SerialClick
                end
                object Button_ChangeNamePC: TButton
                  AlignWithMargins = True
                  Left = 5
                  Top = 63
                  Width = 105
                  Height = 47
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Align = alClient
                  Caption = #1030#1084#39#1103' '#1055#1050':'
                  Enabled = False
                  TabOrder = 5
                end
              end
            end
            object EditDirGrubName: TEdit
              AlignWithMargins = True
              Left = 13
              Top = 510
              Width = 655
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
              TabOrder = 5
              Text = 'EditDirGrubName'
              OnChange = EditDirGrubNameChange
            end
          end
        end
        object TabGRUBerP: TTabSheet
          Margins.Left = 5
          Margins.Top = 5
          Margins.Right = 5
          Margins.Bottom = 5
          Caption = 'GRUBer+'
          ImageIndex = 3
          object GridPanel4: TGridPanel
            Left = 0
            Top = 0
            Width = 682
            Height = 811
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
                Control = GroupBox5
                Row = 0
              end
              item
                Column = 0
                Control = GroupBox6
                Row = 1
              end
              item
                Column = 0
                Control = GroupBox7
                Row = 2
              end>
            RowCollection = <
              item
                SizeStyle = ssAbsolute
                Value = 345.000000000000000000
              end
              item
                SizeStyle = ssAbsolute
                Value = 194.000000000000000000
              end
              item
                SizeStyle = ssAbsolute
                Value = 144.000000000000000000
              end
              item
                Value = 100.000000000000000000
              end>
            TabOrder = 0
            object GroupBox5: TGroupBox
              AlignWithMargins = True
              Left = 5
              Top = 5
              Width = 672
              Height = 335
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Caption = #1044#1086#1082#1091#1084#1077#1085#1090#1080' '#1087#1086' '#1040#1056#1052
              TabOrder = 0
              object GridPanel11: TGridPanel
                Left = 2
                Top = 32
                Width = 668
                Height = 301
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                Align = alClient
                BevelOuter = bvNone
                ColumnCollection = <
                  item
                    Value = 39.448458173837060000
                  end
                  item
                    Value = 60.551541826162940000
                  end>
                ControlCollection = <
                  item
                    Column = 0
                    Control = Label11
                    Row = 0
                  end
                  item
                    Column = 1
                    Control = Edit_InNumberARM
                    Row = 0
                  end
                  item
                    Column = 0
                    Control = Label13
                    Row = 1
                  end
                  item
                    Column = 1
                    Control = Edit_InNumberHDD
                    Row = 1
                  end
                  item
                    Column = 0
                    Control = Label14
                    Row = 2
                  end
                  item
                    Column = 1
                    Control = Edit_InNumberDeclr
                    Row = 2
                  end
                  item
                    Column = 0
                    Control = Label15
                    Row = 3
                  end
                  item
                    Column = 1
                    Control = Edit_InNumberFormulyar
                    Row = 3
                  end
                  item
                    Column = 0
                    Control = Label16
                    Row = 4
                  end
                  item
                    Column = 1
                    Control = Edit_InNumberWork
                    Row = 4
                  end
                  item
                    Column = 0
                    Control = Label17
                    Row = 5
                  end
                  item
                    Column = 1
                    Control = Edit_InNumberPerson
                    Row = 5
                  end>
                RowCollection = <
                  item
                    Value = 16.666666666666660000
                  end
                  item
                    Value = 16.666666666666660000
                  end
                  item
                    Value = 16.666666666666660000
                  end
                  item
                    Value = 16.666666666666660000
                  end
                  item
                    Value = 16.666666666666660000
                  end
                  item
                    Value = 16.666666666666700000
                  end>
                TabOrder = 0
                DesignSize = (
                  668
                  301)
                object Label11: TLabel
                  AlignWithMargins = True
                  Left = 5
                  Top = 10
                  Width = 244
                  Height = 30
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = [akLeft]
                  Caption = #1030#1085#1074#1077#1085#1090#1072#1088#1085#1080#1081' '#1085#1086#1084#1077#1088' '#1040#1056#1052':'
                  ExplicitTop = 12
                end
                object Edit_InNumberARM: TEdit
                  Left = 276
                  Top = 6
                  Width = 380
                  Height = 38
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = []
                  TabOrder = 0
                  Text = 'Edit_InNumberARM'
                  OnChange = Edit_InNumberARMChange
                end
                object Label13: TLabel
                  AlignWithMargins = True
                  Left = 5
                  Top = 60
                  Width = 251
                  Height = 30
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = [akLeft]
                  Caption = #1030#1085#1074#1077#1085#1090#1072#1088#1085#1080#1081' '#1085#1086#1084#1077#1088' '#1046#1052#1044':'
                  ExplicitTop = 61
                end
                object Edit_InNumberHDD: TEdit
                  Left = 276
                  Top = 56
                  Width = 380
                  Height = 38
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = []
                  TabOrder = 1
                  Text = 'Edit_InNumberHDD'
                  OnChange = Edit_InNumberHDDChange
                end
                object Label14: TLabel
                  AlignWithMargins = True
                  Left = 5
                  Top = 110
                  Width = 135
                  Height = 30
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = [akLeft]
                  Caption = #8470' '#1076#1077#1082#1083#1072#1088#1072#1094#1110#1111':'
                  ExplicitTop = 112
                end
                object Edit_InNumberDeclr: TEdit
                  Left = 276
                  Top = 106
                  Width = 380
                  Height = 38
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = []
                  TabOrder = 2
                  Text = 'Edit_InNumberDeclr'
                  OnChange = Edit_InNumberDeclrChange
                end
                object Label15: TLabel
                  AlignWithMargins = True
                  Left = 5
                  Top = 160
                  Width = 154
                  Height = 30
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = [akLeft]
                  Caption = #1060#1086#1088#1084#1091#1083#1103#1088' '#1040#1056#1052':'
                  ExplicitTop = 163
                end
                object Edit_InNumberFormulyar: TEdit
                  Left = 276
                  Top = 156
                  Width = 380
                  Height = 38
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = []
                  TabOrder = 3
                  Text = 'Edit_InNumberFormulyar'
                  OnChange = Edit_InNumberFormulyarChange
                end
                object Label16: TLabel
                  AlignWithMargins = True
                  Left = 5
                  Top = 211
                  Width = 220
                  Height = 30
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = [akLeft]
                  Caption = #1046#1091#1088#1085#1072#1083' '#1086#1073#1083#1110#1082#1091' '#1088#1086#1073#1086#1090#1080':'
                  ExplicitTop = 212
                end
                object Edit_InNumberWork: TEdit
                  Left = 276
                  Top = 207
                  Width = 380
                  Height = 38
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = []
                  TabOrder = 4
                  Text = 'Edit_InNumberWork'
                  OnChange = Edit_InNumberWorkChange
                end
                object Label17: TLabel
                  AlignWithMargins = True
                  Left = 5
                  Top = 261
                  Width = 232
                  Height = 30
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = [akLeft]
                  Caption = #1057#1087#1080#1089#1086#1082' '#1076#1086#1087#1091#1097#1077#1085#1080#1093' '#1086#1089#1110#1073':'
                  ExplicitTop = 263
                end
                object Edit_InNumberPerson: TEdit
                  AlignWithMargins = True
                  Left = 276
                  Top = 257
                  Width = 380
                  Height = 38
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = []
                  TabOrder = 5
                  Text = 'Edit_InNumberPerson'
                  OnChange = Edit_InNumberPersonChange
                end
              end
            end
            object GroupBox6: TGroupBox
              AlignWithMargins = True
              Left = 5
              Top = 350
              Width = 672
              Height = 184
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Caption = #1053#1072#1083#1072#1096#1090#1091#1074#1072#1085#1085#1103' '#1073#1077#1079#1087#1077#1082#1080' '#1040#1056#1052
              TabOrder = 1
              object GridPanel12: TGridPanel
                Left = 2
                Top = 32
                Width = 668
                Height = 150
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                Align = alClient
                BevelOuter = bvNone
                ColumnCollection = <
                  item
                    Value = 39.374968981287910000
                  end
                  item
                    Value = 60.625031018712090000
                  end>
                ControlCollection = <
                  item
                    Column = 0
                    Control = CheckBox_PoliticInstall
                    Row = 0
                  end
                  item
                    Column = 1
                    Control = Edit_ComPoliticInstall
                    Row = 0
                  end
                  item
                    Column = 0
                    Control = CheckBox_ContrUSB
                    Row = 1
                  end
                  item
                    Column = 1
                    Control = Edit_ComContrUSB
                    Row = 1
                  end
                  item
                    Column = 0
                    Control = CheckBox_MultiUSERS
                    Row = 2
                  end
                  item
                    Column = 1
                    Control = Edit_ComMultiUSERS
                    Row = 2
                  end>
                RowCollection = <
                  item
                    Value = 33.333333333333300000
                  end
                  item
                    Value = 33.333333333333300000
                  end
                  item
                    Value = 33.333333333333400000
                  end>
                TabOrder = 0
                DesignSize = (
                  668
                  150)
                object CheckBox_PoliticInstall: TCheckBox
                  AlignWithMargins = True
                  Left = 5
                  Top = 11
                  Width = 251
                  Height = 28
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = [akLeft]
                  Caption = #1042#1089#1090#1072#1085#1086#1074#1083#1077#1085#1085#1110' '#1087#1086#1083#1110#1090#1080#1082#1080':'
                  TabOrder = 0
                  OnClick = CheckBox_PoliticInstallClick
                end
                object Edit_ComPoliticInstall: TEdit
                  Left = 275
                  Top = 6
                  Width = 380
                  Height = 38
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = []
                  TabOrder = 1
                  Text = 'Edit_ComPoliticInstall'
                  OnChange = Edit_ComPoliticInstallChange
                end
                object CheckBox_ContrUSB: TCheckBox
                  AlignWithMargins = True
                  Left = 5
                  Top = 60
                  Width = 251
                  Height = 29
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = [akLeft]
                  Caption = #1053#1072#1083#1072#1096#1090#1091#1074#1072#1085#1085#1103' '#1050#1055':'
                  TabOrder = 2
                  OnClick = CheckBox_ContrUSBClick
                end
                object Edit_ComContrUSB: TEdit
                  Left = 275
                  Top = 56
                  Width = 380
                  Height = 38
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = []
                  TabOrder = 3
                  Text = 'Edit_ComContrUSB'
                  OnChange = Edit_ComContrUSBChange
                end
                object CheckBox_MultiUSERS: TCheckBox
                  AlignWithMargins = True
                  Left = 5
                  Top = 110
                  Width = 251
                  Height = 30
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = [akLeft]
                  Caption = #1056#1086#1079#1084#1077#1078#1091#1074#1072#1085#1103' '#1076#1086#1089#1090#1091#1087#1091':'
                  TabOrder = 4
                  OnClick = CheckBox_MultiUSERSClick
                end
                object Edit_ComMultiUSERS: TEdit
                  Left = 275
                  Top = 106
                  Width = 380
                  Height = 38
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = []
                  TabOrder = 5
                  Text = 'Edit_ComMultiUSERS'
                  OnChange = Edit_ComMultiUSERSChange
                end
              end
            end
            object GroupBox7: TGroupBox
              AlignWithMargins = True
              Left = 5
              Top = 544
              Width = 672
              Height = 134
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Caption = #1030#1085#1092#1086' '#1087#1088#1086' '#1055#1054' '#1085#1072' '#1040#1056#1052
              TabOrder = 2
              object GridPanel13: TGridPanel
                Left = 2
                Top = 32
                Width = 668
                Height = 100
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                Align = alClient
                BevelOuter = bvNone
                ColumnCollection = <
                  item
                    Value = 39.559432737229440000
                  end
                  item
                    Value = 60.440567262770560000
                  end>
                ControlCollection = <
                  item
                    Column = 0
                    Control = Label9
                    Row = 0
                  end
                  item
                    Column = 1
                    Control = EditLicWin
                    Row = 0
                  end
                  item
                    Column = 0
                    Control = Label10
                    Row = 1
                  end
                  item
                    Column = 1
                    Control = EditLicOffice
                    Row = 1
                  end>
                RowCollection = <
                  item
                    Value = 50.176296918237020000
                  end
                  item
                    Value = 49.823703081762980000
                  end>
                TabOrder = 0
                DesignSize = (
                  668
                  100)
                object Label9: TLabel
                  AlignWithMargins = True
                  Left = 5
                  Top = 10
                  Width = 133
                  Height = 30
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = [akLeft]
                  Caption = #1051#1110#1094'. Windows:'
                  ExplicitTop = 15
                end
                object EditLicWin: TComboBox
                  Left = 277
                  Top = 6
                  Width = 378
                  Height = 38
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Style = csDropDownList
                  Anchors = []
                  ItemIndex = 0
                  TabOrder = 0
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
                  Top = 60
                  Width = 104
                  Height = 30
                  Margins.Left = 9
                  Margins.Top = 9
                  Margins.Right = 9
                  Margins.Bottom = 9
                  Anchors = [akLeft]
                  Caption = #1051#1110#1094'. Office:'
                  ExplicitTop = 73
                end
                object EditLicOffice: TComboBox
                  Left = 277
                  Top = 56
                  Width = 378
                  Height = 38
                  Margins.Left = 9
                  Margins.Top = 9
                  Margins.Right = 9
                  Margins.Bottom = 9
                  Style = csDropDownList
                  Anchors = []
                  ItemIndex = 0
                  TabOrder = 1
                  Text = #1053#1077' '#1074#1082#1072#1079#1072#1085#1086
                  OnChange = EditLicOfficeChange
                  Items.Strings = (
                    #1053#1077' '#1074#1082#1072#1079#1072#1085#1086
                    #1040#1082#1090#1080#1074#1086#1074#1072#1085#1072
                    #1053#1077' '#1072#1082#1090#1080#1074#1086#1074#1072#1085#1072
                    'KMS'
                    #1055#1054' '#1074#1110#1076#1089#1091#1090#1085#1077)
                end
              end
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
            Height = 811
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
                Value = 114.000000000000000000
              end
              item
                SizeStyle = ssAbsolute
                Value = 184.000000000000000000
              end
              item
                Value = 100.000000000000000000
              end>
            TabOrder = 0
            ExplicitLeft = 4
            ExplicitTop = 4
            DesignSize = (
              682
              811)
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
                end
              end
            end
            object GroupBox_AppFille: TGroupBox
              AlignWithMargins = True
              Left = 5
              Top = 259
              Width = 672
              Height = 104
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Caption = #1060#1072#1081#1083#1086#1074#1072' '#1089#1080#1089#1090#1077#1084#1072
              TabOrder = 1
              ExplicitHeight = 174
              object GridPanel10: TGridPanel
                Left = 2
                Top = 32
                Width = 668
                Height = 70
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
                  end>
                RowCollection = <
                  item
                    Value = 100.000000000000000000
                  end>
                TabOrder = 0
                ExplicitHeight = 140
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
                end
              end
            end
            object GroupBox_AppUSB: TGroupBox
              AlignWithMargins = True
              Left = 5
              Top = 373
              Width = 672
              Height = 174
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Caption = 'USB '#1087#1088#1080#1089#1090#1088#1086#1111
              TabOrder = 2
              ExplicitTop = 443
              object GridPanel14: TGridPanel
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
                    Control = BtnApp_UscDevU
                    Row = 0
                  end
                  item
                    Column = 1
                    Control = BtnApp_DeviceCleanup
                    Row = 0
                  end
                  item
                    Column = 0
                    Control = BtnApp_UsbTreeView
                    Row = 1
                  end
                  item
                    Column = 1
                    Control = Button4
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
                object BtnApp_UscDevU: TButton
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
                  Caption = 'USBDeview'
                  TabOrder = 0
                  OnClick = BtnApp_UscDevUClick
                end
                object BtnApp_DeviceCleanup: TButton
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
                  Caption = 'DeviceCleanup'
                  TabOrder = 1
                  OnClick = BtnApp_DeviceCleanupClick
                end
                object BtnApp_UsbTreeView: TButton
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
                  Caption = 'UsbTreeView'
                  TabOrder = 2
                  OnClick = BtnApp_UsbTreeViewClick
                end
                object Button4: TButton
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
                end
              end
            end
            object CheckBox_RunAs: TCheckBox
              Left = 22
              Top = 759
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
            Height = 811
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
              end
              item
                Column = 0
                Control = GridPanel15
                Row = 2
              end>
            RowCollection = <
              item
                SizeStyle = ssAbsolute
                Value = 450.000000000000000000
              end
              item
                Value = 100.000000000000000000
              end
              item
                SizeStyle = ssAbsolute
                Value = 51.000000000000000000
              end
              item
                SizeStyle = ssAuto
              end>
            TabOrder = 0
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
                Width = 632
                Height = 38
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                EditLabel.Width = 116
                EditLabel.Height = 30
                EditLabel.Margins.Left = 151
                EditLabel.Margins.Top = 151
                EditLabel.Margins.Right = 151
                EditLabel.Margins.Bottom = 151
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
                Width = 254
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
                Width = 632
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
                Width = 360
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
              AlignWithMargins = True
              Left = 5
              Top = 455
              Width = 672
              Height = 300
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Caption = #1053#1072#1083#1072#1096#1090#1091#1074#1072#1085#1085#1103' '#1086#1085#1086#1074#1083#1077#1085#1085#1103' ESET ('#1076#1083#1103' '#1087#1086#1090#1086#1095#1085#1086#1075#1086' '#1055#1050')'
              TabOrder = 1
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
                EditLabel.Margins.Left = 151
                EditLabel.Margins.Top = 151
                EditLabel.Margins.Right = 151
                EditLabel.Margins.Bottom = 151
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
            object GridPanel15: TGridPanel
              Left = 0
              Top = 760
              Width = 682
              Height = 51
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              ColumnCollection = <
                item
                  Value = 50.000000000000000000
                end
                item
                  Value = 50.000000000000000000
                end>
              ControlCollection = <
                item
                  Column = 1
                  Control = BtnAboutGruber
                  Row = 0
                end
                item
                  Column = 0
                  Control = Button_RestartAssAdmin
                  Row = 0
                end>
              RowCollection = <
                item
                  Value = 100.000000000000000000
                end>
              TabOrder = 2
              object BtnAboutGruber: TButton
                AlignWithMargins = True
                Left = 346
                Top = 6
                Width = 330
                Height = 39
                Hint = #1055#1088#1086' GRUBer'
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                Align = alClient
                Anchors = []
                Caption = #1055#1088#1086' GRUBer'
                ParentShowHint = False
                ShowHint = False
                TabOrder = 0
                OnClick = BtnAboutGruberClick
              end
              object Button_RestartAssAdmin: TButton
                AlignWithMargins = True
                Left = 6
                Top = 6
                Width = 330
                Height = 39
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                Align = alClient
                Caption = #1055#1077#1088#1077#1079#1072#1087#1091#1089#1090#1080#1090#1080' '#1074#1110#1076' '#1040#1076#1084#1110#1085#1072
                TabOrder = 1
                OnClick = Button_RestartAssAdminClick
              end
            end
          end
        end
      end
      object MemoLOG: TMemo
        Left = 710
        Top = 10
        Width = 848
        Height = 856
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
      end
    end
    object StatusBar1: TStatusBar
      Left = 1
      Top = 965
      Width = 1568
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
    end
  end
  object DirOpenEsetMirror: TFileOpenDialog
    FavoriteLinks = <>
    FileTypes = <>
    Options = [fdoPickFolders, fdoForceFileSystem, fdoPathMustExist, fdoDontAddToRecent]
    OnFileOkClick = DirOpenEsetMirrorFileOkClick
    Left = 1395
    Top = 222
  end
  object PopupMenu_SysTool: TPopupMenu
    Left = 1160
    Top = 61
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
    Left = 999
    Top = 65
  end
  object PopupMenu_StopGrub: TPopupMenu
    Left = 877
    Top = 211
    object Рass: TMenuItem
      Caption = #1055#1088#1086#1087#1091#1089#1082' '#1082#1088#1086#1082#1091
      OnClick = РassClick
    end
  end
  object PopupMenu_mailGrubFile: TPopupMenu
    AutoLineReduction = maManual
    Left = 1146
    Top = 219
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
  object PopupMenu_GrubButton: TPopupMenu
    Left = 869
    Top = 379
    object MiniGrub: TMenuItem
      Caption = #1054#1085#1086#1074#1080#1090#1080' '#1076#1072#1085#1085#1110' ('#1084#1110#1085#1110#1084#1072#1083#1100#1085#1080#1081' '#1075#1088#1072#1073')'
      OnClick = MiniGrubClick
    end
  end
end
