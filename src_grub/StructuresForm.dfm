object FormStructures: TFormStructures
  Left = 0
  Top = 0
  Margins.Left = 6
  Margins.Top = 6
  Margins.Right = 6
  Margins.Bottom = 6
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = #1056#1077#1076#1072#1075#1091#1074#1072#1085#1085#1103' '#1089#1090#1088#1091#1082#1090#1091#1088
  ClientHeight = 700
  ClientWidth = 920
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -21
  Font.Name = 'Segoe UI'
  Font.Style = []
  FormStyle = fsStayOnTop
  Position = poOwnerFormCenter
  PixelsPerInch = 168
  TextHeight = 30
  object GridPanelMain: TGridPanel
    Left = 0
    Top = 0
    Width = 920
    Height = 700
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
        Control = GridPanelContent
        Row = 0
      end
      item
        Column = 0
        Control = GridPanelButtons
        Row = 1
      end>
    RowCollection = <
      item
        Value = 100.000000000000000000
      end
      item
        SizeStyle = ssAbsolute
        Value = 90.000000000000000000
      end>
    TabOrder = 0
    object GridPanelContent: TGridPanel
      Left = 0
      Top = 0
      Width = 920
      Height = 610
      Margins.Left = 6
      Margins.Top = 6
      Margins.Right = 6
      Margins.Bottom = 6
      Align = alClient
      BevelOuter = bvNone
      ColumnCollection = <
        item
          Value = 35.000000000000000000
        end
        item
          Value = 65.000000000000000000
        end>
      ControlCollection = <
        item
          Column = 0
          Control = ListBoxStructures
          Row = 0
        end
        item
          Column = 1
          Control = GridPanelDetail
          Row = 0
        end>
      RowCollection = <
        item
          Value = 100.000000000000000000
        end>
      TabOrder = 0
      object ListBoxStructures: TListBox
        AlignWithMargins = True
        Left = 6
        Top = 6
        Width = 310
        Height = 598
        Margins.Left = 6
        Margins.Top = 6
        Margins.Right = 6
        Margins.Bottom = 6
        Align = alClient
        ItemHeight = 30
        TabOrder = 0
        OnClick = ListBoxStructuresClick
      end
      object GridPanelDetail: TGridPanel
        Left = 322
        Top = 0
        Width = 598
        Height = 610
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
            Control = EditStructName
            Row = 0
          end
          item
            Column = 0
            Control = LabelStructPartition
            Row = 1
          end
          item
            Column = 0
            Control = MemoStructPartition
            Row = 2
          end
          item
            Column = 0
            Control = LabEdit_StructNumber
            Row = 3
          end>
        RowCollection = <
          item
            SizeStyle = ssAbsolute
            Value = 50.000000000000000000
          end
          item
            SizeStyle = ssAbsolute
            Value = 44.000000000000000000
          end
          item
            Value = 100.000000000000000000
          end
          item
            SizeStyle = ssAbsolute
            Value = 75.000000000000000000
          end>
        TabOrder = 1
        object EditStructName: TLabeledEdit
          AlignWithMargins = True
          Left = 6
          Top = 6
          Width = 586
          Height = 38
          Margins.Left = 6
          Margins.Top = 6
          Margins.Right = 6
          Margins.Bottom = 6
          Align = alClient
          EditLabel.Width = 62
          EditLabel.Height = 30
          EditLabel.Caption = #1053#1072#1079#1074#1072':'
          TabOrder = 0
          Text = ''
          OnChange = EditStructNameChange
        end
        object LabelStructPartition: TLabel
          AlignWithMargins = True
          Left = 6
          Top = 56
          Width = 586
          Height = 32
          Margins.Left = 6
          Margins.Top = 6
          Margins.Right = 6
          Margins.Bottom = 6
          Align = alClient
          Caption = #1042#1110#1076#1076#1110#1083#1080' ('#1087#1086' '#1086#1076#1085#1086#1084#1091' '#1085#1072' '#1088#1103#1076#1086#1082'):'
          Layout = tlCenter
          ExplicitTop = 86
          ExplicitWidth = 283
          ExplicitHeight = 30
        end
        object MemoStructPartition: TMemo
          AlignWithMargins = True
          Left = 6
          Top = 100
          Width = 586
          Height = 429
          Margins.Left = 6
          Margins.Top = 6
          Margins.Right = 6
          Margins.Bottom = 6
          Align = alClient
          ScrollBars = ssBoth
          TabOrder = 1
          OnChange = MemoStructPartitionChange
          ExplicitTop = 130
          ExplicitHeight = 394
        end
        object LabEdit_StructNumber: TLabeledEdit
          AlignWithMargins = True
          Left = 6
          Top = 568
          Width = 586
          Height = 36
          Margins.Left = 6
          Margins.Top = 6
          Margins.Right = 6
          Margins.Bottom = 6
          Align = alBottom
          EditLabel.Width = 199
          EditLabel.Height = 30
          EditLabel.Caption = #1053#1086#1084#1077#1088' '#1085#1072' '#1094#1100#1086#1084#1091' '#1055#1050':'
          ReadOnly = True
          TabOrder = 2
          Text = ''
          ExplicitLeft = 0
          ExplicitTop = 574
          ExplicitWidth = 598
        end
      end
    end
    object GridPanelButtons: TGridPanel
      Left = 0
      Top = 610
      Width = 920
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
          Control = ButtonAddStruct
          Row = 0
        end
        item
          Column = 1
          Control = ButtonDeleteStruct
          Row = 0
        end
        item
          Column = 2
          Control = ButtonSaveStructures
          Row = 0
        end
        item
          Column = 3
          Control = ButtonCloseStructures
          Row = 0
        end>
      RowCollection = <
        item
          Value = 100.000000000000000000
        end>
      TabOrder = 1
      object ButtonAddStruct: TButton
        AlignWithMargins = True
        Left = 6
        Top = 6
        Width = 218
        Height = 78
        Margins.Left = 6
        Margins.Top = 6
        Margins.Right = 6
        Margins.Bottom = 6
        Align = alClient
        Caption = #1044#1086#1076#1072#1090#1080
        TabOrder = 0
        OnClick = ButtonAddStructClick
      end
      object ButtonDeleteStruct: TButton
        AlignWithMargins = True
        Left = 236
        Top = 6
        Width = 218
        Height = 78
        Margins.Left = 6
        Margins.Top = 6
        Margins.Right = 6
        Margins.Bottom = 6
        Align = alClient
        Caption = #1042#1080#1076#1072#1083#1080#1090#1080
        TabOrder = 1
        OnClick = ButtonDeleteStructClick
      end
      object ButtonSaveStructures: TButton
        AlignWithMargins = True
        Left = 466
        Top = 6
        Width = 218
        Height = 78
        Margins.Left = 6
        Margins.Top = 6
        Margins.Right = 6
        Margins.Bottom = 6
        Align = alClient
        Caption = #1047#1073#1077#1088#1077#1075#1090#1080
        TabOrder = 2
        OnClick = ButtonSaveStructuresClick
      end
      object ButtonCloseStructures: TButton
        AlignWithMargins = True
        Left = 696
        Top = 6
        Width = 218
        Height = 78
        Margins.Left = 6
        Margins.Top = 6
        Margins.Right = 6
        Margins.Bottom = 6
        Align = alClient
        Caption = #1042#1110#1076#1084#1110#1085#1072
        TabOrder = 3
        OnClick = ButtonCloseStructuresClick
      end
    end
  end
end
