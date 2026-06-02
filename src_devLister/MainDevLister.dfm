object Form1: TForm1
  Left = 0
  Top = 0
  Margins.Left = 5
  Margins.Top = 5
  Margins.Right = 5
  Margins.Bottom = 5
  Caption = 'DeviceLister'
  ClientHeight = 836
  ClientWidth = 1576
  Color = clBtnFace
  Constraints.MinHeight = 900
  Constraints.MinWidth = 1600
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -21
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poDesigned
  Scaled = False
  PixelsPerInch = 168
  TextHeight = 30
  object GridPanel_Main: TGridPanel
    Left = 0
    Top = 0
    Width = 1576
    Height = 836
    Margins.Left = 5
    Margins.Top = 5
    Margins.Right = 5
    Margins.Bottom = 5
    Align = alClient
    BevelOuter = bvNone
    ColumnCollection = <
      item
        Value = 100.00000000000000000
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
        Value = 250.00000000000000000
      end
      item
        Value = 100.00000000000000000
      end
      item
        SizeStyle = ssAbsolute
        Value = 90.00000000000000000
      end
      item
        SizeStyle = ssAbsolute
        Value = 40.00000000000000000
      end
      item
        SizeStyle = ssAuto
      end>
    TabOrder = 0
    object DBGrid1: TDBGrid
      AlignWithMargins = True
      Left = 5
      Top = 255
      Width = 1566
      Height = 446
      Margins.Left = 5
      Margins.Top = 5
      Margins.Right = 5
      Margins.Bottom = 5
      Align = alClient
      DataSource = DataSource1
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
      Width = 1576
      Height = 250
      Margins.Left = 5
      Margins.Top = 5
      Margins.Right = 5
      Margins.Bottom = 5
      Align = alClient
      BevelOuter = bvLowered
      ColumnCollection = <
        item
          SizeStyle = ssAbsolute
          Value = 300.00000000000000000
        end
        item
          SizeStyle = ssAbsolute
          Value = 300.00000000000000000
        end
        item
          SizeStyle = ssAbsolute
          Value = 300.00000000000000000
        end
        item
          SizeStyle = ssAbsolute
          Value = 300.00000000000000000
        end
        item
          Value = 100.00000000000000000
        end>
      ControlCollection = <
        item
          Column = 0
          Control = ListBox_Filter
          Row = 1
        end
        item
          Column = 0
          Control = Label1
          Row = 0
        end
        item
          Column = 2
          Control = GridPanel_FilterButton
          Row = 0
          RowSpan = 2
        end
        item
          Column = 1
          Control = GroupBox_FilterCheckBox
          Row = 0
          RowSpan = 2
        end
        item
          Column = 3
          Control = GridPanel_Else
          Row = 0
          RowSpan = 2
        end
        item
          Column = 4
          Control = Memo_LOG
          Row = 0
          RowSpan = 2
        end>
      RowCollection = <
        item
          SizeStyle = ssAbsolute
          Value = 40.00000000000000000
        end
        item
          Value = 100.00000000000000000
        end>
      TabOrder = 1
      object ListBox_Filter: TListBox
        AlignWithMargins = True
        Left = 6
        Top = 46
        Width = 290
        Height = 198
        Margins.Left = 5
        Margins.Top = 5
        Margins.Right = 5
        Margins.Bottom = 5
        Align = alClient
        ItemHeight = 30
        Items.Strings = (
          '('#1059#1089#1110' '#1082#1083#1072#1089#1080' '#1087#1088#1080#1089#1090#1088#1086#1111#1074')'
          'USB'
          'WPD'
          'DiskDrive'
          'Volume')
        MultiSelect = True
        TabOrder = 0
        OnClick = ListBox_FilterClick
        ExplicitTop = 66
        ExplicitHeight = 178
      end
      object Label1: TLabel
        AlignWithMargins = True
        Left = 6
        Top = 6
        Width = 290
        Height = 30
        Margins.Left = 5
        Margins.Top = 5
        Margins.Right = 5
        Margins.Bottom = 5
        Align = alClient
        Caption = #1060#1110#1083#1100#1090#1088' '#1087#1086' '#1082#1083#1072#1089#1091' '#1087#1088#1080#1089#1090#1088#1086#1102':'
        Layout = tlCenter
        ExplicitWidth = 258
      end
      object GridPanel_FilterButton: TGridPanel
        Left = 601
        Top = 1
        Width = 300
        Height = 248
        Margins.Left = 5
        Margins.Top = 5
        Margins.Right = 5
        Margins.Bottom = 5
        Align = alClient
        BevelOuter = bvNone
        ColumnCollection = <
          item
            Value = 100.00000000000000000
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
            Value = 25.00000000000000000
          end
          item
            Value = 25.00000000000000000
          end
          item
            Value = 25.00000000000000000
          end
          item
            Value = 25.00000000000000000
          end>
        TabOrder = 1
        object Button_FilterContainerID: TButton
          AlignWithMargins = True
          Left = 5
          Top = 191
          Width = 290
          Height = 52
          Margins.Left = 5
          Margins.Top = 5
          Margins.Right = 5
          Margins.Bottom = 5
          Align = alClient
          Caption = #1042#1110#1076#1110#1073#1088#1072#1090#1080' '#1079#1072' '#1082#1086#1085#1090#1077#1081#1085#1077#1088#1086#1084
          TabOrder = 0
          OnClick = Button_FilterContainerIDClick
        end
        object Button_ShowUnknowUSB: TButton
          AlignWithMargins = True
          Left = 5
          Top = 67
          Width = 290
          Height = 52
          Margins.Left = 5
          Margins.Top = 5
          Margins.Right = 5
          Margins.Bottom = 5
          Align = alClient
          Caption = #1058#1110#1083#1100#1082#1110' '#1085#1077#1074#1110#1076#1086#1084#1110' '#1092#1083#1077#1096#1082#1080
          TabOrder = 1
          OnClick = Button_ShowUnknowUSBClick
        end
        object Button_ShowAllert: TButton
          AlignWithMargins = True
          Left = 5
          Top = 129
          Width = 290
          Height = 52
          Margins.Left = 5
          Margins.Top = 5
          Margins.Right = 5
          Margins.Bottom = 5
          Align = alClient
          Caption = #1058#1110#1083#1100#1082#1080' '#1087#1086#1088#1091#1096#1077#1085#1103
          TabOrder = 2
          OnClick = Button_ShowAllertClick
        end
        object Button_ShowUSB: TButton
          AlignWithMargins = True
          Left = 5
          Top = 5
          Width = 290
          Height = 52
          Margins.Left = 5
          Margins.Top = 5
          Margins.Right = 5
          Margins.Bottom = 5
          Align = alClient
          Caption = #1058#1110#1083#1100#1082#1080' '#1092#1083#1077#1096#1082#1080
          TabOrder = 3
          OnClick = Button_ShowUSBClick
        end
      end
      object GroupBox_FilterCheckBox: TGroupBox
        AlignWithMargins = True
        Left = 306
        Top = 6
        Width = 290
        Height = 238
        Margins.Left = 5
        Margins.Top = 5
        Margins.Right = 5
        Margins.Bottom = 5
        Align = alClient
        Caption = #1044#1086#1076#1072#1090#1082#1086#1074#1110' '#1085#1072#1083#1072#1096#1090#1091#1074#1072#1085#1085#1103':'
        TabOrder = 2
        object GridPanel_FilterCheckBox: TGridPanel
          Left = 2
          Top = 32
          Width = 286
          Height = 204
          Margins.Left = 5
          Margins.Top = 5
          Margins.Right = 5
          Margins.Bottom = 5
          Align = alClient
          BevelOuter = bvNone
          ColumnCollection = <
            item
              SizeStyle = ssAbsolute
              Value = 50.00000000000000000
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
              Value = 20.00000000000000000
            end
            item
              Value = 20.00000000000000000
            end
            item
              Value = 20.00000000000000000
            end
            item
              Value = 20.00000000000000000
            end
            item
              Value = 20.00000000000000000
            end>
          TabOrder = 0
          object CheckBox_FilterMotherboard: TCheckBox
            AlignWithMargins = True
            Left = 5
            Top = 5
            Width = 278
            Height = 31
            Margins.Left = 5
            Margins.Top = 5
            Margins.Right = 5
            Margins.Bottom = 5
            Align = alLeft
            Caption = #1057#1080#1089#1090#1077#1084#1085#1110' '#1087#1088#1080#1089#1090#1088#1086#1111
            Checked = True
            State = cbChecked
            TabOrder = 0
            OnClick = CheckBox_FilterMotherboardClick
          end
          object CheckBox_WIP2: TCheckBox
            AlignWithMargins = True
            Left = 5
            Top = 46
            Width = 278
            Height = 31
            Margins.Left = 5
            Margins.Top = 5
            Margins.Right = 5
            Margins.Bottom = 5
            Align = alLeft
            Caption = 'CheckBox_WIP2'
            Enabled = False
            TabOrder = 1
          end
          object CheckBox_WIP3: TCheckBox
            AlignWithMargins = True
            Left = 5
            Top = 87
            Width = 278
            Height = 30
            Margins.Left = 5
            Margins.Top = 5
            Margins.Right = 5
            Margins.Bottom = 5
            Align = alLeft
            Caption = 'CheckBox_WIP3'
            Enabled = False
            TabOrder = 2
          end
          object CheckBox_WIP4: TCheckBox
            AlignWithMargins = True
            Left = 5
            Top = 127
            Width = 278
            Height = 31
            Margins.Left = 5
            Margins.Top = 5
            Margins.Right = 5
            Margins.Bottom = 5
            Align = alLeft
            Caption = 'CheckBox_WIP4'
            Enabled = False
            TabOrder = 3
          end
          object CheckBox_AutoUpdateDev: TCheckBox
            AlignWithMargins = True
            Left = 5
            Top = 168
            Width = 278
            Height = 31
            Margins.Left = 5
            Margins.Top = 5
            Margins.Right = 5
            Margins.Bottom = 5
            Align = alLeft
            Caption = #1040#1074#1090#1086#1086#1085#1086#1074#1083#1077#1085#1103' '#1087#1088#1080#1089#1090#1088#1086#1111#1074
            Checked = True
            State = cbChecked
            TabOrder = 4
          end
        end
      end
      object GridPanel_Else: TGridPanel
        Left = 901
        Top = 1
        Width = 300
        Height = 248
        Margins.Left = 5
        Margins.Top = 5
        Margins.Right = 5
        Margins.Bottom = 5
        Align = alClient
        BevelOuter = bvNone
        ColumnCollection = <
          item
            Value = 100.00000000000000000
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
            Value = 100.00000000000000000
          end
          item
            SizeStyle = ssAbsolute
            Value = 100.00000000000000000
          end
          item
            Value = 100.00000000000000000
          end>
        TabOrder = 3
        object GroupBox_CountErrSerial: TGroupBox
          AlignWithMargins = True
          Left = 5
          Top = 5
          Width = 290
          Height = 90
          Margins.Left = 5
          Margins.Top = 5
          Margins.Right = 5
          Margins.Bottom = 5
          Align = alClient
          Caption = #1050#1086#1083'-'#1074#1086'. '#1087#1086#1084#1080#1083#1086#1082' '#1074' S/N:'
          TabOrder = 0
          object TrackBar_CountErrSerial: TTrackBar
            Left = 2
            Top = 32
            Width = 286
            Height = 56
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
            ThumbLength = 40
            TickMarks = tmBoth
            OnChange = TrackBar_CountErrSerialChange
          end
        end
        object GroupBox_CategPC: TGroupBox
          AlignWithMargins = True
          Left = 5
          Top = 105
          Width = 290
          Height = 90
          Margins.Left = 5
          Margins.Top = 5
          Margins.Right = 5
          Margins.Bottom = 5
          Align = alClient
          Caption = #1050#1072#1090#1077#1075#1086#1088#1110#1103' '#1055#1050':'
          TabOrder = 1
          object ComboBox_CategPC: TComboBox
            AlignWithMargins = True
            Left = 7
            Top = 37
            Width = 276
            Height = 38
            Margins.Left = 5
            Margins.Top = 5
            Margins.Right = 5
            Margins.Bottom = 5
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
          Left = 5
          Top = 205
          Width = 290
          Height = 38
          Margins.Left = 5
          Margins.Top = 5
          Margins.Right = 5
          Margins.Bottom = 5
          Align = alClient
          Anchors = []
          Caption = #1042#1080#1076#1072#1083#1080#1090#1080' '#1087#1088#1080#1089#1090#1088#1110#1081'!'
          TabOrder = 2
          OnClick = Button_DelDeviceClick
        end
      end
      object Memo_LOG: TMemo
        AlignWithMargins = True
        Left = 1206
        Top = 6
        Width = 364
        Height = 238
        Margins.Left = 5
        Margins.Top = 5
        Margins.Right = 5
        Margins.Bottom = 5
        Align = alClient
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Segoe UI'
        Font.Style = []
        ParentFont = False
        ReadOnly = True
        ScrollBars = ssBoth
        TabOrder = 4
        WordWrap = False
      end
    end
    object StatusBar1: TStatusBar
      Left = 0
      Top = 796
      Width = 1576
      Height = 40
      Margins.Left = 5
      Margins.Top = 5
      Margins.Right = 5
      Margins.Bottom = 5
      Anchors = []
      Panels = <
        item
          Text = 'ROW:'
          Width = 50
        end>
    end
    object GridPanel_RunButton: TGridPanel
      Left = 0
      Top = 706
      Width = 1576
      Height = 90
      Margins.Left = 5
      Margins.Top = 5
      Margins.Right = 5
      Margins.Bottom = 5
      Align = alClient
      BevelOuter = bvNone
      ColumnCollection = <
        item
          Value = 25.00000000000000000
        end
        item
          Value = 25.00000000000000000
        end
        item
          Value = 25.00000000000000000
        end
        item
          Value = 25.00000000000000000
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
          Value = 100.00000000000000000
        end>
      TabOrder = 3
      object Button_DeviceUpdateCurPC: TButton
        AlignWithMargins = True
        Left = 5
        Top = 5
        Width = 384
        Height = 80
        Margins.Left = 5
        Margins.Top = 5
        Margins.Right = 5
        Margins.Bottom = 5
        Align = alClient
        Caption = #1054#1085#1086#1074#1080#1090#1080#13#10#1087#1088#1080#1089#1090#1088#1086#1111' '#1079' '#1087#1086#1090#1086#1095#1085#1086#1075#1086' '#1055#1050
        TabOrder = 0
        OnClick = Button_DeviceUpdateCurPCClick
      end
      object Button_SaveToJSON: TButton
        AlignWithMargins = True
        Left = 1187
        Top = 5
        Width = 384
        Height = 80
        Margins.Left = 5
        Margins.Top = 5
        Margins.Right = 5
        Margins.Bottom = 5
        Align = alClient
        Caption = #1047#1073#1077#1088#1077#1075#1090#1080' '#1087#1088#1080#1089#1090#1088#1086#1111' '#1074' '#1092#1072#1081#1083
        TabOrder = 1
        OnClick = Button_SaveToJSONClick
      end
      object Button_LoadFromJSON: TButton
        AlignWithMargins = True
        Left = 399
        Top = 5
        Width = 384
        Height = 80
        Margins.Left = 5
        Margins.Top = 5
        Margins.Right = 5
        Margins.Bottom = 5
        Align = alClient
        Caption = #1042#1110#1076#1086#1073#1088#1072#1079#1080#1090#1080' '#1087#1088#1080#1089#1090#1088#1086#1111' '#1079' '#1092#1072#1081#1083#1091
        TabOrder = 2
        OnClick = Button_LoadFromJSONClick
        ExplicitLeft = 968
        ExplicitTop = 56
        ExplicitWidth = 131
        ExplicitHeight = 44
      end
    end
  end
  object FDConnection1: TFDConnection
    Params.Strings = (
      'Database=:memory:'
      'DriverID=SQLite'
      'StringFormat=Choose')
    Left = 56
    Top = 602
  end
  object FDQuery1: TFDQuery
    AfterOpen = FDQuery1AfterOpen
    AfterRefresh = FDQuery1AfterOpen
    Connection = FDConnection1
    SQL.Strings = (
      '')
    Left = 140
    Top = 602
  end
  object FDPhysSQLiteDriverLink1: TFDPhysSQLiteDriverLink
    Left = 252
    Top = 602
  end
  object DataSource1: TDataSource
    DataSet = FDQuery1
    Left = 378
    Top = 602
  end
  object Timer1: TTimer
    Enabled = False
    OnTimer = Timer1Timer
    Left = 56
    Top = 518
  end
  object OpenDialog_FromJSON: TOpenDialog
    Left = 1260
    Top = 476
  end
  object SaveDialog_ToJSON: TSaveDialog
    Left = 1120
    Top = 476
  end
end
