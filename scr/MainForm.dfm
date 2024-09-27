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
    ExplicitWidth = 862
    ExplicitHeight = 559
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
      ExplicitWidth = 860
      ExplicitHeight = 527
      object ProgressBar1: TProgressBar
        Left = 6
        Top = 475
        Width = 850
        Height = 54
        Align = alClient
        TabOrder = 0
        ExplicitTop = 467
        ExplicitWidth = 848
      end
      object PageControl1: TPageControl
        Left = 6
        Top = 6
        Width = 394
        Height = 463
        ActivePage = grid
        Align = alClient
        TabOrder = 1
        ExplicitHeight = 455
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
              end
              item
                Column = 0
                ColumnSpan = 2
                Control = GroupBox2
                Row = 3
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
            ExplicitHeight = 425
            object GroupBox1: TGroupBox
              AlignWithMargins = True
              Left = 5
              Top = 5
              Width = 222
              Height = 255
              Align = alClient
              Caption = #1044#1072#1085#1110' '#1087#1086' '#1040#1056#1052
              TabOrder = 0
              ExplicitLeft = 2
              ExplicitTop = 2
              ExplicitWidth = 228
              object GridPanel5: TGridPanel
                Left = 2
                Top = 17
                Width = 218
                Height = 236
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
                    Column = 1
                    Control = Edit5
                    Row = 3
                  end
                  item
                    Column = 0
                    Control = Label5
                    Row = 4
                  end
                  item
                    Column = 1
                    Control = Edit6
                    Row = 4
                  end
                  item
                    Column = 0
                    Control = Label6
                    Row = 5
                  end
                  item
                    Column = 1
                    Control = Edit7
                    Row = 5
                  end
                  item
                    Column = 1
                    Control = NumberBox1
                    Row = 0
                  end
                  item
                    Column = 1
                    Control = ComboBox1
                    Row = 1
                  end
                  item
                    Column = 1
                    Control = ComboBox2
                    Row = 2
                  end>
                Padding.Left = 1
                Padding.Top = 1
                Padding.Right = 1
                Padding.Bottom = 1
                RowCollection = <
                  item
                    Value = 17.154021311474090000
                  end
                  item
                    Value = 16.956057761047390000
                  end
                  item
                    Value = 16.760380277296630000
                  end
                  item
                    Value = 16.566963133854170000
                  end
                  item
                    Value = 16.375778395795510000
                  end
                  item
                    Value = 16.186799120532230000
                  end
                  item
                    SizeStyle = ssAuto
                  end>
                TabOrder = 0
                ExplicitLeft = 16
                ExplicitTop = 104
                ExplicitWidth = 185
                ExplicitHeight = 41
                DesignSize = (
                  218
                  236)
                object Label1: TLabel
                  AlignWithMargins = True
                  Left = 5
                  Top = 13
                  Width = 38
                  Height = 15
                  Anchors = [akLeft]
                  Caption = #1053#1086#1084#1077#1088
                end
                object Label2: TLabel
                  AlignWithMargins = True
                  Left = 5
                  Top = 53
                  Width = 32
                  Height = 15
                  Anchors = [akLeft]
                  Caption = #1042#1110#1076#1076#1110#1083
                end
                object Label3: TLabel
                  AlignWithMargins = True
                  Left = 5
                  Top = 93
                  Width = 52
                  Height = 15
                  Anchors = [akLeft]
                  Caption = #1050#1072#1090#1077#1075#1086#1088#1110#1103
                end
                object Label4: TLabel
                  AlignWithMargins = True
                  Left = 5
                  Top = 132
                  Width = 48
                  Height = 15
                  Anchors = [akLeft]
                  Caption = #1042#1110#1076#1087#1086#1074#1110#1076'.'
                end
                object Edit5: TEdit
                  Left = 82
                  Top = 128
                  Width = 130
                  Height = 23
                  Anchors = [akLeft, akTop, akRight, akBottom]
                  TabOrder = 0
                  Text = 'Edit5'
                end
                object Label5: TLabel
                  AlignWithMargins = True
                  Left = 5
                  Top = 170
                  Width = 54
                  Height = 15
                  Anchors = [akLeft]
                  Caption = #1050#1086#1084#1077#1085#1090#1072#1088
                end
                object Edit6: TEdit
                  Left = 82
                  Top = 166
                  Width = 130
                  Height = 23
                  Anchors = [akLeft, akTop, akRight, akBottom]
                  TabOrder = 1
                  Text = 'Edit6'
                end
                object Label6: TLabel
                  AlignWithMargins = True
                  Left = 5
                  Top = 208
                  Width = 45
                  Height = 15
                  Anchors = [akLeft]
                  Caption = #1051#1110#1094#1077#1085#1079#1110#1103
                end
                object Edit7: TEdit
                  Left = 82
                  Top = 204
                  Width = 130
                  Height = 23
                  Anchors = [akLeft, akTop, akRight, akBottom]
                  TabOrder = 2
                  Text = 'Edit7'
                end
                object NumberBox1: TNumberBox
                  Left = 82
                  Top = 9
                  Width = 130
                  Height = 23
                  Anchors = [akLeft, akTop, akRight, akBottom]
                  TabOrder = 3
                end
                object ComboBox1: TComboBox
                  Left = 82
                  Top = 49
                  Width = 130
                  Height = 23
                  Anchors = [akLeft, akTop, akRight, akBottom]
                  TabOrder = 4
                  Text = 'ComboBox1'
                end
                object ComboBox2: TComboBox
                  Left = 82
                  Top = 89
                  Width = 130
                  Height = 23
                  Anchors = [akLeft, akTop, akRight, akBottom]
                  TabOrder = 5
                  Text = 'ComboBox2'
                end
              end
            end
            object Button1: TButton
              AlignWithMargins = True
              Left = 5
              Top = 298
              Width = 222
              Height = 42
              Align = alClient
              Caption = 'Button1'
              TabOrder = 1
              ExplicitLeft = 2
              ExplicitTop = 289
              ExplicitWidth = 228
              ExplicitHeight = 48
            end
            object Button2: TButton
              AlignWithMargins = True
              Left = 235
              Top = 298
              Width = 146
              Height = 42
              Align = alClient
              Caption = 'Button2'
              TabOrder = 2
              ExplicitLeft = 232
              ExplicitTop = 289
              ExplicitWidth = 152
              ExplicitHeight = 48
            end
            object GridPanel3: TGridPanel
              Left = 232
              Top = 2
              Width = 152
              Height = 261
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
              RowCollection = <
                item
                  Value = 69.742122127755340000
                end
                item
                  Value = 15.171436200141860000
                end
                item
                  Value = 15.086441672102810000
                end>
              TabOrder = 3
              ExplicitHeight = 255
              object Button3: TButton
                AlignWithMargins = True
                Left = 3
                Top = 3
                Width = 145
                Height = 175
                Align = alClient
                Caption = 'Button3'
                TabOrder = 0
                ExplicitLeft = 2
                ExplicitTop = 2
                ExplicitWidth = 150
                ExplicitHeight = 125
              end
              object Button4: TButton
                AlignWithMargins = True
                Left = 3
                Top = 184
                Width = 145
                Height = 34
                Align = alClient
                Caption = 'Button4'
                TabOrder = 1
                ExplicitLeft = 2
                ExplicitTop = 129
                ExplicitWidth = 150
                ExplicitHeight = 61
              end
              object Button5: TButton
                AlignWithMargins = True
                Left = 3
                Top = 224
                Width = 145
                Height = 33
                Align = alClient
                Caption = 'Button5'
                TabOrder = 2
                ExplicitLeft = 2
                ExplicitTop = 192
                ExplicitWidth = 150
                ExplicitHeight = 61
              end
            end
            object GridPanel4: TGridPanel
              Left = 2
              Top = 265
              Width = 382
              Height = 28
              Align = alClient
              BevelOuter = bvNone
              ColumnCollection = <
                item
                  SizeStyle = ssAbsolute
                  Value = 25.000000000000000000
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
              TabOrder = 4
              ExplicitTop = 259
              object CheckBox1: TCheckBox
                AlignWithMargins = True
                Left = 3
                Top = 3
                Width = 19
                Height = 22
                Align = alClient
                Alignment = taLeftJustify
                DoubleBuffered = True
                ParentDoubleBuffered = False
                TabOrder = 0
              end
              object Edit1: TEdit
                AlignWithMargins = True
                Left = 28
                Top = 3
                Width = 351
                Height = 22
                Align = alClient
                Alignment = taCenter
                TabOrder = 1
                Text = 'Edit1'
                ExplicitLeft = 54
                ExplicitTop = 4
                ExplicitWidth = 299
              end
            end
            object GroupBox2: TGroupBox
              AlignWithMargins = True
              Left = 5
              Top = 348
              Width = 376
              Height = 80
              Align = alClient
              Caption = #1030#1085#1092#1086' '#1087#1086' '#1040#1056#1052
              TabOrder = 5
              ExplicitLeft = 104
              ExplicitTop = 168
              ExplicitWidth = 185
              ExplicitHeight = 105
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
        ExplicitWidth = 448
        ExplicitHeight = 455
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
      ExplicitTop = 528
      ExplicitWidth = 860
    end
  end
end
