object Form1: TForm1
  Left = 0
  Top = 0
  Margins.Left = 5
  Margins.Top = 5
  Margins.Right = 5
  Margins.Bottom = 5
  Anchors = []
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'GRUBer'
  ClientHeight = 1179
  ClientWidth = 2076
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
  object GridPanelMain: TGridPanel
    Left = 0
    Top = 0
    Width = 2076
    Height = 1179
    Margins.Left = 5
    Margins.Top = 5
    Margins.Right = 5
    Margins.Bottom = 5
    Align = alClient
    Anchors = []
    BevelOuter = bvNone
    ColumnCollection = <
      item
        Value = 100.000000000000000000
      end>
    ControlCollection = <
      item
        Column = 0
        Control = GridPanel_forPage
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
    object GridPanel_forPage: TGridPanel
      Left = 0
      Top = 0
      Width = 2076
      Height = 1126
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
          Control = PageControl_SetInfo
          Row = 0
        end
        item
          Column = 1
          Control = PageControl2
          Row = 0
          RowSpan = 3
        end
        item
          Column = 0
          Control = ProgressBar_Grub
          Row = 2
        end
        item
          Column = 0
          Control = GridPanel_forButGrub
          Row = 1
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
          Value = 300.000000000000000000
        end
        item
          SizeStyle = ssAbsolute
          Value = 88.000000000000000000
        end>
      TabOrder = 0
      ExplicitLeft = 1
      ExplicitTop = 1
      ExplicitWidth = 2074
      ExplicitHeight = 1036
      object PageControl_SetInfo: TPageControl
        AlignWithMargins = True
        Left = 15
        Top = 15
        Width = 680
        Height = 708
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
        TabOrder = 0
        ExplicitLeft = 25
        ExplicitTop = 20
        object TabGRUBer: TTabSheet
          Margins.Left = 5
          Margins.Top = 5
          Margins.Right = 5
          Margins.Bottom = 5
          Caption = #1047#1072#1075#1072#1083#1100#1085#1072
          object GridPanel5: TGridPanel
            Left = 0
            Top = 0
            Width = 672
            Height = 663
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
                Control = Label_Number
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
                Control = Label_ResponNow
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
                Row = 7
              end
              item
                Column = 0
                Control = Label_Purpose
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
                SizeStyle = ssAbsolute
                Value = 54.000000000000000000
              end
              item
                SizeStyle = ssAbsolute
                Value = 54.000000000000000000
              end
              item
                SizeStyle = ssAbsolute
                Value = 54.000000000000000000
              end
              item
                SizeStyle = ssAbsolute
                Value = 54.000000000000000000
              end
              item
                SizeStyle = ssAbsolute
                Value = 54.000000000000000000
              end
              item
                SizeStyle = ssAbsolute
                Value = 54.000000000000000000
              end
              item
                SizeStyle = ssAbsolute
                Value = 54.000000000000000000
              end
              item
                SizeStyle = ssAbsolute
                Value = 54.000000000000000000
              end
              item
                SizeStyle = ssAbsolute
                Value = 54.000000000000000000
              end
              item
                SizeStyle = ssAbsolute
                Value = 54.000000000000000000
              end
              item
                Value = 100.000000000000000000
              end>
            TabOrder = 0
            ExplicitLeft = 14
            ExplicitTop = 9
            object Label_Number: TLabel
              AlignWithMargins = True
              Left = 9
              Top = 9
              Width = 220
              Height = 40
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Caption = #1053#1086#1084#1077#1088
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clWindowText
              Font.Height = -21
              Font.Name = 'Segoe UI'
              Font.Style = []
              ParentFont = False
              ExplicitTop = 16
              ExplicitWidth = 65
              ExplicitHeight = 30
            end
            object Label2: TLabel
              AlignWithMargins = True
              Left = 9
              Top = 63
              Width = 220
              Height = 40
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Caption = #1055#1110#1076#1088#1086#1079#1076#1110#1083
              ExplicitTop = 79
              ExplicitWidth = 91
              ExplicitHeight = 30
            end
            object Label3: TLabel
              AlignWithMargins = True
              Left = 9
              Top = 171
              Width = 220
              Height = 40
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Caption = #1050#1072#1090#1077#1075#1086#1088#1110#1103
              ExplicitTop = 198
              ExplicitWidth = 91
              ExplicitHeight = 30
            end
            object Label_ResponNow: TLabel
              AlignWithMargins = True
              Left = 9
              Top = 279
              Width = 220
              Height = 40
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Caption = #1055#1086#1090'.'#1074#1110#1076#1087#1086#1074#1110#1076'.'
              ExplicitTop = 409
              ExplicitWidth = 124
              ExplicitHeight = 30
            end
            object EditNumber: TNumberBox
              AlignWithMargins = True
              Left = 243
              Top = 9
              Width = 420
              Height = 40
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              MaxValue = 9999.000000000000000000
              MaxLength = 3
              TabOrder = 0
              SpinButtonOptions.ButtonWidth = 30
              SpinButtonOptions.Placement = nbspCompact
              UseMouseWheel = True
              OnChange = EditNumberChange
              ExplicitLeft = 330
              ExplicitTop = 21
              ExplicitWidth = 226
              ExplicitHeight = 38
            end
            object EditPartition: TComboBox
              AlignWithMargins = True
              Left = 243
              Top = 63
              Width = 420
              Height = 38
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              DropDownCount = 11
              TabOrder = 1
              Text = #1041#1077#1079' '#1074#1110#1076#1076#1110#1083#1091
              OnChange = EditPartitionChange
              ExplicitLeft = 330
              ExplicitTop = 98
              ExplicitWidth = 226
            end
            object EditCategory: TComboBox
              AlignWithMargins = True
              Left = 243
              Top = 171
              Width = 420
              Height = 38
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Style = csDropDownList
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
              ExplicitLeft = 330
              ExplicitTop = 252
              ExplicitWidth = 226
            end
            object Label7: TLabel
              AlignWithMargins = True
              Left = 9
              Top = 117
              Width = 220
              Height = 40
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Caption = #1050#1083#1072#1089' '#1040#1056#1052
              ExplicitTop = 138
              ExplicitWidth = 95
              ExplicitHeight = 30
            end
            object EditArmClass: TComboBox
              AlignWithMargins = True
              Left = 243
              Top = 117
              Width = 420
              Height = 38
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Style = csDropDownList
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
              ExplicitLeft = 330
              ExplicitTop = 175
              ExplicitWidth = 226
            end
            object EditRespon: TEdit
              AlignWithMargins = True
              Left = 243
              Top = 279
              Width = 420
              Height = 40
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              TabOrder = 4
              OnChange = EditResponChange
              ExplicitLeft = 330
              ExplicitTop = 405
              ExplicitWidth = 226
              ExplicitHeight = 38
            end
            object EditComent: TMemo
              AlignWithMargins = True
              Left = 9
              Top = 387
              Width = 654
              Height = 40
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              ScrollBars = ssVertical
              TabOrder = 5
              WordWrap = False
              OnChange = EditComentChange
              OnDblClick = EditComentDblClick
              ExplicitLeft = 148
              ExplicitTop = 490
              ExplicitWidth = 361
              ExplicitHeight = 100
            end
            object Label_Purpose: TLabel
              AlignWithMargins = True
              Left = 9
              Top = 225
              Width = 220
              Height = 40
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Caption = #1055#1088#1080#1079#1085#1072#1095#1077#1085#1103
              ExplicitTop = 258
              ExplicitWidth = 117
              ExplicitHeight = 30
            end
            object EditPurpose: TEdit
              AlignWithMargins = True
              Left = 243
              Top = 225
              Width = 420
              Height = 40
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              TabOrder = 6
              OnChange = EditPurposeChange
              ExplicitLeft = 330
              ExplicitTop = 328
              ExplicitWidth = 226
              ExplicitHeight = 38
            end
          end
        end
        object TabGRUBerP: TTabSheet
          Margins.Left = 5
          Margins.Top = 5
          Margins.Right = 5
          Margins.Bottom = 5
          Caption = #1055#1086' '#1076#1086#1082#1091#1084#1077#1085#1090#1072#1093
          ImageIndex = 3
          object GridPanel11: TGridPanel
            Left = 0
            Top = 0
            Width = 672
            Height = 663
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
            ExplicitLeft = 2
            ExplicitTop = 32
            ExplicitWidth = 658
            ExplicitHeight = 301
            DesignSize = (
              672
              663)
            object Label11: TLabel
              AlignWithMargins = True
              Left = 5
              Top = 40
              Width = 244
              Height = 30
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Anchors = [akLeft]
              Caption = #1030#1085#1074#1077#1085#1090#1072#1088#1085#1080#1081' '#1085#1086#1084#1077#1088' '#1040#1056#1052':'
              ExplicitTop = 20
            end
            object Edit_InNumberARM: TEdit
              Left = 278
              Top = 36
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
              ExplicitLeft = 269
              ExplicitTop = 6
            end
            object Label13: TLabel
              AlignWithMargins = True
              Left = 5
              Top = 150
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
              Left = 278
              Top = 146
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
              ExplicitLeft = 269
              ExplicitTop = 56
            end
            object Label14: TLabel
              AlignWithMargins = True
              Left = 5
              Top = 261
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
              Left = 278
              Top = 257
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
              ExplicitLeft = 269
              ExplicitTop = 106
            end
            object Label15: TLabel
              AlignWithMargins = True
              Left = 5
              Top = 371
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
              Left = 278
              Top = 367
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
              ExplicitLeft = 269
              ExplicitTop = 156
            end
            object Label16: TLabel
              AlignWithMargins = True
              Left = 5
              Top = 482
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
              Left = 278
              Top = 478
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
              ExplicitLeft = 269
              ExplicitTop = 207
            end
            object Label17: TLabel
              AlignWithMargins = True
              Left = 5
              Top = 592
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
              Left = 278
              Top = 588
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
              ExplicitLeft = 269
              ExplicitTop = 257
            end
          end
        end
        object TabSheet1: TTabSheet
          Margins.Left = 5
          Margins.Top = 5
          Margins.Right = 5
          Margins.Bottom = 5
          Caption = #1030#1085#1096#1077
          ImageIndex = 2
          object GridPanel1: TGridPanel
            Left = 0
            Top = 0
            Width = 672
            Height = 663
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
                Control = GroupBox6
                Row = 0
              end
              item
                Column = 0
                Control = GroupBox7
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
            ExplicitLeft = 14
            ExplicitTop = 9
            object GroupBox6: TGroupBox
              AlignWithMargins = True
              Left = 5
              Top = 5
              Width = 662
              Height = 322
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Caption = #1053#1072#1083#1072#1096#1090#1091#1074#1072#1085#1085#1103' '#1073#1077#1079#1087#1077#1082#1080' '#1040#1056#1052
              TabOrder = 0
              ExplicitLeft = 27
              ExplicitTop = 42
              ExplicitWidth = 621
              ExplicitHeight = 220
              object GridPanel12: TGridPanel
                Left = 2
                Top = 32
                Width = 658
                Height = 288
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
                ExplicitWidth = 617
                ExplicitHeight = 186
                DesignSize = (
                  658
                  288)
                object CheckBox_PoliticInstall: TCheckBox
                  AlignWithMargins = True
                  Left = 5
                  Top = 34
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
                  ExplicitTop = 17
                end
                object Edit_ComPoliticInstall: TEdit
                  Left = 268
                  Top = 29
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
                  ExplicitLeft = 243
                  ExplicitTop = 12
                end
                object CheckBox_ContrUSB: TCheckBox
                  AlignWithMargins = True
                  Left = 5
                  Top = 129
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
                  ExplicitTop = 78
                end
                object Edit_ComContrUSB: TEdit
                  Left = 268
                  Top = 125
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
                  ExplicitLeft = 243
                  ExplicitTop = 74
                end
                object CheckBox_MultiUSERS: TCheckBox
                  AlignWithMargins = True
                  Left = 5
                  Top = 225
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
                  ExplicitTop = 140
                end
                object Edit_ComMultiUSERS: TEdit
                  Left = 268
                  Top = 221
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
                  ExplicitLeft = 243
                  ExplicitTop = 136
                end
              end
            end
            object GroupBox7: TGroupBox
              AlignWithMargins = True
              Left = 5
              Top = 337
              Width = 662
              Height = 321
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Anchors = []
              Caption = #1030#1085#1092#1086' '#1087#1088#1086' '#1055#1054' '#1085#1072' '#1040#1056#1052
              TabOrder = 1
              object GridPanel13: TGridPanel
                Left = 2
                Top = 32
                Width = 658
                Height = 287
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
                  658
                  287)
                object Label9: TLabel
                  AlignWithMargins = True
                  Left = 5
                  Top = 57
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
                  Left = 270
                  Top = 53
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
                  Top = 200
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
                  Left = 270
                  Top = 196
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
      end
      object PageControl2: TPageControl
        AlignWithMargins = True
        Left = 715
        Top = 15
        Width = 1346
        Height = 1096
        Margins.Left = 5
        Margins.Top = 5
        Margins.Right = 5
        Margins.Bottom = 5
        ActivePage = TabSheet_Info
        Align = alClient
        TabOrder = 1
        ExplicitLeft = 705
        ExplicitTop = 10
        ExplicitWidth = 1354
        ExplicitHeight = 1104
        object TabSheet_Info: TTabSheet
          Margins.Left = 5
          Margins.Top = 5
          Margins.Right = 5
          Margins.Bottom = 5
          Caption = 'TabSheet_Info'
          DesignSize = (
            1338
            1051)
          object GroupBox_Info: TGroupBox
            AlignWithMargins = True
            Left = 80
            Top = 73
            Width = 664
            Height = 453
            Margins.Left = 5
            Margins.Top = 5
            Margins.Right = 5
            Margins.Bottom = 5
            Align = alCustom
            Caption = #1030#1085#1092#1086' '#1087#1086' '#1040#1056#1052
            TabOrder = 0
            ExplicitLeft = 60
            ExplicitTop = 53
            object GridPanel6: TGridPanel
              Left = 2
              Top = 32
              Width = 660
              Height = 419
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
                  Column = 1
                  Control = ShowName
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
              ExplicitTop = 29
              DesignSize = (
                660
                419)
              object ShowSerial: TEdit
                Left = 118
                Top = 85
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
              object ShowName: TEdit
                Left = 118
                Top = 294
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
                TabOrder = 1
                Text = 'ShowName'
              end
              object Button_Serial: TButton
                AlignWithMargins = True
                Left = 5
                Top = 5
                Width = 105
                Height = 196
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                Align = alClient
                Caption = #1057#1077#1088#1110#1081#1085#1080#1082':'
                TabOrder = 2
                OnClick = Button_SerialClick
                ExplicitHeight = 46
              end
              object Button_ChangeNamePC: TButton
                AlignWithMargins = True
                Left = 5
                Top = 213
                Width = 105
                Height = 197
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                Align = alClient
                Caption = #1030#1084#39#1103' '#1055#1050':'
                Enabled = False
                TabOrder = 3
                ExplicitLeft = 3
                ExplicitTop = 211
              end
            end
          end
          object BtnLicense: TButton
            Left = 86
            Top = 567
            Width = 175
            Height = 47
            Margins.Left = 5
            Margins.Top = 5
            Margins.Right = 5
            Margins.Bottom = 5
            Anchors = [akLeft, akTop, akRight, akBottom]
            Caption = #1051#1110#1094#1077#1085#1079#1110#1111
            TabOrder = 1
            OnClick = BtnLicenseClick
          end
          object BtnInfo: TButton
            Left = 296
            Top = 568
            Width = 175
            Height = 44
            Margins.Left = 5
            Margins.Top = 5
            Margins.Right = 5
            Margins.Bottom = 5
            Anchors = [akLeft, akTop, akRight, akBottom]
            Caption = #1030#1053#1060#1054
            TabOrder = 2
            OnClick = BtnInfoClick
          end
          object BtnKiberConsolOpen: TButton
            AlignWithMargins = True
            Left = 102
            Top = 692
            Width = 253
            Height = 64
            Margins.Left = 5
            Margins.Top = 5
            Margins.Right = 5
            Margins.Bottom = 5
            Align = alCustom
            Caption = #1042#1110#1076#1082#1088#1080#1090#1080' '#1050#1086#1085#1089#1086#1083#1100
            DropDownMenu = PopupMenu_SysTool
            Style = bsSplitButton
            TabOrder = 3
            OnClick = BtnKiberConsolOpenClick
            ExplicitLeft = 67
            ExplicitTop = 657
          end
          object BtnClearPC: TButton
            AlignWithMargins = True
            Left = 493
            Top = 784
            Width = 257
            Height = 75
            Margins.Left = 5
            Margins.Top = 5
            Margins.Right = 5
            Margins.Bottom = 5
            Align = alCustom
            Caption = #1054#1095#1080#1089#1090#1082#1072' '#1090#1080#1084'.'#1092#1072#1081#1083#1110#1074
            Enabled = False
            TabOrder = 4
            OnClick = BtnClearPCClick
            ExplicitLeft = 478
            ExplicitTop = 769
          end
          object BtnEsetUpdate: TButton
            AlignWithMargins = True
            Left = 200
            Top = 784
            Width = 257
            Height = 74
            Margins.Left = 5
            Margins.Top = 5
            Margins.Right = 5
            Margins.Bottom = 5
            Align = alCustom
            Caption = #1054#1085#1086#1074#1080#1090#1080' ESET'
            Enabled = False
            TabOrder = 5
            OnClick = BtnEsetUpdateClick
            ExplicitLeft = 195
            ExplicitTop = 779
          end
        end
        object TabSheet_Log: TTabSheet
          Margins.Left = 5
          Margins.Top = 5
          Margins.Right = 5
          Margins.Bottom = 5
          Caption = 'TabSheet_Log'
          ImageIndex = 1
          object MemoLOG: TMemo
            AlignWithMargins = True
            Left = 5
            Top = 5
            Width = 1328
            Height = 1041
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
            TabOrder = 0
            ExplicitWidth = 1336
            ExplicitHeight = 1049
          end
        end
        object TabSheet_Soft: TTabSheet
          Margins.Left = 5
          Margins.Top = 5
          Margins.Right = 5
          Margins.Bottom = 5
          Caption = 'TabSheet_Soft'
          ImageIndex = 3
          object GridPanel_Soft: TGridPanel
            Left = 0
            Top = 0
            Width = 1338
            Height = 1051
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
            ExplicitWidth = 1346
            ExplicitHeight = 795
            DesignSize = (
              1338
              1051)
            object GroupBox_AppInfo: TGroupBox
              AlignWithMargins = True
              Left = 5
              Top = 5
              Width = 1328
              Height = 244
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Caption = #1030#1085#1092#1086#1088#1084#1072#1094#1110#1103' '#1086' '#1055#1050
              TabOrder = 0
              ExplicitWidth = 1336
              object GridPanel9: TGridPanel
                Left = 2
                Top = 32
                Width = 1324
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
                ExplicitWidth = 1332
                object BtnApp_HWiNFO: TButton
                  AlignWithMargins = True
                  Left = 5
                  Top = 5
                  Width = 652
                  Height = 60
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Align = alClient
                  Caption = 'HWiNFO'
                  TabOrder = 0
                  OnClick = BtnApp_HWiNFOClick
                  ExplicitWidth = 656
                end
                object BtnApp_procexp: TButton
                  AlignWithMargins = True
                  Left = 667
                  Top = 5
                  Width = 652
                  Height = 60
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Align = alClient
                  Caption = 'Process Explorer'
                  TabOrder = 1
                  OnClick = BtnApp_procexpClick
                  ExplicitLeft = 671
                  ExplicitWidth = 656
                end
                object BtnApp_CPUZ: TButton
                  AlignWithMargins = True
                  Left = 5
                  Top = 75
                  Width = 652
                  Height = 60
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Align = alClient
                  Caption = 'CPU-Z'
                  TabOrder = 2
                  OnClick = BtnApp_CPUZClick
                  ExplicitWidth = 656
                end
                object BtnApp_autoruns: TButton
                  AlignWithMargins = True
                  Left = 667
                  Top = 75
                  Width = 652
                  Height = 60
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Align = alClient
                  Caption = 'AutoRuns'
                  TabOrder = 3
                  OnClick = BtnApp_autorunsClick
                  ExplicitLeft = 671
                  ExplicitWidth = 656
                end
                object BtnApp_GPUZ: TButton
                  AlignWithMargins = True
                  Left = 5
                  Top = 145
                  Width = 652
                  Height = 60
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Align = alClient
                  Caption = 'GPU-Z'
                  TabOrder = 4
                  OnClick = BtnApp_GPUZClick
                  ExplicitWidth = 656
                end
                object BtnApp_tcpview: TButton
                  AlignWithMargins = True
                  Left = 667
                  Top = 145
                  Width = 652
                  Height = 60
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Align = alClient
                  Caption = 'TcpView'
                  TabOrder = 5
                  OnClick = BtnApp_tcpviewClick
                  ExplicitLeft = 671
                  ExplicitWidth = 656
                end
              end
            end
            object GroupBox_AppFille: TGroupBox
              AlignWithMargins = True
              Left = 5
              Top = 259
              Width = 1328
              Height = 104
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Caption = #1060#1072#1081#1083#1086#1074#1072' '#1089#1080#1089#1090#1077#1084#1072
              TabOrder = 1
              ExplicitWidth = 1336
              object GridPanel10: TGridPanel
                Left = 2
                Top = 32
                Width = 1324
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
                ExplicitWidth = 1332
                object BtnApp_Total: TButton
                  AlignWithMargins = True
                  Left = 5
                  Top = 5
                  Width = 652
                  Height = 60
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Align = alClient
                  Caption = 'Total Commander'
                  TabOrder = 0
                  OnClick = BtnApp_TotalClick
                  ExplicitWidth = 656
                end
                object BtnApp_Everything: TButton
                  AlignWithMargins = True
                  Left = 667
                  Top = 5
                  Width = 652
                  Height = 60
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Align = alClient
                  Caption = 'Everything'
                  TabOrder = 1
                  OnClick = BtnApp_EverythingClick
                  ExplicitLeft = 671
                  ExplicitWidth = 656
                end
              end
            end
            object GroupBox_AppUSB: TGroupBox
              AlignWithMargins = True
              Left = 5
              Top = 373
              Width = 1328
              Height = 174
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Caption = 'USB '#1087#1088#1080#1089#1090#1088#1086#1111
              TabOrder = 2
              ExplicitWidth = 1336
              object GridPanel14: TGridPanel
                Left = 2
                Top = 32
                Width = 1324
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
                ExplicitWidth = 1332
                object BtnApp_UscDevU: TButton
                  AlignWithMargins = True
                  Left = 5
                  Top = 5
                  Width = 652
                  Height = 60
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Align = alClient
                  Caption = 'USBDeview'
                  TabOrder = 0
                  OnClick = BtnApp_UscDevUClick
                  ExplicitWidth = 656
                end
                object BtnApp_DeviceCleanup: TButton
                  AlignWithMargins = True
                  Left = 667
                  Top = 5
                  Width = 652
                  Height = 60
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Align = alClient
                  Caption = 'DeviceCleanup'
                  TabOrder = 1
                  OnClick = BtnApp_DeviceCleanupClick
                  ExplicitLeft = 671
                  ExplicitWidth = 656
                end
                object BtnApp_UsbTreeView: TButton
                  AlignWithMargins = True
                  Left = 5
                  Top = 75
                  Width = 652
                  Height = 60
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Align = alClient
                  Caption = 'UsbTreeView'
                  TabOrder = 2
                  OnClick = BtnApp_UsbTreeViewClick
                  ExplicitWidth = 656
                end
                object Button4: TButton
                  AlignWithMargins = True
                  Left = 667
                  Top = 75
                  Width = 652
                  Height = 60
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Align = alClient
                  Caption = '...'
                  Enabled = False
                  TabOrder = 3
                  ExplicitLeft = 671
                  ExplicitWidth = 656
                end
              end
            end
            object CheckBox_RunAs: TCheckBox
              Left = 350
              Top = 999
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
              ExplicitLeft = 354
              ExplicitTop = 743
            end
          end
        end
        object TabSheet_Settings: TTabSheet
          Margins.Left = 5
          Margins.Top = 5
          Margins.Right = 5
          Margins.Bottom = 5
          Caption = 'TabSheet_Settings'
          ImageIndex = 2
          object GridPanel_Settings: TGridPanel
            Left = 0
            Top = 0
            Width = 1338
            Height = 1051
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
            ExplicitWidth = 1346
            ExplicitHeight = 795
            object GroupBox3: TGroupBox
              AlignWithMargins = True
              Left = 5
              Top = 5
              Width = 1328
              Height = 440
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Caption = #1053#1072#1083#1072#1096#1090#1091#1074#1072#1085#1085#1103' GRUBer'#39#1072
              TabOrder = 0
              ExplicitWidth = 1336
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
              Width = 1328
              Height = 540
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Caption = #1053#1072#1083#1072#1096#1090#1091#1074#1072#1085#1085#1103' '#1086#1085#1086#1074#1083#1077#1085#1085#1103' ESET ('#1076#1083#1103' '#1087#1086#1090#1086#1095#1085#1086#1075#1086' '#1055#1050')'
              TabOrder = 1
              ExplicitWidth = 1336
              ExplicitHeight = 284
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
              Top = 1000
              Width = 1338
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
              ExplicitTop = 744
              ExplicitWidth = 1346
              object BtnAboutGruber: TButton
                AlignWithMargins = True
                Left = 674
                Top = 6
                Width = 658
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
                ExplicitLeft = 678
                ExplicitWidth = 662
              end
              object Button_RestartAssAdmin: TButton
                AlignWithMargins = True
                Left = 6
                Top = 6
                Width = 658
                Height = 39
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                Align = alClient
                Caption = #1055#1077#1088#1077#1079#1072#1087#1091#1089#1090#1080#1090#1080' '#1074#1110#1076' '#1040#1076#1084#1110#1085#1072
                TabOrder = 1
                OnClick = Button_RestartAssAdminClick
                ExplicitWidth = 662
              end
            end
          end
        end
      end
      object ProgressBar_Grub: TProgressBar
        AlignWithMargins = True
        Left = 15
        Top = 1043
        Width = 680
        Height = 68
        Margins.Left = 5
        Margins.Top = 5
        Margins.Right = 5
        Margins.Bottom = 5
        Align = alClient
        Anchors = []
        Smooth = True
        MarqueeInterval = 1
        Step = 1
        TabOrder = 2
        ExplicitTop = 1041
        ExplicitHeight = 73
      end
      object GridPanel_forButGrub: TGridPanel
        Left = 10
        Top = 738
        Width = 690
        Height = 290
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
            Control = EditDirGrubName
            Row = 0
          end
          item
            Column = 0
            Control = BtnGruberDirOpen
            Row = 1
          end
          item
            Column = 1
            Control = BtnParserOpen
            Row = 1
          end
          item
            Column = 0
            Control = BtnGruberRun
            Row = 2
          end
          item
            Column = 1
            Control = BtnGruberStop
            Row = 2
          end>
        RowCollection = <
          item
            SizeStyle = ssAbsolute
            Value = 44.000000000000000000
          end
          item
            Value = 50.125410621756320000
          end
          item
            Value = 49.874589378243680000
          end>
        TabOrder = 3
        ExplicitLeft = 459
        ExplicitTop = 1509
        ExplicitWidth = 323
        ExplicitHeight = 71
        object EditDirGrubName: TEdit
          AlignWithMargins = True
          Left = 5
          Top = 5
          Width = 680
          Height = 34
          Margins.Left = 5
          Margins.Top = 5
          Margins.Right = 5
          Margins.Bottom = 5
          Align = alClient
          Alignment = taCenter
          BevelEdges = []
          BevelInner = bvNone
          BiDiMode = bdLeftToRight
          Color = clWhite
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -23
          Font.Name = 'Consolas'
          Font.Style = [fsBold]
          ParentBiDiMode = False
          ParentFont = False
          TabOrder = 0
          Text = 'EditDirGrubName'
          OnChange = EditDirGrubNameChange
          ExplicitHeight = 35
        end
        object BtnGruberDirOpen: TButton
          AlignWithMargins = True
          Left = 5
          Top = 49
          Width = 335
          Height = 113
          Margins.Left = 5
          Margins.Top = 5
          Margins.Right = 5
          Margins.Bottom = 5
          Align = alClient
          Anchors = []
          Caption = #1042#1110#1076#1082#1088#1080#1090#1080' '#1090#1077#1082#1091' '#1079' '#1075#1088#1072#1073#1086#1084
          Enabled = False
          TabOrder = 1
          OnClick = BtnGruberDirOpenClick
          ExplicitLeft = 9
          ExplicitTop = 580
          ExplicitWidth = 387
          ExplicitHeight = 74
        end
        object BtnParserOpen: TButton
          AlignWithMargins = True
          Left = 350
          Top = 49
          Width = 335
          Height = 113
          Margins.Left = 5
          Margins.Top = 5
          Margins.Right = 5
          Margins.Bottom = 5
          Align = alClient
          Anchors = []
          Caption = 'GRUBer-Parser'
          Enabled = False
          TabOrder = 2
          OnClick = BtnParserOpenClick
          ExplicitLeft = 410
          ExplicitTop = 580
          ExplicitWidth = 253
          ExplicitHeight = 74
        end
        object BtnGruberRun: TButton
          AlignWithMargins = True
          Left = 5
          Top = 172
          Width = 335
          Height = 113
          Margins.Left = 5
          Margins.Top = 5
          Margins.Right = 5
          Margins.Bottom = 5
          Align = alClient
          Anchors = []
          Caption = #1047#1072#1087#1091#1089#1082' GRUBer'
          DropDownMenu = PopupMenu_GrubButton
          Style = bsSplitButton
          TabOrder = 3
          OnClick = BtnGruberRunClick
          ExplicitTop = 5
          ExplicitWidth = 253
          ExplicitHeight = 190
        end
        object BtnGruberStop: TButton
          AlignWithMargins = True
          Left = 350
          Top = 172
          Width = 335
          Height = 113
          Margins.Left = 5
          Margins.Top = 5
          Margins.Right = 5
          Margins.Bottom = 5
          Align = alClient
          Anchors = []
          Caption = #1047#1091#1087#1080#1085#1080#1090#1080' GRUBer'
          DropDownMenu = PopupMenu_StopGrub
          Enabled = False
          Style = bsSplitButton
          TabOrder = 4
          OnClick = BtnGruberStopClick
          ExplicitLeft = 5
          ExplicitTop = 205
          ExplicitWidth = 253
          ExplicitHeight = 68
        end
      end
    end
    object StatusBar1: TStatusBar
      Left = 0
      Top = 1126
      Width = 2076
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
      ExplicitLeft = 1
      ExplicitTop = 1125
      ExplicitWidth = 2074
    end
  end
  object DirOpenEsetMirror: TFileOpenDialog
    FavoriteLinks = <>
    FileTypes = <>
    Options = [fdoPickFolders, fdoForceFileSystem, fdoPathMustExist, fdoDontAddToRecent]
    OnFileOkClick = DirOpenEsetMirrorFileOkClick
    Left = 1409
    Top = 880
  end
  object PopupMenu_SysTool: TPopupMenu
    Left = 1512
    Top = 933
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
    Left = 726
    Top = 926
  end
  object PopupMenu_StopGrub: TPopupMenu
    Left = 1087
    Top = 915
    object Рass: TMenuItem
      Caption = #1055#1088#1086#1087#1091#1089#1082' '#1082#1088#1086#1082#1091
      OnClick = РassClick
    end
  end
  object PopupMenu_mailGrubFile: TPopupMenu
    AutoLineReduction = maManual
    Left = 1278
    Top = 929
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
    Left = 905
    Top = 901
    object MiniGrub: TMenuItem
      Caption = #1054#1085#1086#1074#1080#1090#1080' '#1076#1072#1085#1085#1110' ('#1084#1110#1085#1110#1084#1072#1083#1100#1085#1080#1081' '#1075#1088#1072#1073')'
      OnClick = MiniGrubClick
    end
  end
end
