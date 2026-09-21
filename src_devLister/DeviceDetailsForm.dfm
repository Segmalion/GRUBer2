object FormDeviceDetails: TFormDeviceDetails
  Left = 0
  Top = 0
  Margins.Left = 6
  Margins.Top = 6
  Margins.Right = 6
  Margins.Bottom = 6
  BorderStyle = bsDialog
  Caption = #1042#1083#1072#1089#1090#1080#1074#1086#1089#1090#1110' '#1087#1088#1080#1089#1090#1088#1086#1102
  ClientHeight = 980
  ClientWidth = 1100
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -21
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poOwnerFormCenter
  PixelsPerInch = 168
  TextHeight = 30
  object GridPanel_Main: TGridPanel
    Left = 0
    Top = 0
    Width = 1100
    Height = 980
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
        Control = Label_ContainerInfo
        Row = 0
      end
      item
        Column = 0
        Control = ComboBox_Devices
        Row = 1
      end
      item
        Column = 0
        Control = Grid_Properties
        Row = 2
      end
      item
        Column = 0
        Control = Panel_Buttons
        Row = 3
      end>
    RowCollection = <
      item
        SizeStyle = ssAbsolute
        Value = 46.000000000000000000
      end
      item
        SizeStyle = ssAbsolute
        Value = 52.000000000000000000
      end
      item
        Value = 100.000000000000000000
      end
      item
        SizeStyle = ssAbsolute
        Value = 70.000000000000000000
      end>
    TabOrder = 0
    object Label_ContainerInfo: TLabel
      AlignWithMargins = True
      Left = 6
      Top = 6
      Width = 1088
      Height = 34
      Margins.Left = 6
      Margins.Top = 6
      Margins.Right = 6
      Margins.Bottom = 6
      Align = alClient
      Caption = #1050#1086#1085#1090#1077#1081#1085#1077#1088
      Layout = tlCenter
      ExplicitWidth = 130
      ExplicitHeight = 30
    end
    object ComboBox_Devices: TComboBox
      AlignWithMargins = True
      Left = 6
      Top = 52
      Width = 1088
      Height = 40
      Margins.Left = 6
      Margins.Top = 0
      Margins.Right = 6
      Margins.Bottom = 6
      Align = alClient
      Style = csDropDownList
      TabOrder = 0
      OnChange = ComboBox_DevicesChange
    end
    object Grid_Properties: TStringGrid
      AlignWithMargins = True
      Left = 6
      Top = 98
      Width = 1088
      Height = 800
      Margins.Left = 6
      Margins.Top = 0
      Margins.Right = 6
      Margins.Bottom = 6
      Align = alClient
      ColCount = 2
      DefaultRowHeight = 34
      DefaultDrawing = False
      FixedCols = 0
      RowCount = 1
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -18
      Font.Name = 'Segoe UI'
      Font.Style = []
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRowSelect]
      ParentFont = False
      PopupMenu = PopupMenu_Grid
      TabOrder = 1
      OnDrawCell = Grid_PropertiesDrawCell
      OnKeyDown = Grid_PropertiesKeyDown
      OnMouseDown = Grid_PropertiesMouseDown
      ColWidths = (
        320
        752)
    end
    object Panel_Buttons: TPanel
      Left = 0
      Top = 900
      Width = 1100
      Height = 70
      Align = alClient
      BevelOuter = bvNone
      TabOrder = 2
      object Button_Close: TButton
        AlignWithMargins = True
        Left = 934
        Top = 6
        Width = 160
        Height = 58
        Margins.Left = 6
        Margins.Top = 6
        Margins.Right = 6
        Margins.Bottom = 6
        Align = alRight
        Caption = #1047#1072#1082#1088#1080#1090#1080
        ModalResult = 1
        TabOrder = 0
      end
    end
  end
  object FDQuery_Container: TFDQuery
    Left = 24
    Top = 760
  end
  object PopupMenu_Grid: TPopupMenu
    OnPopup = PopupMenu_GridPopup
    Left = 96
    Top = 760
    object MenuItem_CopyValue: TMenuItem
      Caption = #1050#1086#1087#1110#1102#1074#1072#1090#1080' '#1079#1085#1072#1095#1077#1085#1085#1103' (Ctrl+C)'
      OnClick = MenuItem_CopyValueClick
    end
  end
end
