object Form1: TForm1
  Left = 0
  Top = 0
  Margins.Left = 6
  Margins.Top = 6
  Margins.Right = 6
  Margins.Bottom = 6
  Caption = 'DeviceLister'
  ClientHeight = 1107
  ClientWidth = 1574
  Color = clBtnFace
  Constraints.MinHeight = 672
  Constraints.MinWidth = 917
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -21
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poDesigned
  OnDestroy = FormDestroy
  PixelsPerInch = 168
  TextHeight = 30
  object GridPanel_Main: TGridPanel
    Left = 0
    Top = 0
    Width = 1574
    Height = 1107
    Margins.Left = 6
    Margins.Top = 6
    Margins.Right = 6
    Margins.Bottom = 6
    Align = alClient
    BevelOuter = bvNone
    ColumnCollection = <
      item
        Value = 100.000000000000000000
      end>
    ControlCollection = <
      item
        Column = 0
        Control = DBGrid1
        Row = 1
      end
      item
        Column = 0
        Control = GridPanel_Filter
        Row = 0
      end
      item
        Column = 0
        Control = StatusBar1
        Row = 3
      end
      item
        Column = 0
        Control = GridPanel_RunButton
        Row = 2
      end>
    RowCollection = <
      item
        SizeStyle = ssAbsolute
        Value = 251.000000000000000000
      end
      item
        Value = 100.000000000000000000
      end
      item
        SizeStyle = ssAbsolute
        Value = 90.000000000000000000
      end
      item
        SizeStyle = ssAbsolute
        Value = 41.000000000000000000
      end
      item
        SizeStyle = ssAuto
      end>
    TabOrder = 0
    object DBGrid1: TDBGrid
      AlignWithMargins = True
      Left = 6
      Top = 257
      Width = 1556
      Height = 696
      Margins.Left = 6
      Margins.Top = 6
      Margins.Right = 6
      Margins.Bottom = 6
      Align = alClient
      DataSource = DataSource1
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -21
      Font.Name = 'Fira Code'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 0
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -21
      TitleFont.Name = 'Segoe UI'
      TitleFont.Style = []
      OnDrawColumnCell = DBGrid1DrawColumnCell
      OnTitleClick = DBGrid1TitleClick
    end
    object GridPanel_Filter: TGridPanel
      Left = 0
      Top = 0
      Width = 1568
      Height = 251
      Margins.Left = 6
      Margins.Top = 6
      Margins.Right = 6
      Margins.Bottom = 6
      Align = alClient
      BevelOuter = bvLowered
      ColumnCollection = <
        item
          SizeStyle = ssAbsolute
          Value = 70.000000000000000000
        end
        item
          SizeStyle = ssAbsolute
          Value = 300.000000000000000000
        end
        item
          SizeStyle = ssAbsolute
          Value = 300.000000000000000000
        end
        item
          SizeStyle = ssAbsolute
          Value = 300.000000000000000000
        end
        item
          SizeStyle = ssAbsolute
          Value = 300.000000000000000000
        end
        item
          Value = 100.000000000000000000
        end>
      ControlCollection = <
        item
          Column = 2
          Control = ListBox_Filter
          Row = 1
        end
        item
          Column = 2
          Control = Label1
          Row = 0
        end
        item
          Column = 1
          Control = GridPanel_FilterButton
          Row = 0
          RowSpan = 2
        end
        item
          Column = 3
          Control = GroupBox_FilterCheckBox
          Row = 0
          RowSpan = 2
        end
        item
          Column = 4
          Control = GridPanel_Else
          Row = 0
          RowSpan = 2
        end
        item
          Column = 5
          Control = Memo_LOG
          Row = 0
          RowSpan = 2
        end
        item
          Column = 0
          Control = Button_ShowAll
          Row = 0
          RowSpan = 2
        end>
      RowCollection = <
        item
          SizeStyle = ssAbsolute
          Value = 41.000000000000000000
        end
        item
          Value = 100.000000000000000000
        end>
      TabOrder = 1
      object ListBox_Filter: TListBox
        AlignWithMargins = True
        Left = 377
        Top = 48
        Width = 288
        Height = 196
        Margins.Left = 6
        Margins.Top = 6
        Margins.Right = 6
        Margins.Bottom = 6
        Align = alClient
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -21
        Font.Name = 'Fira Code'
        Font.Style = []
        ItemHeight = 25
        Items.Strings = (
          '('#1059#1089#1110' '#1082#1083#1072#1089#1080' '#1087#1088#1080#1089#1090#1088#1086#1111#1074')'
          'USB'
          'WPD'
          'DiskDrive'
          'Volume')
        MultiSelect = True
        ParentFont = False
        TabOrder = 0
        OnClick = ListBox_FilterClick
      end
      object Label1: TLabel
        AlignWithMargins = True
        Left = 377
        Top = 7
        Width = 288
        Height = 29
        Margins.Left = 6
        Margins.Top = 6
        Margins.Right = 6
        Margins.Bottom = 6
        Align = alClient
        Caption = #1060#1110#1083#1100#1090#1088' '#1087#1086' '#1082#1083#1072#1089#1091' '#1087#1088#1080#1089#1090#1088#1086#1102':'
        Layout = tlCenter
        ExplicitWidth = 258
        ExplicitHeight = 30
      end
      object GridPanel_FilterButton: TGridPanel
        Left = 71
        Top = 1
        Width = 300
        Height = 249
        Margins.Left = 6
        Margins.Top = 6
        Margins.Right = 6
        Margins.Bottom = 6
        Align = alClient
        BevelOuter = bvNone
        ColumnCollection = <
          item
            Value = 100.000000000000000000
          end>
        ControlCollection = <
          item
            Column = 0
            Control = Button_FilterContainerID
            Row = 3
          end
          item
            Column = 0
            Control = Button_ShowUnknowUSB
            Row = 1
          end
          item
            Column = 0
            Control = Button_ShowAllert
            Row = 2
          end
          item
            Column = 0
            Control = Button_ShowUSB
            Row = 0
          end>
        RowCollection = <
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
        TabOrder = 1
        object Button_FilterContainerID: TButton
          AlignWithMargins = True
          Left = 6
          Top = 193
          Width = 288
          Height = 50
          Margins.Left = 6
          Margins.Top = 6
          Margins.Right = 6
          Margins.Bottom = 6
          Align = alClient
          Caption = #1042#1110#1076#1110#1073#1088#1072#1090#1080' '#1079#1072' '#1082#1086#1085#1090#1077#1081#1085#1077#1088#1086#1084
          TabOrder = 0
          OnClick = Button_FilterContainerIDClick
        end
        object Button_ShowUnknowUSB: TButton
          AlignWithMargins = True
          Left = 6
          Top = 68
          Width = 288
          Height = 50
          Margins.Left = 6
          Margins.Top = 6
          Margins.Right = 6
          Margins.Bottom = 6
          Align = alClient
          Caption = #1058#1110#1083#1100#1082#1110' '#1085#1077#1074#1110#1076#1086#1084#1110' '#1092#1083#1077#1096#1082#1080
          TabOrder = 1
          OnClick = Button_ShowUnknowUSBClick
        end
        object Button_ShowAllert: TButton
          AlignWithMargins = True
          Left = 6
          Top = 130
          Width = 288
          Height = 51
          Margins.Left = 6
          Margins.Top = 6
          Margins.Right = 6
          Margins.Bottom = 6
          Align = alClient
          Caption = #1058#1110#1083#1100#1082#1080' '#1087#1086#1088#1091#1096#1077#1085#1103
          TabOrder = 2
          OnClick = Button_ShowAllertClick
        end
        object Button_ShowUSB: TButton
          AlignWithMargins = True
          Left = 6
          Top = 6
          Width = 288
          Height = 50
          Margins.Left = 6
          Margins.Top = 6
          Margins.Right = 6
          Margins.Bottom = 6
          Align = alClient
          Caption = #1058#1110#1083#1100#1082#1080' '#1092#1083#1077#1096#1082#1080
          TabOrder = 3
          OnClick = Button_ShowUSBClick
        end
      end
      object GroupBox_FilterCheckBox: TGroupBox
        AlignWithMargins = True
        Left = 677
        Top = 7
        Width = 288
        Height = 237
        Margins.Left = 6
        Margins.Top = 6
        Margins.Right = 6
        Margins.Bottom = 6
        Align = alClient
        Caption = #1044#1086#1076#1072#1090#1082#1086#1074#1110' '#1085#1072#1083#1072#1096#1090#1091#1074#1072#1085#1085#1103':'
        TabOrder = 2
        object GridPanel_FilterCheckBox: TGridPanel
          Left = 2
          Top = 32
          Width = 284
          Height = 203
          Margins.Left = 6
          Margins.Top = 6
          Margins.Right = 6
          Margins.Bottom = 6
          Align = alClient
          BevelOuter = bvNone
          ColumnCollection = <
            item
              SizeStyle = ssAbsolute
              Value = 50.000000000000000000
            end>
          ControlCollection = <
            item
              Column = 0
              Control = CheckBox_FilterMotherboard
              Row = 0
            end
            item
              Column = 0
              Control = CheckBox_WIP2
              Row = 1
            end
            item
              Column = 0
              Control = CheckBox_WIP3
              Row = 2
            end
            item
              Column = 0
              Control = CheckBox_WIP4
              Row = 3
            end
            item
              Column = 0
              Control = CheckBox_AutoUpdateDev
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
          object CheckBox_FilterMotherboard: TCheckBox
            AlignWithMargins = True
            Left = 6
            Top = 6
            Width = 278
            Height = 29
            Margins.Left = 6
            Margins.Top = 6
            Margins.Right = 6
            Margins.Bottom = 6
            Align = alLeft
            Caption = #1057#1080#1089#1090#1077#1084#1085#1110' '#1087#1088#1080#1089#1090#1088#1086#1111
            Checked = True
            State = cbChecked
            TabOrder = 0
            OnClick = CheckBox_FilterMotherboardClick
          end
          object CheckBox_WIP2: TCheckBox
            AlignWithMargins = True
            Left = 6
            Top = 47
            Width = 278
            Height = 28
            Margins.Left = 6
            Margins.Top = 6
            Margins.Right = 6
            Margins.Bottom = 6
            Align = alLeft
            Caption = 'CheckBox_WIP2'
            Enabled = False
            TabOrder = 1
          end
          object CheckBox_WIP3: TCheckBox
            AlignWithMargins = True
            Left = 6
            Top = 87
            Width = 278
            Height = 29
            Margins.Left = 6
            Margins.Top = 6
            Margins.Right = 6
            Margins.Bottom = 6
            Align = alLeft
            Caption = 'CheckBox_WIP3'
            Enabled = False
            TabOrder = 2
          end
          object CheckBox_WIP4: TCheckBox
            AlignWithMargins = True
            Left = 6
            Top = 128
            Width = 278
            Height = 28
            Margins.Left = 6
            Margins.Top = 6
            Margins.Right = 6
            Margins.Bottom = 6
            Align = alLeft
            Caption = 'CheckBox_WIP4'
            Enabled = False
            TabOrder = 3
          end
          object CheckBox_AutoUpdateDev: TCheckBox
            AlignWithMargins = True
            Left = 6
            Top = 168
            Width = 278
            Height = 29
            Margins.Left = 6
            Margins.Top = 6
            Margins.Right = 6
            Margins.Bottom = 6
            Align = alLeft
            Caption = #1040#1074#1090#1086#1086#1085#1086#1074#1083#1077#1085#1103' '#1087#1088#1080#1089#1090#1088#1086#1111#1074
            Checked = True
            State = cbChecked
            TabOrder = 4
          end
        end
      end
      object GridPanel_Else: TGridPanel
        Left = 971
        Top = 1
        Width = 300
        Height = 249
        Margins.Left = 6
        Margins.Top = 6
        Margins.Right = 6
        Margins.Bottom = 6
        Align = alClient
        BevelOuter = bvNone
        ColumnCollection = <
          item
            Value = 100.000000000000000000
          end>
        ControlCollection = <
          item
            Column = 0
            Control = GroupBox_CountErrSerial
            Row = 0
          end
          item
            Column = 0
            Control = GroupBox_CategPC
            Row = 1
          end
          item
            Column = 0
            Control = Button_DelDevice
            Row = 2
          end>
        RowCollection = <
          item
            SizeStyle = ssAbsolute
            Value = 99.000000000000000000
          end
          item
            SizeStyle = ssAbsolute
            Value = 99.000000000000000000
          end
          item
            Value = 100.000000000000000000
          end>
        TabOrder = 3
        object GroupBox_CountErrSerial: TGroupBox
          AlignWithMargins = True
          Left = 6
          Top = 6
          Width = 288
          Height = 87
          Margins.Left = 6
          Margins.Top = 6
          Margins.Right = 6
          Margins.Bottom = 6
          Align = alClient
          Caption = #1050#1086#1083'-'#1074#1086'. '#1087#1086#1084#1080#1083#1086#1082' '#1074' S/N:'
          TabOrder = 0
          object TrackBar_CountErrSerial: TTrackBar
            Left = 2
            Top = 32
            Width = 284
            Height = 53
            Margins.Left = 11
            Margins.Top = 11
            Margins.Right = 11
            Margins.Bottom = 11
            Align = alClient
            LineSize = 10
            Max = 5
            ParentShowHint = False
            PageSize = 1
            PositionToolTip = ptBottom
            ShowHint = False
            TabOrder = 0
            ThumbLength = 41
            TickMarks = tmBoth
            OnChange = TrackBar_CountErrSerialChange
          end
        end
        object GroupBox_CategPC: TGroupBox
          AlignWithMargins = True
          Left = 6
          Top = 105
          Width = 288
          Height = 87
          Margins.Left = 6
          Margins.Top = 6
          Margins.Right = 6
          Margins.Bottom = 6
          Align = alClient
          Caption = #1050#1072#1090#1077#1075#1086#1088#1110#1103' '#1055#1050':'
          TabOrder = 1
          object ComboBox_CategPC: TComboBox
            AlignWithMargins = True
            Left = 8
            Top = 38
            Width = 272
            Height = 38
            Margins.Left = 6
            Margins.Top = 6
            Margins.Right = 6
            Margins.Bottom = 6
            Align = alTop
            Style = csDropDownList
            ItemIndex = 0
            TabOrder = 0
            Text = #1041#1077#1079' '#1082#1072#1090#1077#1075#1086#1088#1110#1111
            OnChange = ComboBox_CategPCChange
            Items.Strings = (
              #1041#1077#1079' '#1082#1072#1090#1077#1075#1086#1088#1110#1111
              #1053#1077' '#1058#1072#1108#1084#1085#1086
              #1044#1057#1050
              #1058#1072#1108#1084#1085#1086
              #1062#1110#1083#1082#1086#1084' '#1058#1072#1108#1084#1085#1086)
          end
        end
        object Button_DelDevice: TButton
          AlignWithMargins = True
          Left = 6
          Top = 204
          Width = 288
          Height = 39
          Margins.Left = 6
          Margins.Top = 6
          Margins.Right = 6
          Margins.Bottom = 6
          Align = alClient
          Anchors = []
          Caption = #1042#1080#1076#1072#1083#1080#1090#1080' '#1087#1088#1080#1089#1090#1088#1110#1081'!'
          TabOrder = 2
          OnClick = Button_DelDeviceClick
        end
      end
      object Memo_LOG: TMemo
        AlignWithMargins = True
        Left = 1277
        Top = 7
        Width = 284
        Height = 237
        Margins.Left = 6
        Margins.Top = 6
        Margins.Right = 6
        Margins.Bottom = 6
        Align = alClient
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -20
        Font.Name = 'Consolas'
        Font.Style = []
        ParentFont = False
        ReadOnly = True
        ScrollBars = ssBoth
        TabOrder = 4
        WordWrap = False
      end
      object Button_ShowAll: TButton
        AlignWithMargins = True
        Left = 7
        Top = 7
        Width = 58
        Height = 237
        Margins.Left = 6
        Margins.Top = 6
        Margins.Right = 6
        Margins.Bottom = 6
        Align = alClient
        BiDiMode = bdLeftToRight
        Caption = #8635
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -62
        Font.Name = 'Segoe UI'
        Font.Style = []
        ParentBiDiMode = False
        ParentFont = False
        TabOrder = 5
        OnClick = Button_ShowAllClick
      end
    end
    object StatusBar1: TStatusBar
      Left = 0
      Top = 1053
      Width = 1568
      Height = 37
      Margins.Left = 6
      Margins.Top = 6
      Margins.Right = 6
      Margins.Bottom = 6
      Anchors = []
      Panels = <
        item
          Text = 'ROW:'
          Width = 232
        end
        item
          Alignment = taRightJustify
          BiDiMode = bdLeftToRight
          ParentBiDiMode = False
          Text = 'v. 0.0.0.1'
          Width = 232
        end>
    end
    object GridPanel_RunButton: TGridPanel
      Left = 0
      Top = 959
      Width = 1568
      Height = 90
      Margins.Left = 6
      Margins.Top = 6
      Margins.Right = 6
      Margins.Bottom = 6
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
          Control = Button_DeviceUpdateCurPC
          Row = 0
        end
        item
          Column = 3
          Control = Button_SaveToJSON
          Row = 0
        end
        item
          Column = 1
          Control = Button_LoadFromJSON
          Row = 0
        end>
      RowCollection = <
        item
          Value = 100.000000000000000000
        end>
      TabOrder = 3
      object Button_DeviceUpdateCurPC: TButton
        AlignWithMargins = True
        Left = 6
        Top = 6
        Width = 380
        Height = 78
        Margins.Left = 6
        Margins.Top = 6
        Margins.Right = 6
        Margins.Bottom = 6
        Align = alClient
        Caption = #1054#1085#1086#1074#1080#1090#1080#13#10#1087#1088#1080#1089#1090#1088#1086#1111' '#1079' '#1087#1086#1090#1086#1095#1085#1086#1075#1086' '#1055#1050
        TabOrder = 0
        OnClick = Button_DeviceUpdateCurPCClick
      end
      object Button_SaveToJSON: TButton
        AlignWithMargins = True
        Left = 1182
        Top = 6
        Width = 380
        Height = 78
        Margins.Left = 6
        Margins.Top = 6
        Margins.Right = 6
        Margins.Bottom = 6
        Align = alClient
        Caption = #1047#1073#1077#1088#1077#1075#1090#1080' '#1087#1088#1080#1089#1090#1088#1086#1111' '#1074' '#1092#1072#1081#1083
        TabOrder = 1
        OnClick = Button_SaveToJSONClick
      end
      object Button_LoadFromJSON: TButton
        AlignWithMargins = True
        Left = 398
        Top = 6
        Width = 380
        Height = 78
        Margins.Left = 6
        Margins.Top = 6
        Margins.Right = 6
        Margins.Bottom = 6
        Align = alClient
        Caption = #1042#1110#1076#1086#1073#1088#1072#1079#1080#1090#1080' '#1087#1088#1080#1089#1090#1088#1086#1111' '#1079' '#1092#1072#1081#1083#1091
        TabOrder = 2
        OnClick = Button_LoadFromJSONClick
      end
    end
  end
  object FDConnection1: TFDConnection
    Params.Strings = (
      'Database=:memory:'
      'DriverID=SQLite'
      'StringFormat=Choose')
    Left = 272
    Top = 434
  end
  object FDQuery1: TFDQuery
    AfterOpen = FDQuery1AfterOpen
    AfterRefresh = FDQuery1AfterOpen
    Connection = FDConnection1
    SQL.Strings = (
      '')
    Left = 116
    Top = 602
  end
  object FDPhysSQLiteDriverLink1: TFDPhysSQLiteDriverLink
    Left = 276
    Top = 602
  end
  object DataSource1: TDataSource
    DataSet = FDQuery1
    Left = 450
    Top = 602
  end
  object Timer1: TTimer
    Enabled = False
    OnTimer = Timer1Timer
    Left = 46
    Top = 434
  end
  object OpenDialog_FromJSON: TOpenDialog
    Left = 1176
    Top = 524
  end
  object SaveDialog_ToFile: TSaveDialog
    DefaultExt = 'json'
    Options = [ofHideReadOnly, ofExtensionDifferent, ofEnableSizing]
    Left = 976
    Top = 524
  end
end
