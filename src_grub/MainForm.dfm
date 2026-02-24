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
  ClientHeight = 1102
  ClientWidth = 1416
  Color = clBtnFace
  Constraints.MinHeight = 621
  Constraints.MinWidth = 425
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -21
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poDesigned
  StyleName = 'Windows'
  PixelsPerInch = 168
  TextHeight = 30
  object GridPanelMain: TGridPanel
    Left = 0
    Top = 0
    Width = 1416
    Height = 1102
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
      Width = 1416
      Height = 1049
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
          Control = PageControl_InfoTabs
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
      object PageControl_SetInfo: TPageControl
        AlignWithMargins = True
        Left = 15
        Top = 15
        Width = 680
        Height = 631
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
        object TabGRUBer: TTabSheet
          Margins.Left = 5
          Margins.Top = 5
          Margins.Right = 5
          Margins.Bottom = 5
          Caption = #1047#1072#1075#1072#1083#1100#1085#1072
          object GridPanel_EditInfo: TGridPanel
            Left = 0
            Top = 0
            Width = 672
            Height = 586
            Margins.Left = 5
            Margins.Top = 5
            Margins.Right = 5
            Margins.Bottom = 5
            Align = alClient
            BevelOuter = bvNone
            ColumnCollection = <
              item
                Value = 29.954162553106570000
              end
              item
                Value = 70.045837446893430000
              end>
            ControlCollection = <
              item
                Column = 0
                Control = Label2
                Row = 1
              end
              item
                Column = 0
                Control = Label3
                Row = 2
              end
              item
                Column = 0
                Control = Label_ResponNow
                Row = 5
              end
              item
                Column = 1
                Control = EditPartition
                Row = 1
              end
              item
                Column = 1
                Control = EditCategory
                Row = 2
              end
              item
                Column = 0
                Control = Label7
                Row = 3
              end
              item
                Column = 1
                Control = EditArmClass
                Row = 3
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
                Row = 8
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
              end
              item
                Column = 0
                Control = Label_Place
                Row = 6
              end
              item
                Column = 0
                Control = Label_Phone
                Row = 7
              end
              item
                Column = 1
                Control = Edit_Place
                Row = 6
              end
              item
                Column = 1
                Control = Edit_Phone
                Row = 7
              end
              item
                Column = 0
                Control = Label_NumberARM
                Row = 0
              end
              item
                Column = 1
                Control = GridPanel2
                Row = 0
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
                Value = 100.000000000000000000
              end>
            TabOrder = 0
            object Label2: TLabel
              AlignWithMargins = True
              Left = 9
              Top = 63
              Width = 186
              Height = 40
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Caption = #1055#1110#1076#1088#1086#1079#1076#1110#1083':'
              Layout = tlCenter
              ExplicitWidth = 96
              ExplicitHeight = 30
            end
            object Label3: TLabel
              AlignWithMargins = True
              Left = 9
              Top = 117
              Width = 186
              Height = 40
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Caption = #1050#1072#1090#1077#1075#1086#1088#1110#1103':'
              Layout = tlCenter
              ExplicitWidth = 96
              ExplicitHeight = 30
            end
            object Label_ResponNow: TLabel
              AlignWithMargins = True
              Left = 9
              Top = 279
              Width = 186
              Height = 40
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Caption = #1055#1086#1090'.'#1074#1110#1076#1087#1086#1074#1110#1076'.:'
              Layout = tlCenter
              ExplicitWidth = 129
              ExplicitHeight = 30
            end
            object EditPartition: TComboBox
              AlignWithMargins = True
              Left = 209
              Top = 63
              Width = 454
              Height = 38
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              DropDownCount = 11
              TabOrder = 0
              Text = #1041#1077#1079' '#1074#1110#1076#1076#1110#1083#1091
              OnChange = EditPartitionChange
            end
            object EditCategory: TComboBox
              AlignWithMargins = True
              Left = 209
              Top = 117
              Width = 454
              Height = 38
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Style = csDropDownList
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
              Left = 9
              Top = 171
              Width = 186
              Height = 40
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Caption = #1050#1083#1072#1089' '#1040#1056#1052':'
              Layout = tlCenter
              ExplicitWidth = 100
              ExplicitHeight = 30
            end
            object EditArmClass: TComboBox
              AlignWithMargins = True
              Left = 209
              Top = 171
              Width = 454
              Height = 38
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Style = csDropDownList
              DropDownCount = 15
              ItemIndex = 0
              TabOrder = 1
              Text = #1041#1077#1079' '#1082#1083#1072#1089#1091
              OnChange = EditArmClassChange
              Items.Strings = (
                #1041#1077#1079' '#1082#1083#1072#1089#1091
                #1040#1057'-1 ('#1041#1077#1079' '#1087#1110#1076#1082#1083#1102#1095#1077#1085#1085#1103')'
                #1040#1057'-2 ('#1051#1086#1082#1072#1083#1100#1085#1072' '#1084#1077#1088#1077#1078#1072')'
                #1040#1057'-3 ('#1043#1083#1086#1073#1072#1083#1100#1085#1072' '#1084#1077#1088#1077#1078#1072')'
                #1040#1057'-3 ('#1042#1086#1088#1082#1083#1072#1091#1076')')
            end
            object EditRespon: TEdit
              AlignWithMargins = True
              Left = 209
              Top = 279
              Width = 454
              Height = 40
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              TabOrder = 3
              OnChange = EditResponChange
              ExplicitHeight = 38
            end
            object EditComent: TMemo
              AlignWithMargins = True
              Left = 9
              Top = 441
              Width = 654
              Height = 136
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              ScrollBars = ssVertical
              TabOrder = 4
              WordWrap = False
              OnChange = EditComentChange
              OnDblClick = EditComentDblClick
            end
            object Label_Purpose: TLabel
              AlignWithMargins = True
              Left = 9
              Top = 225
              Width = 186
              Height = 40
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Caption = #1055#1088#1080#1079#1085#1072#1095#1077#1085#1103':'
              Layout = tlCenter
              ExplicitWidth = 122
              ExplicitHeight = 30
            end
            object EditPurpose: TEdit
              AlignWithMargins = True
              Left = 209
              Top = 225
              Width = 454
              Height = 40
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              TabOrder = 5
              OnChange = EditPurposeChange
              ExplicitHeight = 38
            end
            object Label_Place: TLabel
              AlignWithMargins = True
              Left = 9
              Top = 333
              Width = 186
              Height = 40
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Caption = #1056#1086#1079#1090#1072#1096#1091#1074#1072#1085#1103':'
              Layout = tlCenter
              ExplicitWidth = 130
              ExplicitHeight = 30
            end
            object Label_Phone: TLabel
              AlignWithMargins = True
              Left = 9
              Top = 387
              Width = 186
              Height = 40
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Caption = #1053#1086#1084#1077#1088' '#1090#1077#1083#1077#1092#1086#1085#1091':'
              Layout = tlCenter
              ExplicitWidth = 166
              ExplicitHeight = 30
            end
            object Edit_Place: TEdit
              AlignWithMargins = True
              Left = 209
              Top = 333
              Width = 454
              Height = 40
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              TabOrder = 6
              Text = 'Edit_Place'
              OnChange = Edit_PlaceChange
              ExplicitHeight = 38
            end
            object Edit_Phone: TEdit
              AlignWithMargins = True
              Left = 209
              Top = 387
              Width = 454
              Height = 40
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              TabOrder = 7
              Text = 'Edit_Phone'
              OnChange = Edit_PhoneChange
              ExplicitHeight = 38
            end
            object Label_NumberARM: TLabel
              AlignWithMargins = True
              Left = 9
              Top = 9
              Width = 186
              Height = 40
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Anchors = []
              BiDiMode = bdLeftToRight
              Caption = #1042#1085#1091#1090#1088#1110#1096#1085#1110#1081' '#1085#1086#1084#1077#1088':'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clWindowText
              Font.Height = -21
              Font.Name = 'Segoe UI'
              Font.Style = []
              ParentBiDiMode = False
              ParentFont = False
              Layout = tlCenter
              ExplicitWidth = 179
              ExplicitHeight = 30
            end
            object GridPanel2: TGridPanel
              Left = 204
              Top = 4
              Width = 464
              Height = 50
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              BevelOuter = bvNone
              ColumnCollection = <
                item
                  Value = 39.449625188335880000
                end
                item
                  Value = 60.550374811664110000
                end>
              ControlCollection = <
                item
                  Column = 0
                  Control = Edit_NumberARM
                  Row = 0
                end
                item
                  Column = 1
                  Control = Label_infoForNumberARM
                  Row = 0
                end>
              RowCollection = <
                item
                  Value = 100.000000000000000000
                end>
              TabOrder = 8
              object Edit_NumberARM: TNumberBox
                AlignWithMargins = True
                Left = 5
                Top = 5
                Width = 173
                Height = 40
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                Align = alClient
                Anchors = []
                Color = clBtnFace
                MaxValue = 9999.000000000000000000
                MaxLength = 3
                TabOrder = 0
                SpinButtonOptions.ButtonWidth = 30
                SpinButtonOptions.Placement = nbspCompact
                UseMouseWheel = True
                OnChange = Edit_NumberARMChange
                ExplicitHeight = 38
              end
              object Label_infoForNumberARM: TLabel
                AlignWithMargins = True
                Left = 188
                Top = 5
                Width = 271
                Height = 40
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                Align = alClient
                Anchors = []
                Caption = 'Label_infoForNumberARM'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowFrame
                Font.Height = -21
                Font.Name = 'Segoe UI'
                Font.Style = [fsItalic]
                ParentFont = False
                Layout = tlCenter
                ExplicitWidth = 234
                ExplicitHeight = 30
              end
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
          object GridPanel_EditInfoDoc: TGridPanel
            Left = 0
            Top = 0
            Width = 672
            Height = 586
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
              end
              item
                Column = 0
                Control = Label_Respon
                Row = 6
              end
              item
                Column = 1
                Control = Edit_InRespon
                Row = 6
              end
              item
                Column = 1
                Control = Edit_InAdminBP
                Row = 7
              end
              item
                Column = 0
                Control = Label_AdminBP
                Row = 7
              end>
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
            DesignSize = (
              672
              586)
            object Label11: TLabel
              AlignWithMargins = True
              Left = 5
              Top = 21
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
              Top = 17
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
              Top = 95
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
              Top = 91
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
              Top = 168
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
              Top = 164
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
              Top = 241
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
              Top = 237
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
              Top = 314
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
              Top = 310
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
              Top = 388
              Width = 232
              Height = 30
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Anchors = [akLeft]
              Caption = #1057#1087#1080#1089#1086#1082' '#1076#1086#1087#1091#1097#1077#1085#1080#1093' '#1086#1089#1110#1073':'
              ExplicitTop = 439
            end
            object Edit_InNumberPerson: TEdit
              AlignWithMargins = True
              Left = 278
              Top = 384
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
            object Label_Respon: TLabel
              AlignWithMargins = True
              Left = 5
              Top = 461
              Width = 153
              Height = 30
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Anchors = [akLeft]
              Caption = #1042#1110#1076#1087#1086#1074#1110#1076#1072#1083#1100#1085#1080#1081':'
              ExplicitTop = 428
            end
            object Edit_InRespon: TEdit
              AlignWithMargins = True
              Left = 278
              Top = 457
              Width = 380
              Height = 38
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Anchors = []
              TabOrder = 6
              Text = 'Edit_InRespon'
              OnChange = Edit_InResponChange
            end
            object Edit_InAdminBP: TEdit
              AlignWithMargins = True
              Left = 278
              Top = 530
              Width = 380
              Height = 38
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Anchors = []
              TabOrder = 7
              Text = 'Edit_InAdminBP'
              OnChange = Edit_InAdminBPChange
            end
            object Label_AdminBP: TLabel
              AlignWithMargins = True
              Left = 5
              Top = 534
              Width = 145
              Height = 30
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Anchors = [akLeft]
              Caption = #1040#1076#1084#1110#1085' '#1041#1077#1079#1087#1077#1082#1080':'
              ExplicitTop = 497
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
            Height = 586
            Margins.Left = 5
            Margins.Top = 5
            Margins.Right = 5
            Margins.Bottom = 5
            Align = alClient
            BevelOuter = bvNone
            ColumnCollection = <
              item
                Value = 61.819980217606330000
              end
              item
                Value = 38.180019782393670000
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
              end
              item
                Column = 1
                Control = GroupBox_SPZ
                Row = 0
                RowSpan = 3
              end>
            RowCollection = <
              item
                SizeStyle = ssAbsolute
                Value = 185.000000000000000000
              end
              item
                SizeStyle = ssAbsolute
                Value = 140.000000000000000000
              end
              item
                Value = 100.000000000000000000
              end>
            TabOrder = 0
            object GroupBox6: TGroupBox
              AlignWithMargins = True
              Left = 5
              Top = 5
              Width = 405
              Height = 175
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Caption = #1053#1072#1083#1072#1096#1090#1091#1074#1072#1085#1085#1103' '#1073#1077#1079#1087#1077#1082#1080' '#1040#1056#1052
              TabOrder = 0
              object GridPanel_EditInfoBezp: TGridPanel
                Left = 2
                Top = 32
                Width = 401
                Height = 141
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
                    Column = 1
                    Control = ComboBox_PoliticInstall
                    Row = 0
                  end
                  item
                    Column = 1
                    Control = ComboBox_ContrUSB
                    Row = 1
                  end
                  item
                    Column = 1
                    Control = ComboBox_MultiUSERS
                    Row = 2
                  end
                  item
                    Column = 0
                    Control = Label18
                    Row = 0
                  end
                  item
                    Column = 0
                    Control = Label19
                    Row = 1
                  end
                  item
                    Column = 0
                    Control = Label20
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
                object ComboBox_PoliticInstall: TComboBox
                  AlignWithMargins = True
                  Left = 163
                  Top = 5
                  Width = 233
                  Height = 38
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Align = alClient
                  TabOrder = 0
                  Text = '---'
                  OnChange = ComboBox_PoliticInstallChange
                end
                object ComboBox_ContrUSB: TComboBox
                  AlignWithMargins = True
                  Left = 163
                  Top = 52
                  Width = 233
                  Height = 38
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Align = alClient
                  TabOrder = 1
                  Text = '---'
                  OnChange = ComboBox_ContrUSBChange
                end
                object ComboBox_MultiUSERS: TComboBox
                  AlignWithMargins = True
                  Left = 163
                  Top = 99
                  Width = 233
                  Height = 38
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Align = alClient
                  TabOrder = 2
                  Text = '---'
                  OnChange = ComboBox_MultiUSERSChange
                end
                object Label18: TLabel
                  AlignWithMargins = True
                  Left = 5
                  Top = 5
                  Width = 148
                  Height = 37
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Align = alClient
                  Caption = #1055#1086#1083#1110#1090#1080#1082#1080':'
                  Layout = tlCenter
                  ExplicitWidth = 91
                  ExplicitHeight = 30
                end
                object Label19: TLabel
                  AlignWithMargins = True
                  Left = 5
                  Top = 52
                  Width = 148
                  Height = 37
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Align = alClient
                  Caption = 'USB:'
                  Layout = tlCenter
                  ExplicitWidth = 42
                  ExplicitHeight = 30
                end
                object Label20: TLabel
                  AlignWithMargins = True
                  Left = 5
                  Top = 99
                  Width = 148
                  Height = 37
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Align = alClient
                  Caption = #1050#1086#1088#1080#1089#1090#1091#1074#1072#1095#1110':'
                  Layout = tlCenter
                  ExplicitWidth = 121
                  ExplicitHeight = 30
                end
              end
            end
            object GroupBox7: TGroupBox
              AlignWithMargins = True
              Left = 5
              Top = 190
              Width = 405
              Height = 130
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Anchors = []
              Caption = #1030#1085#1092#1086' '#1087#1088#1086' '#1055#1054' '#1085#1072' '#1040#1056#1052
              TabOrder = 1
              object GridPanel_EditInfoLic: TGridPanel
                Left = 2
                Top = 32
                Width = 401
                Height = 96
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
                    Value = 50.088304136590000000
                  end
                  item
                    Value = 49.911695863410000000
                  end>
                TabOrder = 0
                object Label9: TLabel
                  AlignWithMargins = True
                  Left = 5
                  Top = 5
                  Width = 149
                  Height = 38
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Align = alClient
                  Caption = #1051#1110#1094'. Windows:'
                  ExplicitWidth = 133
                  ExplicitHeight = 30
                end
                object EditLicWin: TComboBox
                  AlignWithMargins = True
                  Left = 164
                  Top = 5
                  Width = 232
                  Height = 38
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Align = alClient
                  TabOrder = 0
                  Text = '---'
                  OnChange = EditLicWinChange
                  Items.Strings = (
                    #1040#1082#1090#1080#1074#1086#1074#1072#1085#1072
                    #1053#1077' '#1072#1082#1090#1080#1074#1086#1074#1072#1085#1072
                    'KMS')
                end
                object Label10: TLabel
                  AlignWithMargins = True
                  Left = 9
                  Top = 57
                  Width = 141
                  Height = 30
                  Margins.Left = 9
                  Margins.Top = 9
                  Margins.Right = 9
                  Margins.Bottom = 9
                  Align = alClient
                  Caption = #1051#1110#1094'. Office:'
                  ExplicitWidth = 104
                end
                object EditLicOffice: TComboBox
                  AlignWithMargins = True
                  Left = 164
                  Top = 53
                  Width = 232
                  Height = 38
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Align = alClient
                  TabOrder = 1
                  Text = '---'
                  OnChange = EditLicOfficeChange
                  Items.Strings = (
                    #1040#1082#1090#1080#1074#1086#1074#1072#1085#1072
                    #1053#1077' '#1072#1082#1090#1080#1074#1086#1074#1072#1085#1072
                    'KMS'
                    #1055#1054' '#1074#1110#1076#1089#1091#1090#1085#1077)
                end
              end
            end
            object GroupBox_SPZ: TGroupBox
              AlignWithMargins = True
              Left = 420
              Top = 5
              Width = 247
              Height = 576
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Caption = #1053#1072#1083#1072#1096#1090#1086#1074#1072#1085#1077' '#1057#1055#1047
              TabOrder = 2
              object CheckListBox_SPZ: TCheckListBox
                AlignWithMargins = True
                Left = 7
                Top = 37
                Width = 233
                Height = 532
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                Align = alClient
                ItemHeight = 30
                TabOrder = 0
                OnClickCheck = CheckListBox_SPZClickCheck
              end
            end
          end
        end
      end
      object PageControl_InfoTabs: TPageControl
        AlignWithMargins = True
        Left = 715
        Top = 15
        Width = 686
        Height = 1019
        Margins.Left = 5
        Margins.Top = 5
        Margins.Right = 5
        Margins.Bottom = 5
        ActivePage = TabSheet_Info
        Align = alClient
        TabOrder = 1
        object TabSheet_Info: TTabSheet
          Margins.Left = 5
          Margins.Top = 5
          Margins.Right = 5
          Margins.Bottom = 5
          Caption = #1030#1053#1060#1054
          object GridPanel_Info: TGridPanel
            Left = 0
            Top = 0
            Width = 678
            Height = 974
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
                Control = GroupBox_Number
                Row = 0
              end
              item
                Column = 0
                Control = GroupBox_InfoARM
                Row = 1
              end>
            RowCollection = <
              item
                SizeStyle = ssAbsolute
                Value = 125.000000000000000000
              end
              item
                SizeStyle = ssAbsolute
                Value = 400.000000000000000000
              end
              item
                Value = 100.000000000000000000
              end>
            TabOrder = 0
            object GroupBox_Number: TGroupBox
              AlignWithMargins = True
              Left = 5
              Top = 5
              Width = 668
              Height = 115
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Caption = #1042#1085#1091#1090#1088#1110#1096#1085#1110' '#1085#1086#1084#1077#1088#1072' '#1040#1056#1052':'
              TabOrder = 0
              object GridPanel3: TGridPanel
                Left = 2
                Top = 32
                Width = 664
                Height = 81
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
                    Control = LabEdit_NumUVs
                    Row = 0
                  end
                  item
                    Column = 1
                    Control = LabEdit_NumUVsO
                    Row = 0
                  end
                  item
                    Column = 2
                    Control = LabEdit_NumOK
                    Row = 0
                  end
                  item
                    Column = 3
                    Control = LabEdit_NumOKO
                    Row = 0
                  end>
                RowCollection = <
                  item
                    Value = 100.000000000000000000
                  end>
                TabOrder = 0
                DesignSize = (
                  664
                  81)
                object LabEdit_NumUVs: TLabeledEdit
                  Left = 8
                  Top = 35
                  Width = 150
                  Height = 38
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = [akLeft, akTop, akRight]
                  EditLabel.Width = 82
                  EditLabel.Height = 30
                  EditLabel.Margins.Left = 5
                  EditLabel.Margins.Top = 5
                  EditLabel.Margins.Right = 5
                  EditLabel.Margins.Bottom = 5
                  EditLabel.Caption = #1059#1042'('#1089') "'#1055'"'
                  EditLabel.Color = clBtnFace
                  EditLabel.Font.Charset = DEFAULT_CHARSET
                  EditLabel.Font.Color = clWindowFrame
                  EditLabel.Font.Height = -21
                  EditLabel.Font.Name = 'Segoe UI'
                  EditLabel.Font.Style = [fsItalic]
                  EditLabel.ParentColor = False
                  EditLabel.ParentFont = False
                  NumbersOnly = True
                  ReadOnly = True
                  TabOrder = 0
                  Text = ''
                end
                object LabEdit_NumUVsO: TLabeledEdit
                  Left = 174
                  Top = 35
                  Width = 150
                  Height = 38
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = [akLeft, akTop, akRight]
                  EditLabel.Width = 144
                  EditLabel.Height = 30
                  EditLabel.Margins.Left = 5
                  EditLabel.Margins.Top = 5
                  EditLabel.Margins.Right = 5
                  EditLabel.Margins.Bottom = 5
                  EditLabel.Caption = #1059#1042'('#1089')"'#1055'" '#1054#1043#1088#1051#1047
                  EditLabel.Font.Charset = DEFAULT_CHARSET
                  EditLabel.Font.Color = clWindowFrame
                  EditLabel.Font.Height = -21
                  EditLabel.Font.Name = 'Segoe UI'
                  EditLabel.Font.Style = [fsItalic]
                  EditLabel.ParentFont = False
                  NumbersOnly = True
                  ReadOnly = True
                  TabOrder = 1
                  Text = ''
                end
                object LabEdit_NumOK: TLabeledEdit
                  Left = 340
                  Top = 35
                  Width = 150
                  Height = 38
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = [akLeft, akTop, akRight]
                  EditLabel.Width = 60
                  EditLabel.Height = 30
                  EditLabel.Margins.Left = 5
                  EditLabel.Margins.Top = 5
                  EditLabel.Margins.Right = 5
                  EditLabel.Margins.Bottom = 5
                  EditLabel.Caption = #1054#1050'"'#1055'"'
                  EditLabel.Font.Charset = DEFAULT_CHARSET
                  EditLabel.Font.Color = clWindowFrame
                  EditLabel.Font.Height = -21
                  EditLabel.Font.Name = 'Segoe UI'
                  EditLabel.Font.Style = [fsItalic]
                  EditLabel.ParentFont = False
                  NumbersOnly = True
                  ReadOnly = True
                  TabOrder = 2
                  Text = ''
                end
                object LabEdit_NumOKO: TLabeledEdit
                  Left = 506
                  Top = 35
                  Width = 150
                  Height = 38
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = [akLeft, akTop, akRight]
                  EditLabel.Width = 128
                  EditLabel.Height = 30
                  EditLabel.Margins.Left = 5
                  EditLabel.Margins.Top = 5
                  EditLabel.Margins.Right = 5
                  EditLabel.Margins.Bottom = 5
                  EditLabel.Caption = #1054#1050'"'#1055'" '#1054#1043#1088#1051#1047
                  EditLabel.Font.Charset = DEFAULT_CHARSET
                  EditLabel.Font.Color = clWindowFrame
                  EditLabel.Font.Height = -21
                  EditLabel.Font.Name = 'Segoe UI'
                  EditLabel.Font.Style = [fsItalic]
                  EditLabel.ParentFont = False
                  NumbersOnly = True
                  ReadOnly = True
                  TabOrder = 3
                  Text = ''
                end
              end
            end
            object GroupBox_InfoARM: TGroupBox
              AlignWithMargins = True
              Left = 5
              Top = 130
              Width = 668
              Height = 390
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Anchors = []
              Caption = #1030#1085#1092#1086' '#1087#1088#1086' '#1040#1056#1052':'
              TabOrder = 1
              object GridPanel_InfoArm: TGridPanel
                Left = 2
                Top = 32
                Width = 664
                Height = 356
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                Align = alClient
                BevelOuter = bvNone
                ColumnCollection = <
                  item
                    Value = 25.521466109939620000
                  end
                  item
                    Value = 74.478533890060380000
                  end>
                ControlCollection = <
                  item
                    Column = 0
                    Control = Label5
                    Row = 0
                  end
                  item
                    Column = 0
                    Control = Label6
                    Row = 1
                  end
                  item
                    Column = 0
                    Control = Label8
                    Row = 2
                  end
                  item
                    Column = 1
                    Control = ShowSerial
                    Row = 0
                  end
                  item
                    Column = 1
                    Control = ShowName
                    Row = 2
                  end
                  item
                    Column = 1
                    Control = ShowSerialGenarate
                    Row = 1
                  end
                  item
                    Column = 0
                    Control = Label1
                    Row = 3
                  end
                  item
                    Column = 1
                    Control = ShowManufacturer
                    Row = 3
                  end
                  item
                    Column = 0
                    Control = Label4
                    Row = 4
                  end
                  item
                    Column = 1
                    Control = ShowProductName
                    Row = 4
                  end>
                RowCollection = <
                  item
                    Value = 20.000000000000000000
                  end
                  item
                    Value = 20.000000000000000000
                  end
                  item
                    Value = 20.000000000000000000
                  end
                  item
                    Value = 20.000000000000000000
                  end
                  item
                    Value = 20.000000000000000000
                  end>
                TabOrder = 0
                DesignSize = (
                  664
                  356)
                object Label5: TLabel
                  Left = 0
                  Top = 0
                  Width = 169
                  Height = 71
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Align = alClient
                  Alignment = taCenter
                  Caption = #1057#1077#1088#1110#1081#1080#1082' '#1040#1056#1052':'
                  Layout = tlCenter
                  ExplicitWidth = 131
                  ExplicitHeight = 30
                end
                object Label6: TLabel
                  Left = 0
                  Top = 71
                  Width = 169
                  Height = 71
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Align = alClient
                  Alignment = taCenter
                  Caption = #1047#1075#1077#1085#1077#1088#1086#1074#1072#1085#1080#1081#13#10#1089#1077#1088#1110#1081#1085#1080#1082':'
                  Layout = tlCenter
                  ExplicitWidth = 135
                  ExplicitHeight = 60
                end
                object Label8: TLabel
                  Left = 0
                  Top = 142
                  Width = 169
                  Height = 72
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Align = alClient
                  Alignment = taCenter
                  Caption = #1030#1084#39#1103' '#1040#1056#1052':'
                  Layout = tlCenter
                  ExplicitWidth = 93
                  ExplicitHeight = 30
                end
                object ShowSerial: TEdit
                  Left = 176
                  Top = 18
                  Width = 480
                  Height = 35
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = []
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
                  Left = 176
                  Top = 160
                  Width = 480
                  Height = 35
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = []
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
                object ShowSerialGenarate: TEdit
                  Left = 176
                  Top = 89
                  Width = 480
                  Height = 35
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = []
                  Font.Charset = DEFAULT_CHARSET
                  Font.Color = clWindowText
                  Font.Height = -23
                  Font.Name = 'Consolas'
                  Font.Style = []
                  ParentFont = False
                  ReadOnly = True
                  TabOrder = 2
                  Text = 'ShowSerialGenarate'
                  OnDblClick = ShowSerialGenarateDblClick
                end
                object Label1: TLabel
                  Left = 0
                  Top = 214
                  Width = 169
                  Height = 71
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Align = alClient
                  Alignment = taCenter
                  Caption = #1042#1080#1088#1086#1073#1085#1080#1082':'
                  Layout = tlCenter
                  ExplicitWidth = 99
                  ExplicitHeight = 30
                end
                object ShowManufacturer: TEdit
                  AlignWithMargins = True
                  Left = 176
                  Top = 232
                  Width = 480
                  Height = 35
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = []
                  Font.Charset = DEFAULT_CHARSET
                  Font.Color = clWindowText
                  Font.Height = -23
                  Font.Name = 'Consolas'
                  Font.Style = []
                  ParentFont = False
                  ReadOnly = True
                  TabOrder = 3
                  Text = 'ShowManufacturer'
                end
                object Label4: TLabel
                  Left = 0
                  Top = 285
                  Width = 169
                  Height = 71
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Align = alClient
                  Alignment = taCenter
                  Caption = #1052#1086#1076#1077#1083#1100':'
                  Layout = tlCenter
                  ExplicitWidth = 80
                  ExplicitHeight = 30
                end
                object ShowProductName: TEdit
                  Left = 176
                  Top = 303
                  Width = 480
                  Height = 35
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Anchors = []
                  Font.Charset = DEFAULT_CHARSET
                  Font.Color = clWindowText
                  Font.Height = -23
                  Font.Name = 'Consolas'
                  Font.Style = []
                  ParentFont = False
                  ReadOnly = True
                  TabOrder = 4
                  Text = 'ShowProductName'
                end
              end
            end
          end
        end
        object TabSheet_CheckList: TTabSheet
          Margins.Left = 5
          Margins.Top = 5
          Margins.Right = 5
          Margins.Bottom = 5
          Caption = #1055#1077#1088#1077#1074#1110#1088#1082#1080
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -21
          Font.Name = 'Segoe UI'
          Font.Style = []
          ImageIndex = 4
          ParentFont = False
          object GridPanel_CheckInfo: TGridPanel
            Left = 0
            Top = 0
            Width = 678
            Height = 974
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
                Control = GridPanel_ESETQuarantine
                Row = 0
              end
              item
                Column = 0
                Control = Label_DefectionUser
                Row = 1
              end
              item
                Column = 0
                Control = Memo2
                Row = 2
              end
              item
                Column = 0
                Control = Label_DefectionSoft
                Row = 3
              end
              item
                Column = 0
                Control = Memo1
                Row = 4
              end
              item
                Column = 0
                Control = Button_CheckDefection
                Row = 6
              end>
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWhite
            Font.Height = -21
            Font.Name = 'Segoe UI'
            Font.Style = []
            ParentFont = False
            RowCollection = <
              item
                SizeStyle = ssAbsolute
                Value = 50.000000000000000000
              end
              item
                SizeStyle = ssAbsolute
                Value = 50.000000000000000000
              end
              item
                SizeStyle = ssAbsolute
                Value = 160.000000000000000000
              end
              item
                SizeStyle = ssAbsolute
                Value = 50.000000000000000000
              end
              item
                SizeStyle = ssAbsolute
                Value = 160.000000000000000000
              end
              item
                Value = 100.000000000000000000
              end
              item
                SizeStyle = ssAbsolute
                Value = 80.000000000000000000
              end>
            TabOrder = 0
            object GridPanel_ESETQuarantine: TGridPanel
              Left = 0
              Top = 0
              Width = 678
              Height = 50
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              BevelOuter = bvNone
              ColumnCollection = <
                item
                  Value = 58.070761609198890000
                end
                item
                  Value = 41.929238390801110000
                end>
              ControlCollection = <
                item
                  Column = 0
                  Control = Label_checkQuarantineEset_1
                  Row = 0
                end
                item
                  Column = 1
                  Control = Show_ESETQuarantine
                  Row = 0
                end>
              RowCollection = <
                item
                  Value = 100.000000000000000000
                end
                item
                  SizeStyle = ssAuto
                end>
              TabOrder = 0
              DesignSize = (
                678
                50)
              object Label_checkQuarantineEset_1: TLabel
                AlignWithMargins = True
                Left = 5
                Top = 5
                Width = 384
                Height = 40
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                Align = alClient
                Caption = #1047#1085#1072#1081#1076#1077#1085#1085#1086' '#1092#1072#1081#1083#1110#1074' '#1074' '#1082#1072#1088#1072#1085#1090#1080#1085#1110' ESET:'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -21
                Font.Name = 'Segoe UI'
                Font.Style = []
                ParentFont = False
                Layout = tlCenter
                StyleElements = [seClient, seBorder]
                ExplicitWidth = 346
                ExplicitHeight = 30
              end
              object Show_ESETQuarantine: TEdit
                AlignWithMargins = True
                Left = 401
                Top = 6
                Width = 270
                Height = 38
                Hint = '12312321'
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                Anchors = []
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -21
                Font.Name = 'Segoe UI'
                Font.Style = []
                ParentFont = False
                ParentShowHint = False
                ReadOnly = True
                ShowHint = True
                TabOrder = 0
                Text = '[WIP] ESETQuarantine'
              end
            end
            object Label_DefectionUser: TLabel
              AlignWithMargins = True
              Left = 5
              Top = 55
              Width = 668
              Height = 40
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Caption = #1055#1086#1090#1086#1095#1085#1110' '#1082#1086#1088#1080#1089#1090#1091#1074#1072#1095#1110' '#1040#1056#1052':'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clWindowText
              Font.Height = -21
              Font.Name = 'Segoe UI'
              Font.Style = []
              ParentFont = False
              Layout = tlBottom
              StyleElements = [seClient, seBorder]
              ExplicitWidth = 253
              ExplicitHeight = 30
            end
            object Memo2: TMemo
              AlignWithMargins = True
              Left = 5
              Top = 105
              Width = 668
              Height = 150
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clWindowText
              Font.Height = -21
              Font.Name = 'Consolas'
              Font.Style = []
              ParentFont = False
              ReadOnly = True
              ScrollBars = ssVertical
              TabOrder = 1
            end
            object Label_DefectionSoft: TLabel
              AlignWithMargins = True
              Left = 5
              Top = 265
              Width = 668
              Height = 40
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Caption = #1047#1072#1073#1086#1088#1086#1085#1077#1085#1080#1081' '#1089#1086#1092#1090':'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clWindowText
              Font.Height = -21
              Font.Name = 'Segoe UI'
              Font.Style = []
              ParentFont = False
              Layout = tlBottom
              StyleElements = [seClient, seBorder]
              ExplicitWidth = 185
              ExplicitHeight = 30
            end
            object Memo1: TMemo
              AlignWithMargins = True
              Left = 5
              Top = 315
              Width = 668
              Height = 150
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clWindowText
              Font.Height = -21
              Font.Name = 'Consolas'
              Font.Style = []
              ParentFont = False
              ReadOnly = True
              ScrollBars = ssVertical
              TabOrder = 2
              WordWrap = False
            end
            object Button_CheckDefection: TButton
              AlignWithMargins = True
              Left = 5
              Top = 899
              Width = 668
              Height = 70
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Caption = #1055#1086#1074#1090#1086#1088#1085#1072' '#1087#1077#1088#1077#1074#1110#1088#1082#1072
              TabOrder = 3
              OnClick = Button_CheckDefectionClick
            end
          end
        end
        object TabSheet_Log: TTabSheet
          Margins.Left = 5
          Margins.Top = 5
          Margins.Right = 5
          Margins.Bottom = 5
          Caption = #1051#1086#1075' '#1043#1088#1072#1073#1072
          ImageIndex = 1
          object RichEdit_LOG: TRichEdit
            AlignWithMargins = True
            Left = 5
            Top = 5
            Width = 668
            Height = 964
            Margins.Left = 5
            Margins.Top = 5
            Margins.Right = 5
            Margins.Bottom = 5
            Align = alClient
            Font.Charset = RUSSIAN_CHARSET
            Font.Color = clWindowText
            Font.Height = -21
            Font.Name = 'Consolas'
            Font.Style = []
            ParentFont = False
            ReadOnly = True
            ScrollBars = ssBoth
            TabOrder = 0
          end
        end
        object TabSheet_Soft: TTabSheet
          Margins.Left = 5
          Margins.Top = 5
          Margins.Right = 5
          Margins.Bottom = 5
          Caption = #1059#1090#1110#1083#1110#1090#1080
          ImageIndex = 3
          object GridPanel_Soft: TGridPanel
            Left = 0
            Top = 0
            Width = 678
            Height = 974
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
                Row = 5
              end
              item
                Column = 0
                Control = GroupBox_SettingsPC
                Row = 3
              end
              item
                Column = 0
                Control = GroupBox_ConsoleUtil
                Row = 4
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
                SizeStyle = ssAbsolute
                Value = 254.000000000000000000
              end
              item
                SizeStyle = ssAbsolute
                Value = 114.000000000000000000
              end
              item
                Value = 100.000000000000000000
              end>
            TabOrder = 0
            object GroupBox_AppInfo: TGroupBox
              AlignWithMargins = True
              Left = 5
              Top = 5
              Width = 668
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
                Width = 664
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
                  Width = 322
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
                  Left = 337
                  Top = 5
                  Width = 322
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
                  Width = 322
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
                  Left = 337
                  Top = 75
                  Width = 322
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
                  Width = 322
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
                  Left = 337
                  Top = 145
                  Width = 322
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
              Width = 668
              Height = 104
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Caption = #1060#1072#1081#1083#1086#1074#1072' '#1089#1080#1089#1090#1077#1084#1072
              TabOrder = 1
              object GridPanel10: TGridPanel
                Left = 2
                Top = 32
                Width = 664
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
                object BtnApp_Total: TButton
                  AlignWithMargins = True
                  Left = 5
                  Top = 5
                  Width = 322
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
                  Left = 337
                  Top = 5
                  Width = 322
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
              Width = 668
              Height = 174
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Caption = 'USB '#1087#1088#1080#1089#1090#1088#1086#1111
              TabOrder = 2
              object GridPanel14: TGridPanel
                Left = 2
                Top = 32
                Width = 664
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
                  Width = 322
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
                  Left = 337
                  Top = 5
                  Width = 322
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
                  Width = 322
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
                  Left = 337
                  Top = 75
                  Width = 322
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
              AlignWithMargins = True
              Left = 5
              Top = 925
              Width = 668
              Height = 44
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Caption = #1047#1072#1087#1091#1089#1090#1080#1090#1080' '#1089' '#1087#1088#1072#1074#1072#1084#1080' '#1072#1076#1084#1110#1085#1110#1089#1090#1088#1072#1090#1086#1088#1072
              Checked = True
              State = cbChecked
              TabOrder = 3
            end
            object GroupBox_SettingsPC: TGroupBox
              AlignWithMargins = True
              Left = 5
              Top = 557
              Width = 668
              Height = 244
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Caption = #1057#1080#1089#1090#1077#1084#1085#1110' '#1091#1090#1110#1083#1110#1090#1080
              TabOrder = 4
              object GridPanel_SettingsPC: TGridPanel
                Left = 2
                Top = 32
                Width = 664
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
                    Control = BtnKiberConsolOpen
                    Row = 0
                  end
                  item
                    Column = 1
                    Control = Button_ControlPanel
                    Row = 0
                  end
                  item
                    Column = 0
                    Control = Button_setingsPC
                    Row = 1
                  end
                  item
                    Column = 1
                    Control = Button_msconfig
                    Row = 1
                  end
                  item
                    Column = 0
                    Control = Button_CrashMonitor
                    Row = 2
                  end
                  item
                    Column = 1
                    Control = Button_ResMon
                    Row = 2
                  end>
                RowCollection = <
                  item
                    Value = 33.363493834353250000
                  end
                  item
                    Value = 33.300000000000000000
                  end
                  item
                    Value = 33.336506165646750000
                  end>
                TabOrder = 0
                object BtnKiberConsolOpen: TButton
                  AlignWithMargins = True
                  Left = 5
                  Top = 5
                  Width = 322
                  Height = 60
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Align = alClient
                  Caption = #1042#1110#1076#1082#1088#1080#1090#1080' '#1050#1086#1085#1089#1086#1083#1100
                  TabOrder = 0
                  OnClick = BtnKiberConsolOpenClick
                end
                object Button_ControlPanel: TButton
                  AlignWithMargins = True
                  Left = 337
                  Top = 5
                  Width = 322
                  Height = 60
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Align = alClient
                  Caption = #1055#1072#1085#1077#1083#1100' '#1082#1077#1088#1091#1074#1072#1085#1103
                  TabOrder = 1
                  OnClick = Button_ControlPanelClick
                end
                object Button_setingsPC: TButton
                  AlignWithMargins = True
                  Left = 5
                  Top = 75
                  Width = 322
                  Height = 60
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Align = alClient
                  Caption = #1042#1083#1072#1089#1090#1080#1074#1086#1089#1090#1110' '#1089#1080#1089#1090#1077#1084#1080
                  TabOrder = 2
                  OnClick = Button_setingsPCClick
                end
                object Button_msconfig: TButton
                  AlignWithMargins = True
                  Left = 337
                  Top = 75
                  Width = 322
                  Height = 60
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Align = alClient
                  Caption = 'MSconfig'
                  TabOrder = 3
                  OnClick = Button_msconfigClick
                end
                object Button_CrashMonitor: TButton
                  AlignWithMargins = True
                  Left = 5
                  Top = 145
                  Width = 322
                  Height = 60
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Align = alClient
                  Caption = #1052#1086#1085#1110#1090#1086#1088' '#1089#1090#1072#1073#1110#1083#1100#1085#1086#1089#1090#1110
                  TabOrder = 4
                  OnClick = Button_CrashMonitorClick
                end
                object Button_ResMon: TButton
                  AlignWithMargins = True
                  Left = 337
                  Top = 145
                  Width = 322
                  Height = 60
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Align = alClient
                  Caption = #1052#1086#1085#1110#1090#1086#1088' '#1088#1077#1089#1091#1088#1089#1110#1074
                  TabOrder = 5
                  OnClick = Button_ResMonClick
                end
              end
            end
            object GroupBox_ConsoleUtil: TGroupBox
              AlignWithMargins = True
              Left = 5
              Top = 811
              Width = 668
              Height = 104
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Caption = #1050#1086#1085#1089#1086#1083#1100#1085#1110' '#1091#1090#1110#1083#1110#1090#1080
              TabOrder = 5
              object GridPanel_ConsoleUtil: TGridPanel
                Left = 2
                Top = 32
                Width = 664
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
                    Control = BtnInfo
                    Row = 0
                  end
                  item
                    Column = 1
                    Control = BtnLicense
                    Row = 0
                  end>
                RowCollection = <
                  item
                    Value = 100.000000000000000000
                  end>
                TabOrder = 0
                object BtnInfo: TButton
                  AlignWithMargins = True
                  Left = 5
                  Top = 5
                  Width = 322
                  Height = 60
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Align = alClient
                  Caption = #1030#1053#1060#1054
                  TabOrder = 0
                  OnClick = BtnInfoClick
                end
                object BtnLicense: TButton
                  AlignWithMargins = True
                  Left = 337
                  Top = 5
                  Width = 322
                  Height = 60
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Align = alClient
                  Caption = #1051#1110#1094#1077#1085#1079#1110#1111
                  TabOrder = 1
                  OnClick = BtnLicenseClick
                end
              end
            end
          end
        end
        object TabSheet_Settings: TTabSheet
          Margins.Left = 5
          Margins.Top = 5
          Margins.Right = 5
          Margins.Bottom = 5
          Caption = #1053#1072#1083#1072#1096#1090#1091#1074#1072#1085#1085#1103
          ImageIndex = 2
          object GridPanel_Settings: TGridPanel
            Left = 0
            Top = 0
            Width = 678
            Height = 974
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
                Control = GroupBox_SetingsGRUB
                Row = 0
              end
              item
                Column = 0
                Control = GroupBox_SetingsESET
                Row = 1
              end
              item
                Column = 0
                Control = GridPanel15
                Row = 3
              end
              item
                Column = 0
                Control = GroupBox1
                Row = 2
              end>
            RowCollection = <
              item
                SizeStyle = ssAbsolute
                Value = 440.000000000000000000
              end
              item
                SizeStyle = ssAbsolute
                Value = 180.000000000000000000
              end
              item
                Value = 100.000000000000000000
              end
              item
                SizeStyle = ssAbsolute
                Value = 110.000000000000000000
              end>
            TabOrder = 0
            object GroupBox_SetingsGRUB: TGroupBox
              AlignWithMargins = True
              Left = 5
              Top = 5
              Width = 668
              Height = 430
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Caption = #1053#1072#1083#1072#1096#1090#1091#1074#1072#1085#1085#1103' '#1089#1073#1086#1088#1091' GRUBer'#39#1072
              TabOrder = 0
              object Label_ForNumberARM: TLabel
                Left = 19
                Top = 380
                Width = 328
                Height = 30
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                Caption = #1042#1080#1082#1086#1088#1080#1089#1090#1086#1074#1091#1074#1072#1090#1080' '#1085#1086#1084#1077#1088' '#1040#1056#1052' '#1076#1083#1103':'
              end
              object CheckBoxDebug: TCheckBox
                Left = 397
                Top = 133
                Width = 221
                Height = 29
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                Caption = #1044#1077#1073#1072#1075'-'#1110#1085#1092#1086
                Checked = True
                State = cbChecked
                TabOrder = 0
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
                TabOrder = 1
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
                TabOrder = 2
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
                TabOrder = 3
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
                TabOrder = 4
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
                TabOrder = 5
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
                TabOrder = 6
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
                TabOrder = 7
                OnClick = BtnEditPartitionClick
              end
              object CheckBox_ShowEsetUpdate: TCheckBox
                Left = 397
                Top = 172
                Width = 263
                Height = 30
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                Caption = #1054#1082#1085#1086' '#1086#1085#1086#1074#1083#1077#1085#1085#1103' ESET'
                TabOrder = 8
                OnClick = CheckBox_ShowEsetUpdateClick
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
                TabOrder = 9
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
                TabOrder = 10
                OnClick = CheckBoxPrefixPartitionClick
              end
              object ComboBox_forNumberARM: TComboBox
                Left = 357
                Top = 376
                Width = 293
                Height = 38
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                Style = csDropDownList
                ItemIndex = 0
                TabOrder = 11
                Text = #1053#1077' '#1074#1082#1072#1079#1072#1085#1086
                OnChange = ComboBox_forNumberARMChange
                Items.Strings = (
                  #1053#1077' '#1074#1082#1072#1079#1072#1085#1086
                  #1059#1042'('#1089') "'#1055#1110#1074#1076#1077#1085#1100'"'
                  #1059#1042'('#1089') "'#1055#1110#1074#1076#1077#1085#1100'" - '#1054#1043#1088#1051#1047' '
                  #1054#1050' "'#1055#1110#1074#1076#1077#1085#1100'"'
                  #1054#1050' "'#1055#1110#1074#1076#1077#1085#1100'" - '#1054#1043#1088#1051#1047' ')
              end
              object CheckBox_TempDir: TCheckBox
                Left = 397
                Top = 212
                Width = 248
                Height = 30
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                Caption = 'CheckBox_TempDir'
                TabOrder = 12
              end
            end
            object GroupBox_SetingsESET: TGroupBox
              AlignWithMargins = True
              Left = 5
              Top = 445
              Width = 668
              Height = 170
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
              Top = 864
              Width = 678
              Height = 110
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
                  Column = 1
                  Control = BtnAboutGruber
                  Row = 1
                end
                item
                  Column = 0
                  Control = Button_RestartAssAdmin
                  Row = 1
                end
                item
                  Column = 0
                  ColumnSpan = 2
                  Control = BtnSaveSetteings
                  Row = 0
                end>
              RowCollection = <
                item
                  Value = 50.000000000000000000
                end
                item
                  Value = 50.000000000000000000
                end>
              TabOrder = 2
              object BtnAboutGruber: TButton
                AlignWithMargins = True
                Left = 344
                Top = 60
                Width = 329
                Height = 45
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
                Left = 5
                Top = 60
                Width = 329
                Height = 45
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                Align = alClient
                Caption = #1055#1077#1088#1077#1079#1072#1087#1091#1089#1090#1080#1090#1080' '#1074#1110#1076' '#1040#1076#1084#1110#1085#1072
                TabOrder = 1
                OnClick = Button_RestartAssAdminClick
              end
              object BtnSaveSetteings: TButton
                AlignWithMargins = True
                Left = 5
                Top = 5
                Width = 668
                Height = 45
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                Align = alClient
                Caption = #1047#1073#1077#1088#1077#1075#1090#1080' '#1085#1072#1083#1072#1096#1090#1091#1074#1072#1085#1085#1103
                TabOrder = 2
                OnClick = BtnSaveSetteingsClick
              end
            end
            object GroupBox1: TGroupBox
              AlignWithMargins = True
              Left = 5
              Top = 625
              Width = 668
              Height = 234
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Caption = #1053#1072#1083#1072#1096#1090#1091#1074#1072#1085#1103' '#1055#1054
              TabOrder = 3
              object GridPanel4: TGridPanel
                Left = 2
                Top = 32
                Width = 664
                Height = 200
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                Align = alClient
                BevelOuter = bvNone
                ColumnCollection = <
                  item
                    Value = 30.747922437673130000
                  end
                  item
                    Value = 69.252077562326870000
                  end>
                ControlCollection = <
                  item
                    Column = 0
                    Control = Label12
                    Row = 0
                  end
                  item
                    Column = 1
                    Control = ComboBox_ThemeChange
                    Row = 0
                  end>
                RowCollection = <
                  item
                    SizeStyle = ssAbsolute
                    Value = 48.000000000000000000
                  end
                  item
                    Value = 100.000000000000000000
                  end>
                TabOrder = 0
                object Label12: TLabel
                  AlignWithMargins = True
                  Left = 5
                  Top = 5
                  Width = 194
                  Height = 38
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Align = alClient
                  Caption = #1058#1077#1084#1072' '#1074#1110#1082#1085#1072':'
                  ExplicitWidth = 108
                  ExplicitHeight = 30
                end
                object ComboBox_ThemeChange: TComboBox
                  AlignWithMargins = True
                  Left = 209
                  Top = 5
                  Width = 450
                  Height = 38
                  Margins.Left = 5
                  Margins.Top = 5
                  Margins.Right = 5
                  Margins.Bottom = 5
                  Align = alClient
                  Style = csDropDownList
                  Enabled = False
                  ItemIndex = 0
                  TabOrder = 0
                  Text = #1057#1074#1110#1090#1083#1072' '#1090#1077#1084#1072
                  Items.Strings = (
                    #1057#1074#1110#1090#1083#1072' '#1090#1077#1084#1072
                    #1058#1077#1084#1085#1072' '#1090#1077#1084#1072)
                end
              end
            end
          end
        end
      end
      object ProgressBar_Grub: TProgressBar
        AlignWithMargins = True
        Left = 15
        Top = 966
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
      end
      object GridPanel_forButGrub: TGridPanel
        Left = 10
        Top = 661
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
            Row = 2
          end
          item
            Column = 1
            Control = BtnParserOpen
            Row = 2
          end
          item
            Column = 0
            Control = BtnGruberRun
            Row = 3
          end
          item
            Column = 1
            Control = BtnGruberStop
            Row = 3
          end
          item
            Column = 0
            Control = BtnEsetUpdate
            Row = 1
          end
          item
            Column = 1
            Control = BtnClearPC
            Row = 1
          end>
        RowCollection = <
          item
            SizeStyle = ssAbsolute
            Value = 44.000000000000000000
          end
          item
            Value = 33.389834485146790000
          end
          item
            Value = 33.321420452340340000
          end
          item
            Value = 33.288745062512870000
          end>
        TabOrder = 3
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
          Color = clBtnFace
          TabOrder = 0
          Text = 'EditDirGrubName'
          StyleElements = [seBorder]
          OnChange = EditDirGrubNameChange
          ExplicitHeight = 38
        end
        object BtnGruberDirOpen: TButton
          AlignWithMargins = True
          Left = 5
          Top = 131
          Width = 335
          Height = 72
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
        end
        object BtnParserOpen: TButton
          AlignWithMargins = True
          Left = 350
          Top = 131
          Width = 335
          Height = 72
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
        end
        object BtnGruberRun: TButton
          AlignWithMargins = True
          Left = 5
          Top = 213
          Width = 335
          Height = 72
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
        end
        object BtnGruberStop: TButton
          AlignWithMargins = True
          Left = 350
          Top = 213
          Width = 335
          Height = 72
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
        end
        object BtnEsetUpdate: TButton
          AlignWithMargins = True
          Left = 5
          Top = 49
          Width = 335
          Height = 72
          Margins.Left = 5
          Margins.Top = 5
          Margins.Right = 5
          Margins.Bottom = 5
          Align = alClient
          Caption = #1054#1085#1086#1074#1080#1090#1080' ESET'
          Enabled = False
          TabOrder = 5
          OnClick = BtnEsetUpdateClick
        end
        object BtnClearPC: TButton
          AlignWithMargins = True
          Left = 350
          Top = 49
          Width = 335
          Height = 72
          Margins.Left = 5
          Margins.Top = 5
          Margins.Right = 5
          Margins.Bottom = 5
          Align = alClient
          Caption = #1054#1095#1080#1089#1090#1082#1072' '#1090#1080#1084'.'#1092#1072#1081#1083#1110#1074
          Enabled = False
          TabOrder = 6
          OnClick = BtnClearPCClick
        end
      end
    end
    object StatusBar1: TStatusBar
      Left = 0
      Top = 1049
      Width = 1416
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
          Text = ' GRUBer '#1085#1077' '#1079#1072#1087#1091#1089#1082#1072#1074#1089#1103
          Width = 350
        end
        item
          Text = ' '#1041#1072#1079#1080' '#1085#1077' '#1086#1085#1086#1074#1083#1102#1074#1072#1083#1080#1089#1103
          Width = 350
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
    Left = 1073
    Top = 726
  end
  object Taskbar1: TTaskbar
    TaskBarButtons = <>
    ProgressState = Normal
    ProgressMaxValue = 100
    TabProperties = []
    Left = 1258
    Top = 730
  end
  object PopupMenu_StopGrub: TPopupMenu
    Left = 835
    Top = 733
    object Рass: TMenuItem
      Caption = #1055#1088#1086#1087#1091#1089#1082' '#1082#1088#1086#1082#1091
      OnClick = РassClick
    end
  end
  object PopupMenu_mailGrubFile: TPopupMenu
    AutoLineReduction = maManual
    Left = 1082
    Top = 831
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
    Left = 835
    Top = 831
    object Gruber_Mini: TMenuItem
      Caption = #1054#1085#1086#1074#1080#1090#1080' '#1076#1072#1085#1085#1110
      OnClick = Gruber_MiniClick
    end
    object Gruber_USB: TMenuItem
      Caption = #1054#1085#1086#1074#1080#1090#1080' USB'
      OnClick = Gruber_USBClick
    end
  end
end
