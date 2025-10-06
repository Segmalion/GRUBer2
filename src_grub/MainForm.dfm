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
  ClientHeight = 1062
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
  PixelsPerInch = 168
  TextHeight = 30
  object GridPanelMain: TGridPanel
    Left = 0
    Top = 0
    Width = 1416
    Height = 1062
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
      Height = 1009
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
        Height = 591
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
            Height = 546
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
            DesignSize = (
              672
              546)
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
              Caption = #1055#1110#1076#1088#1086#1079#1076#1110#1083':'
              Layout = tlCenter
              ExplicitWidth = 96
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
              Caption = #1050#1072#1090#1077#1075#1086#1088#1110#1103':'
              Layout = tlCenter
              ExplicitWidth = 96
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
              Caption = #1055#1086#1090'.'#1074#1110#1076#1087#1086#1074#1110#1076'.:'
              Layout = tlCenter
              ExplicitWidth = 129
              ExplicitHeight = 30
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
              TabOrder = 0
              Text = #1041#1077#1079' '#1074#1110#1076#1076#1110#1083#1091
              OnChange = EditPartitionChange
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
              Top = 117
              Width = 220
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
              TabOrder = 1
              Text = #1041#1077#1079' '#1082#1083#1072#1089#1091
              OnChange = EditArmClassChange
              Items.Strings = (
                #1041#1077#1079' '#1082#1083#1072#1089#1091
                #1040#1057'-1'
                #1040#1057'-2'
                #1040#1057'-3')
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
              TabOrder = 3
              OnChange = EditResponChange
              ExplicitHeight = 38
            end
            object EditComent: TMemo
              AlignWithMargins = True
              Left = 9
              Top = 441
              Width = 654
              Height = 40
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
              Width = 220
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
              Left = 243
              Top = 225
              Width = 420
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
              Width = 220
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
              Width = 220
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
              Left = 243
              Top = 334
              Width = 420
              Height = 38
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Anchors = []
              TabOrder = 6
              Text = 'Edit_Place'
              OnChange = Edit_PlaceChange
            end
            object Edit_Phone: TEdit
              AlignWithMargins = True
              Left = 243
              Top = 388
              Width = 420
              Height = 38
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Anchors = []
              TabOrder = 7
              Text = 'Edit_Phone'
              OnChange = Edit_PhoneChange
            end
            object Label_NumberARM: TLabel
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
              Left = 238
              Top = 4
              Width = 430
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
                Width = 160
                Height = 40
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                Align = alClient
                Anchors = []
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
                Left = 175
                Top = 5
                Width = 250
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
          object GridPanel11: TGridPanel
            Left = 0
            Top = 0
            Width = 672
            Height = 546
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
              546)
            object Label11: TLabel
              AlignWithMargins = True
              Left = 5
              Top = 19
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
              Top = 15
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
              Top = 87
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
              Top = 83
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
              Top = 155
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
              Top = 151
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
              Top = 224
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
              Top = 220
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
              Top = 292
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
              Top = 288
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
              Top = 360
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
              Top = 356
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
              Top = 428
              Width = 153
              Height = 30
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Anchors = [akLeft]
              Caption = #1042#1110#1076#1087#1086#1074#1110#1076#1072#1083#1100#1085#1080#1081':'
            end
            object Edit_InRespon: TEdit
              AlignWithMargins = True
              Left = 278
              Top = 424
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
              Top = 493
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
              Top = 497
              Width = 145
              Height = 30
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Anchors = [akLeft]
              Caption = #1040#1076#1084#1110#1085' '#1041#1077#1079#1087#1077#1082#1080':'
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
            Height = 546
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
            object GroupBox6: TGroupBox
              AlignWithMargins = True
              Left = 5
              Top = 5
              Width = 662
              Height = 263
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Caption = #1053#1072#1083#1072#1096#1090#1091#1074#1072#1085#1085#1103' '#1073#1077#1079#1087#1077#1082#1080' '#1040#1056#1052
              TabOrder = 0
              object GridPanel12: TGridPanel
                Left = 2
                Top = 32
                Width = 658
                Height = 229
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
                  658
                  229)
                object CheckBox_PoliticInstall: TCheckBox
                  AlignWithMargins = True
                  Left = 5
                  Top = 24
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
                  Left = 268
                  Top = 19
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
                  Top = 100
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
                  Left = 268
                  Top = 95
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
                  Top = 176
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
                  Left = 268
                  Top = 172
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
              Top = 278
              Width = 662
              Height = 263
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
                Height = 229
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
                  229)
                object Label9: TLabel
                  AlignWithMargins = True
                  Left = 5
                  Top = 42
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
                  Top = 38
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
                  Top = 157
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
                  Top = 153
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
      object PageControl_InfoTabs: TPageControl
        AlignWithMargins = True
        Left = 715
        Top = 15
        Width = 686
        Height = 979
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
          Caption = #1047#1072#1075#1072#1083#1100#1085#1072' '#1030#1053#1060#1054
          DesignSize = (
            678
            934)
          object GroupBox_Info: TGroupBox
            Left = 5
            Top = 5
            Width = 664
            Height = 195
            Margins.Left = 5
            Margins.Top = 5
            Margins.Right = 5
            Margins.Bottom = 5
            Align = alCustom
            Anchors = []
            Caption = #1030#1085#1092#1086' '#1087#1086' '#1040#1056#1052
            TabOrder = 0
            object GridPanel6: TGridPanel
              Left = 2
              Top = 32
              Width = 660
              Height = 161
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              BevelOuter = bvNone
              ColumnCollection = <
                item
                  Value = 24.439332154174110000
                end
                item
                  Value = 75.560667845825890000
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
              DesignSize = (
                660
                161)
              object ShowSerial: TEdit
                Left = 235
                Top = 21
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
                Left = 235
                Top = 101
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
                Width = 151
                Height = 68
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                Align = alClient
                Caption = #1057#1077#1088#1110#1081#1085#1080#1082':'
                TabOrder = 2
                OnClick = Button_SerialClick
              end
              object Button_ChangeNamePC: TButton
                AlignWithMargins = True
                Left = 5
                Top = 85
                Width = 151
                Height = 67
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                Align = alClient
                Caption = #1030#1084#39#1103' '#1055#1050':'
                Enabled = False
                TabOrder = 3
              end
            end
          end
          object BtnLicense: TButton
            Left = 5
            Top = 210
            Width = 304
            Height = 47
            Margins.Left = 5
            Margins.Top = 5
            Margins.Right = 5
            Margins.Bottom = 5
            Anchors = []
            Caption = #1051#1110#1094#1077#1085#1079#1110#1111
            TabOrder = 1
            OnClick = BtnLicenseClick
          end
          object BtnInfo: TButton
            Left = 336
            Top = 210
            Width = 337
            Height = 44
            Margins.Left = 5
            Margins.Top = 5
            Margins.Right = 5
            Margins.Bottom = 5
            Anchors = []
            Caption = #1030#1053#1060#1054
            TabOrder = 2
            OnClick = BtnInfoClick
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
            Height = 924
            Margins.Left = 5
            Margins.Top = 5
            Margins.Right = 5
            Margins.Bottom = 5
            Align = alClient
            Font.Charset = RUSSIAN_CHARSET
            Font.Color = clWindowText
            Font.Height = -21
            Font.Name = 'Fira Code'
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
            Height = 934
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
                Value = 100.000000000000000000
              end
              item
                SizeStyle = ssAbsolute
                Value = 55.000000000000000000
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
              Top = 884
              Width = 668
              Height = 45
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
            Height = 934
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
                Value = 500.000000000000000000
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
              Width = 668
              Height = 490
              Margins.Left = 5
              Margins.Top = 5
              Margins.Right = 5
              Margins.Bottom = 5
              Align = alClient
              Caption = #1053#1072#1083#1072#1096#1090#1091#1074#1072#1085#1085#1103' GRUBer'#39#1072
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
              object BtnSaveSetteings: TButton
                AlignWithMargins = True
                Left = 19
                Top = 428
                Width = 632
                Height = 51
                Margins.Left = 5
                Margins.Top = 5
                Margins.Right = 5
                Margins.Bottom = 5
                Caption = #1047#1073#1077#1088#1077#1075#1090#1080' '#1085#1072#1083#1072#1096#1090#1091#1074#1072#1085#1085#1103
                TabOrder = 9
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
                TabOrder = 10
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
                TabOrder = 11
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
                TabOrder = 12
                Text = #1053#1077' '#1074#1082#1072#1079#1072#1085#1086
                OnChange = ComboBox_forNumberARMChange
                Items.Strings = (
                  #1053#1077' '#1074#1082#1072#1079#1072#1085#1086
                  #1059#1042'('#1089') "'#1055#1110#1074#1076#1077#1085#1100'"'
                  #1059#1042'('#1089') "'#1055#1110#1074#1076#1077#1085#1100'" - '#1054#1043#1088#1051#1047' '
                  #1054#1050' "'#1055#1110#1074#1076#1077#1085#1100'"'
                  #1054#1050' "'#1055#1110#1074#1076#1077#1085#1100'" - '#1054#1043#1088#1051#1047' ')
              end
            end
            object GroupBox4: TGroupBox
              AlignWithMargins = True
              Left = 5
              Top = 505
              Width = 668
              Height = 373
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
              Top = 883
              Width = 678
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
                Left = 344
                Top = 6
                Width = 328
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
                Width = 328
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
      object ProgressBar_Grub: TProgressBar
        AlignWithMargins = True
        Left = 15
        Top = 926
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
        Top = 621
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
            Value = 48.000000000000000000
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
          Height = 38
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
          Top = 134
          Width = 335
          Height = 70
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
          Top = 134
          Width = 335
          Height = 70
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
          Top = 214
          Width = 335
          Height = 71
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
          Top = 214
          Width = 335
          Height = 71
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
          Top = 53
          Width = 335
          Height = 71
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
          Top = 53
          Width = 335
          Height = 71
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
      Top = 1009
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
    object MiniGrub: TMenuItem
      Caption = #1054#1085#1086#1074#1080#1090#1080' '#1076#1072#1085#1085#1110' ('#1084#1110#1085#1110#1084#1072#1083#1100#1085#1080#1081' '#1075#1088#1072#1073')'
      OnClick = MiniGrubClick
    end
  end
end
