object Form_Serial: TForm_Serial
  Left = 0
  Top = 0
  Margins.Left = 5
  Margins.Top = 5
  Margins.Right = 5
  Margins.Bottom = 5
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'FormSerial'
  ClientHeight = 289
  ClientWidth = 674
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -21
  Font.Name = 'Segoe UI'
  Font.Style = []
  PixelsPerInch = 168
  TextHeight = 30
  object GridPanel_Serial: TGridPanel
    AlignWithMargins = True
    Left = 5
    Top = 5
    Width = 664
    Height = 279
    Margins.Left = 5
    Margins.Top = 5
    Margins.Right = 5
    Margins.Bottom = 5
    Align = alClient
    BevelOuter = bvNone
    ColumnCollection = <
      item
        Value = 30.000000000000000000
      end
      item
        Value = 70.000000000000000000
      end>
    ControlCollection = <
      item
        Column = 1
        Control = Edit1
        Row = 0
      end
      item
        Column = 1
        Control = Edit2
        Row = 1
      end
      item
        Column = 1
        Control = Edit3
        Row = 2
      end
      item
        Column = 1
        Control = Edit4
        Row = 3
      end
      item
        Column = 0
        ColumnSpan = 2
        Control = Edit5
        Row = 5
      end
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
        Row = 2
      end
      item
        Column = 0
        Control = Label4
        Row = 3
      end
      item
        Column = 0
        ColumnSpan = 2
        Control = Label5
        Row = 4
      end>
    RowCollection = <
      item
        Value = 17.154018350251820000
      end
      item
        Value = 16.956061448605380000
      end
      item
        Value = 16.760383758750020000
      end
      item
        Value = 16.566962730878480000
      end
      item
        Value = 16.375776067589410000
      end
      item
        Value = 16.186797643924870000
      end
      item
        SizeStyle = ssAuto
      end>
    TabOrder = 0
    ExplicitWidth = 612
    object Edit1: TEdit
      AlignWithMargins = True
      Left = 204
      Top = 5
      Width = 455
      Height = 38
      Margins.Left = 5
      Margins.Top = 5
      Margins.Right = 5
      Margins.Bottom = 5
      Align = alClient
      CharCase = ecUpperCase
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -23
      Font.Name = 'Consolas'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 0
      Text = 'EDIT1'
      StyleName = 'Windows'
      ExplicitLeft = 201
      ExplicitWidth = 448
      ExplicitHeight = 35
    end
    object Edit2: TEdit
      AlignWithMargins = True
      Left = 204
      Top = 53
      Width = 455
      Height = 37
      Margins.Left = 5
      Margins.Top = 5
      Margins.Right = 5
      Margins.Bottom = 5
      Align = alClient
      CharCase = ecUpperCase
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -23
      Font.Name = 'Consolas'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 1
      Text = 'EDIT2'
      StyleName = 'Windows'
      ExplicitLeft = 201
      ExplicitWidth = 448
      ExplicitHeight = 35
    end
    object Edit3: TEdit
      AlignWithMargins = True
      Left = 204
      Top = 100
      Width = 455
      Height = 37
      Margins.Left = 5
      Margins.Top = 5
      Margins.Right = 5
      Margins.Bottom = 5
      Align = alClient
      CharCase = ecUpperCase
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -23
      Font.Name = 'Consolas'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 2
      Text = 'EDIT3'
      StyleName = 'Windows'
      ExplicitLeft = 201
      ExplicitWidth = 448
      ExplicitHeight = 35
    end
    object Edit4: TEdit
      AlignWithMargins = True
      Left = 204
      Top = 147
      Width = 455
      Height = 36
      Margins.Left = 5
      Margins.Top = 5
      Margins.Right = 5
      Margins.Bottom = 5
      Align = alClient
      CharCase = ecUpperCase
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -23
      Font.Name = 'Consolas'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 3
      Text = 'EDIT4'
      StyleName = 'Windows'
      ExplicitLeft = 201
      ExplicitWidth = 448
      ExplicitHeight = 35
    end
    object Edit5: TEdit
      AlignWithMargins = True
      Left = 5
      Top = 239
      Width = 654
      Height = 35
      Margins.Left = 5
      Margins.Top = 5
      Margins.Right = 5
      Margins.Bottom = 5
      Align = alClient
      Alignment = taCenter
      CharCase = ecUpperCase
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -23
      Font.Name = 'Consolas'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 4
      Text = 'EDIT5'
      ExplicitWidth = 644
      ExplicitHeight = 32
    end
    object Label1: TLabel
      AlignWithMargins = True
      Left = 5
      Top = 5
      Width = 189
      Height = 38
      Margins.Left = 5
      Margins.Top = 5
      Margins.Right = 5
      Margins.Bottom = 5
      Align = alClient
      Alignment = taRightJustify
      AutoSize = False
      BiDiMode = bdLeftToRight
      Caption = 'Serial:'
      ParentBiDiMode = False
      Layout = tlCenter
      ExplicitWidth = 60
      ExplicitHeight = 30
    end
    object Label2: TLabel
      AlignWithMargins = True
      Left = 5
      Top = 53
      Width = 189
      Height = 37
      Margins.Left = 5
      Margins.Top = 5
      Margins.Right = 5
      Margins.Bottom = 5
      Align = alClient
      Alignment = taRightJustify
      AutoSize = False
      BiDiMode = bdLeftToRight
      Caption = 'UUID:'
      ParentBiDiMode = False
      Layout = tlCenter
      ExplicitWidth = 60
      ExplicitHeight = 30
    end
    object Label3: TLabel
      AlignWithMargins = True
      Left = 5
      Top = 100
      Width = 189
      Height = 37
      Margins.Left = 5
      Margins.Top = 5
      Margins.Right = 5
      Margins.Bottom = 5
      Align = alClient
      Alignment = taRightJustify
      AutoSize = False
      BiDiMode = bdLeftToRight
      Caption = 'Serial MotherBoard:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -21
      Font.Name = 'Segoe UI'
      Font.Style = []
      ParentBiDiMode = False
      ParentFont = False
      Layout = tlCenter
      ExplicitWidth = 60
      ExplicitHeight = 30
    end
    object Label4: TLabel
      AlignWithMargins = True
      Left = 5
      Top = 147
      Width = 189
      Height = 36
      Margins.Left = 5
      Margins.Top = 5
      Margins.Right = 5
      Margins.Bottom = 5
      Align = alClient
      Alignment = taRightJustify
      AutoSize = False
      BiDiMode = bdLeftToRight
      Caption = 'CPUID:'
      ParentBiDiMode = False
      Layout = tlCenter
      ExplicitWidth = 60
      ExplicitHeight = 30
    end
    object Label5: TLabel
      Left = 0
      Top = 188
      Width = 302
      Height = 30
      Margins.Left = 5
      Margins.Top = 5
      Margins.Right = 5
      Margins.Bottom = 5
      Align = alClient
      Alignment = taCenter
      Caption = #1057#1075#1077#1085#1077#1088#1086#1074#1072#1085#1080#1081' '#1089#1077#1088#1110#1081#1085#1080#1081' '#1085#1086#1084#1077#1088':'
      Layout = tlBottom
    end
  end
end
