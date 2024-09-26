object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 567
  ClientWidth = 864
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object GridPanelMain: TGridPanel
    Left = 0
    Top = 0
    Width = 864
    Height = 567
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
        Value = 30.000000000000000000
      end>
    TabOrder = 0
    ExplicitLeft = 368
    ExplicitTop = 328
    ExplicitWidth = 185
    ExplicitHeight = 41
    object GridPanel1: TGridPanel
      Left = 1
      Top = 1
      Width = 862
      Height = 535
      Align = alClient
      Anchors = []
      BevelOuter = bvNone
      ColumnCollection = <
        item
          SizeStyle = ssAbsolute
          Value = 400.000000000000000000
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
          Control = Memo1
          Row = 0
        end>
      Padding.Left = 3
      Padding.Top = 3
      Padding.Right = 3
      Padding.Bottom = 3
      RowCollection = <
        item
          Value = 100.000000000000000000
        end
        item
          SizeStyle = ssAbsolute
          Value = 60.000000000000000000
        end>
      TabOrder = 0
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 902
      ExplicitHeight = 657
      object ProgressBar1: TProgressBar
        Left = 6
        Top = 475
        Width = 850
        Height = 54
        Align = alClient
        TabOrder = 0
        ExplicitTop = 557
        ExplicitWidth = 890
      end
      object PageControl1: TPageControl
        Left = 6
        Top = 6
        Width = 394
        Height = 463
        ActivePage = grid
        Align = alClient
        TabOrder = 1
        ExplicitHeight = 553
        object grid: TTabSheet
          Caption = 'GRUBer'
          object GridPanel2: TGridPanel
            Left = 0
            Top = 0
            Width = 386
            Height = 433
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
                ColumnSpan = 2
                Control = GroupBox2
                Row = 3
              end
              item
                Column = 0
                Control = Button1
                Row = 2
              end
              item
                Column = 1
                Control = Button2
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
                Control = GridPanel4
                Row = 1
              end>
            Padding.Left = 1
            Padding.Top = 1
            Padding.Right = 1
            Padding.Bottom = 1
            RowCollection = <
              item
                Value = 74.999914283850400000
              end
              item
                SizeStyle = ssAbsolute
                Value = 30.000000000000000000
              end
              item
                SizeStyle = ssAbsolute
                Value = 50.000000000000000000
              end
              item
                Value = 25.000000000000000000
              end>
            TabOrder = 0
            ExplicitWidth = 434
            ExplicitHeight = 515
            object GroupBox1: TGroupBox
              Left = 2
              Top = 2
              Width = 230
              Height = 263
              Align = alClient
              Caption = #1044#1072#1085#1110' '#1087#1086' '#1040#1056#1052
              TabOrder = 0
              ExplicitLeft = 96
              ExplicitTop = 120
              ExplicitWidth = 185
              ExplicitHeight = 105
            end
            object GroupBox2: TGroupBox
              Left = 2
              Top = 347
              Width = 384
              Height = 86
              Align = alClient
              Caption = #1030#1085#1092#1086' '#1087#1086' '#1040#1056#1052
              TabOrder = 1
              ExplicitLeft = 104
              ExplicitTop = 168
              ExplicitWidth = 185
              ExplicitHeight = 105
            end
            object Button1: TButton
              Left = 2
              Top = 297
              Width = 230
              Height = 48
              Align = alClient
              Caption = 'Button1'
              TabOrder = 2
              ExplicitLeft = 296
              ExplicitTop = 192
              ExplicitWidth = 75
              ExplicitHeight = 25
            end
            object Button2: TButton
              Left = 234
              Top = 297
              Width = 152
              Height = 48
              Align = alClient
              Caption = 'Button2'
              TabOrder = 3
              ExplicitLeft = 272
              ExplicitTop = 208
              ExplicitWidth = 75
              ExplicitHeight = 25
            end
            object GridPanel3: TGridPanel
              Left = 234
              Top = 2
              Width = 152
              Height = 263
              Align = alClient
              BevelOuter = bvNone
              ColumnCollection = <
                item
                  Value = 100.000000000000000000
                end>
              ControlCollection = <
                item
                  Column = 0
                  Control = Button3
                  Row = 0
                end
                item
                  Column = 0
                  Control = Button4
                  Row = 1
                end
                item
                  Column = 0
                  Control = Button5
                  Row = 2
                end>
              Padding.Left = 1
              Padding.Top = 1
              Padding.Bottom = 1
              RowCollection = <
                item
                  Value = 50.140056826060800000
                end
                item
                  Value = 25.000000000000000000
                end
                item
                  Value = 24.859943173939200000
                end>
              TabOrder = 4
              ExplicitLeft = 264
              ExplicitTop = 112
              ExplicitWidth = 185
              ExplicitHeight = 41
              object Button3: TButton
                Left = 2
                Top = 2
                Width = 151
                Height = 129
                Align = alClient
                Caption = 'Button3'
                TabOrder = 0
                ExplicitLeft = 40
                ExplicitTop = 56
                ExplicitWidth = 75
                ExplicitHeight = 25
              end
              object Button4: TButton
                Left = 2
                Top = 133
                Width = 151
                Height = 64
                Align = alClient
                Caption = 'Button4'
                TabOrder = 1
                ExplicitLeft = 56
                ExplicitTop = 168
                ExplicitWidth = 75
                ExplicitHeight = 25
              end
              object Button5: TButton
                Left = 2
                Top = 199
                Width = 151
                Height = 63
                Align = alClient
                Caption = 'Button5'
                TabOrder = 2
                ExplicitLeft = 80
                ExplicitTop = 232
                ExplicitWidth = 75
                ExplicitHeight = 25
              end
            end
            object GridPanel4: TGridPanel
              Left = 2
              Top = 267
              Width = 384
              Height = 28
              Align = alClient
              BevelOuter = bvNone
              ColumnCollection = <
                item
                  SizeStyle = ssAbsolute
                  Value = 30.000000000000000000
                end
                item
                  Value = 100.000000000000000000
                end>
              ControlCollection = <
                item
                  Column = 0
                  Control = CheckBox1
                  Row = 0
                end
                item
                  Column = 1
                  Control = Edit1
                  Row = 0
                end>
              RowCollection = <
                item
                  Value = 100.000000000000000000
                end>
              TabOrder = 5
              ExplicitLeft = 192
              ExplicitTop = 272
              ExplicitWidth = 185
              ExplicitHeight = 41
              object CheckBox1: TCheckBox
                Left = 0
                Top = 0
                Width = 30
                Height = 28
                Align = alClient
                TabOrder = 0
                ExplicitWidth = 24
              end
              object Edit1: TEdit
                Left = 30
                Top = 0
                Width = 354
                Height = 28
                Align = alClient
                TabOrder = 1
                Text = 'Edit1'
                ExplicitLeft = 256
                ExplicitTop = 16
                ExplicitWidth = 121
                ExplicitHeight = 23
              end
            end
          end
        end
        object Налаштування: TTabSheet
          Caption = #1053#1072#1083#1072#1096#1090#1091#1074#1072#1085#1085#1103
          ImageIndex = 1
        end
      end
      object Memo1: TMemo
        Left = 406
        Top = 6
        Width = 450
        Height = 463
        Align = alClient
        Lines.Strings = (
          'Memo1')
        TabOrder = 2
        ExplicitLeft = 454
        ExplicitWidth = 442
        ExplicitHeight = 545
      end
    end
    object StatusBar1: TStatusBar
      Left = 1
      Top = 536
      Width = 862
      Height = 30
      Align = alClient
      Anchors = []
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
          Text = 'GRUBer 0.2 '
          Width = 50
        end>
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 902
      ExplicitHeight = 657
    end
  end
end
