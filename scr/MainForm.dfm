object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 657
  ClientWidth = 902
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object GridPanel1: TGridPanel
    Left = 0
    Top = 0
    Width = 902
    Height = 657
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
        Column = 0
        ColumnSpan = 2
        Control = ProgressBar1
        Row = 1
      end
      item
        Column = 0
        ColumnSpan = 2
        Control = StatusBar1
        Row = 2
      end
      item
        Column = 0
        Control = PageControl1
        Row = 0
      end
      item
        Column = 1
        Control = Memo1
        Row = 0
      end>
    RowCollection = <
      item
        Value = 100.000000000000000000
      end
      item
        SizeStyle = ssAbsolute
        Value = 60.000000000000000000
      end
      item
        SizeStyle = ssAbsolute
        Value = 40.000000000000000000
      end>
    TabOrder = 0
    ExplicitWidth = 900
    ExplicitHeight = 649
    object ProgressBar1: TProgressBar
      Left = 1
      Top = 556
      Width = 900
      Height = 60
      Align = alClient
      TabOrder = 0
      ExplicitTop = 548
      ExplicitWidth = 898
    end
    object StatusBar1: TStatusBar
      Left = 1
      Top = 616
      Width = 900
      Height = 40
      Align = alClient
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
          Style = psOwnerDraw
          Width = 50
        end>
      ExplicitTop = 608
      ExplicitWidth = 898
    end
    object PageControl1: TPageControl
      Left = 1
      Top = 1
      Width = 450
      Height = 555
      ActivePage = TabSheet2
      Align = alClient
      TabOrder = 2
      ExplicitWidth = 449
      ExplicitHeight = 547
      object TabSheet1: TTabSheet
        Caption = 'TabSheet1'
      end
      object TabSheet2: TTabSheet
        Caption = 'TabSheet2'
        ImageIndex = 1
      end
    end
    object Memo1: TMemo
      Left = 451
      Top = 1
      Width = 450
      Height = 555
      Align = alClient
      Lines.Strings = (
        'Memo1')
      TabOrder = 3
      ExplicitLeft = 450
      ExplicitWidth = 449
      ExplicitHeight = 547
    end
  end
end
