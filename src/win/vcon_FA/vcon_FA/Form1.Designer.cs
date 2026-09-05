namespace vcon_FA
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent() {
            components = new System.ComponentModel.Container();
            tableLayoutPanel1 = new TableLayoutPanel();
            ComboBox_Root_ComPort = new ComboBox();
            tabControl1 = new TabControl();
            TabPage_Full = new TabPage();
            TabPage_Simple = new TabPage();
            tableLayoutPanel3 = new TableLayoutPanel();
            CheckBox_Simple_Left = new CheckBox();
            CheckBox_Simple_Right = new CheckBox();
            tableLayoutPanel2 = new TableLayoutPanel();
            CheckBox_Simple_Up = new CheckBox();
            CheckBox_Simple_Down = new CheckBox();
            flowLayoutPanel1 = new FlowLayoutPanel();
            RadioButton_Root_Full = new RadioButton();
            RadioButton_Root_Simple = new RadioButton();
            CheckBox_Root_Run = new CheckBox();
            Timer_Root_Send = new System.Windows.Forms.Timer(components);
            TextBox_Root_Data = new TextBox();
            tableLayoutPanel1.SuspendLayout();
            tabControl1.SuspendLayout();
            TabPage_Simple.SuspendLayout();
            tableLayoutPanel3.SuspendLayout();
            tableLayoutPanel2.SuspendLayout();
            flowLayoutPanel1.SuspendLayout();
            SuspendLayout();
            // 
            // tableLayoutPanel1
            // 
            tableLayoutPanel1.ColumnCount = 3;
            tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 100F));
            tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle());
            tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle());
            tableLayoutPanel1.Controls.Add(ComboBox_Root_ComPort, 0, 0);
            tableLayoutPanel1.Controls.Add(tabControl1, 0, 1);
            tableLayoutPanel1.Controls.Add(flowLayoutPanel1, 2, 0);
            tableLayoutPanel1.Controls.Add(CheckBox_Root_Run, 1, 0);
            tableLayoutPanel1.Controls.Add(TextBox_Root_Data, 0, 2);
            tableLayoutPanel1.Dock = DockStyle.Fill;
            tableLayoutPanel1.Location = new Point(0, 0);
            tableLayoutPanel1.Margin = new Padding(3, 2, 3, 2);
            tableLayoutPanel1.Name = "tableLayoutPanel1";
            tableLayoutPanel1.RowCount = 3;
            tableLayoutPanel1.RowStyles.Add(new RowStyle());
            tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Percent, 66.6666641F));
            tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Percent, 33.3333321F));
            tableLayoutPanel1.Size = new Size(686, 360);
            tableLayoutPanel1.TabIndex = 0;
            // 
            // ComboBox_Root_ComPort
            // 
            ComboBox_Root_ComPort.Anchor = AnchorStyles.Left | AnchorStyles.Right;
            ComboBox_Root_ComPort.FormattingEnabled = true;
            ComboBox_Root_ComPort.Location = new Point(3, 13);
            ComboBox_Root_ComPort.Margin = new Padding(3, 2, 3, 2);
            ComboBox_Root_ComPort.Name = "ComboBox_Root_ComPort";
            ComboBox_Root_ComPort.Size = new Size(576, 20);
            ComboBox_Root_ComPort.TabIndex = 0;
            ComboBox_Root_ComPort.DropDown += ComboBox_Root_ComPort_DropDown;
            // 
            // tabControl1
            // 
            tableLayoutPanel1.SetColumnSpan(tabControl1, 3);
            tabControl1.Controls.Add(TabPage_Full);
            tabControl1.Controls.Add(TabPage_Simple);
            tabControl1.Dock = DockStyle.Fill;
            tabControl1.Location = new Point(3, 53);
            tabControl1.Name = "tabControl1";
            tabControl1.SelectedIndex = 0;
            tabControl1.Size = new Size(680, 200);
            tabControl1.TabIndex = 2;
            // 
            // TabPage_Full
            // 
            TabPage_Full.Location = new Point(4, 22);
            TabPage_Full.Name = "TabPage_Full";
            TabPage_Full.Padding = new Padding(3);
            TabPage_Full.Size = new Size(672, 174);
            TabPage_Full.TabIndex = 0;
            TabPage_Full.Text = "Full";
            TabPage_Full.UseVisualStyleBackColor = true;
            // 
            // TabPage_Simple
            // 
            TabPage_Simple.Controls.Add(tableLayoutPanel3);
            TabPage_Simple.Controls.Add(tableLayoutPanel2);
            TabPage_Simple.Location = new Point(4, 24);
            TabPage_Simple.Name = "TabPage_Simple";
            TabPage_Simple.Padding = new Padding(3);
            TabPage_Simple.Size = new Size(672, 168);
            TabPage_Simple.TabIndex = 1;
            TabPage_Simple.Text = "Simple";
            TabPage_Simple.UseVisualStyleBackColor = true;
            // 
            // tableLayoutPanel3
            // 
            tableLayoutPanel3.ColumnCount = 2;
            tableLayoutPanel3.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 50F));
            tableLayoutPanel3.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 50F));
            tableLayoutPanel3.Controls.Add(CheckBox_Simple_Left, 0, 0);
            tableLayoutPanel3.Controls.Add(CheckBox_Simple_Right, 1, 0);
            tableLayoutPanel3.Location = new Point(307, 59);
            tableLayoutPanel3.Name = "tableLayoutPanel3";
            tableLayoutPanel3.RowCount = 1;
            tableLayoutPanel3.RowStyles.Add(new RowStyle(SizeType.Percent, 50F));
            tableLayoutPanel3.Size = new Size(200, 50);
            tableLayoutPanel3.TabIndex = 0;
            // 
            // CheckBox_Simple_Left
            // 
            CheckBox_Simple_Left.AutoSize = true;
            CheckBox_Simple_Left.Dock = DockStyle.Fill;
            CheckBox_Simple_Left.Location = new Point(3, 3);
            CheckBox_Simple_Left.Name = "CheckBox_Simple_Left";
            CheckBox_Simple_Left.Size = new Size(94, 44);
            CheckBox_Simple_Left.TabIndex = 0;
            CheckBox_Simple_Left.Text = "Left";
            CheckBox_Simple_Left.TextAlign = ContentAlignment.MiddleCenter;
            CheckBox_Simple_Left.UseVisualStyleBackColor = true;
            // 
            // CheckBox_Simple_Right
            // 
            CheckBox_Simple_Right.AutoSize = true;
            CheckBox_Simple_Right.CheckAlign = ContentAlignment.MiddleRight;
            CheckBox_Simple_Right.Dock = DockStyle.Fill;
            CheckBox_Simple_Right.Location = new Point(103, 3);
            CheckBox_Simple_Right.Name = "CheckBox_Simple_Right";
            CheckBox_Simple_Right.Size = new Size(94, 44);
            CheckBox_Simple_Right.TabIndex = 1;
            CheckBox_Simple_Right.Text = "Right";
            CheckBox_Simple_Right.TextAlign = ContentAlignment.MiddleCenter;
            CheckBox_Simple_Right.UseVisualStyleBackColor = true;
            // 
            // tableLayoutPanel2
            // 
            tableLayoutPanel2.ColumnCount = 1;
            tableLayoutPanel2.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 50F));
            tableLayoutPanel2.Controls.Add(CheckBox_Simple_Up, 0, 0);
            tableLayoutPanel2.Controls.Add(CheckBox_Simple_Down, 0, 1);
            tableLayoutPanel2.Location = new Point(179, 33);
            tableLayoutPanel2.Name = "tableLayoutPanel2";
            tableLayoutPanel2.RowCount = 2;
            tableLayoutPanel2.RowStyles.Add(new RowStyle(SizeType.Percent, 50F));
            tableLayoutPanel2.RowStyles.Add(new RowStyle(SizeType.Percent, 50F));
            tableLayoutPanel2.Size = new Size(90, 100);
            tableLayoutPanel2.TabIndex = 0;
            // 
            // CheckBox_Simple_Up
            // 
            CheckBox_Simple_Up.AutoSize = true;
            CheckBox_Simple_Up.CheckAlign = ContentAlignment.TopCenter;
            CheckBox_Simple_Up.Dock = DockStyle.Fill;
            CheckBox_Simple_Up.Location = new Point(3, 3);
            CheckBox_Simple_Up.Name = "CheckBox_Simple_Up";
            CheckBox_Simple_Up.Size = new Size(84, 44);
            CheckBox_Simple_Up.TabIndex = 0;
            CheckBox_Simple_Up.Text = "Up";
            CheckBox_Simple_Up.TextAlign = ContentAlignment.MiddleCenter;
            CheckBox_Simple_Up.UseVisualStyleBackColor = true;
            // 
            // CheckBox_Simple_Down
            // 
            CheckBox_Simple_Down.AutoSize = true;
            CheckBox_Simple_Down.CheckAlign = ContentAlignment.BottomCenter;
            CheckBox_Simple_Down.Dock = DockStyle.Fill;
            CheckBox_Simple_Down.Location = new Point(3, 53);
            CheckBox_Simple_Down.Name = "CheckBox_Simple_Down";
            CheckBox_Simple_Down.Size = new Size(84, 44);
            CheckBox_Simple_Down.TabIndex = 1;
            CheckBox_Simple_Down.Text = "Down";
            CheckBox_Simple_Down.TextAlign = ContentAlignment.MiddleCenter;
            CheckBox_Simple_Down.UseVisualStyleBackColor = true;
            // 
            // flowLayoutPanel1
            // 
            flowLayoutPanel1.AutoSize = true;
            flowLayoutPanel1.Controls.Add(RadioButton_Root_Full);
            flowLayoutPanel1.Controls.Add(RadioButton_Root_Simple);
            flowLayoutPanel1.Dock = DockStyle.Fill;
            flowLayoutPanel1.Location = new Point(618, 3);
            flowLayoutPanel1.Name = "flowLayoutPanel1";
            flowLayoutPanel1.Size = new Size(65, 44);
            flowLayoutPanel1.TabIndex = 3;
            // 
            // RadioButton_Root_Full
            // 
            RadioButton_Root_Full.AutoSize = true;
            RadioButton_Root_Full.Location = new Point(3, 3);
            RadioButton_Root_Full.Name = "RadioButton_Root_Full";
            RadioButton_Root_Full.Size = new Size(47, 16);
            RadioButton_Root_Full.TabIndex = 0;
            RadioButton_Root_Full.Text = "Full";
            RadioButton_Root_Full.UseVisualStyleBackColor = true;
            // 
            // RadioButton_Root_Simple
            // 
            RadioButton_Root_Simple.AutoSize = true;
            RadioButton_Root_Simple.Checked = true;
            RadioButton_Root_Simple.Location = new Point(3, 25);
            RadioButton_Root_Simple.Name = "RadioButton_Root_Simple";
            RadioButton_Root_Simple.Size = new Size(59, 16);
            RadioButton_Root_Simple.TabIndex = 1;
            RadioButton_Root_Simple.TabStop = true;
            RadioButton_Root_Simple.Text = "Simple";
            RadioButton_Root_Simple.UseVisualStyleBackColor = true;
            // 
            // CheckBox_Root_Run
            // 
            CheckBox_Root_Run.Anchor = AnchorStyles.Left | AnchorStyles.Right;
            CheckBox_Root_Run.AutoSize = true;
            CheckBox_Root_Run.CheckAlign = ContentAlignment.TopCenter;
            CheckBox_Root_Run.Location = new Point(585, 10);
            CheckBox_Root_Run.Name = "CheckBox_Root_Run";
            CheckBox_Root_Run.Size = new Size(27, 30);
            CheckBox_Root_Run.TabIndex = 4;
            CheckBox_Root_Run.Text = "Run";
            CheckBox_Root_Run.TextAlign = ContentAlignment.BottomCenter;
            CheckBox_Root_Run.UseVisualStyleBackColor = true;
            CheckBox_Root_Run.CheckedChanged += CheckBox_Root_Run_CheckedChanged;
            // 
            // Timer_Root_Send
            // 
            Timer_Root_Send.Tick += Timer_Root_Send_Tick;
            // 
            // TextBox_Root_Data
            // 
            tableLayoutPanel1.SetColumnSpan(TextBox_Root_Data, 3);
            TextBox_Root_Data.Dock = DockStyle.Fill;
            TextBox_Root_Data.Location = new Point(3, 259);
            TextBox_Root_Data.MaxLength = 65535;
            TextBox_Root_Data.Multiline = true;
            TextBox_Root_Data.Name = "TextBox_Root_Data";
            TextBox_Root_Data.ScrollBars = ScrollBars.Vertical;
            TextBox_Root_Data.Size = new Size(680, 98);
            TextBox_Root_Data.TabIndex = 5;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(96F, 96F);
            AutoScaleMode = AutoScaleMode.Dpi;
            ClientSize = new Size(686, 360);
            Controls.Add(tableLayoutPanel1);
            Font = new Font("BIZ UDゴシック", 9F, FontStyle.Regular, GraphicsUnit.Point, 128);
            Margin = new Padding(3, 2, 3, 2);
            Name = "Form1";
            Text = "Form1";
            Load += Form1_Load;
            tableLayoutPanel1.ResumeLayout(false);
            tableLayoutPanel1.PerformLayout();
            tabControl1.ResumeLayout(false);
            TabPage_Simple.ResumeLayout(false);
            tableLayoutPanel3.ResumeLayout(false);
            tableLayoutPanel3.PerformLayout();
            tableLayoutPanel2.ResumeLayout(false);
            tableLayoutPanel2.PerformLayout();
            flowLayoutPanel1.ResumeLayout(false);
            flowLayoutPanel1.PerformLayout();
            ResumeLayout(false);
        }

        #endregion

        private TableLayoutPanel tableLayoutPanel1;
        private ComboBox ComboBox_Root_ComPort;
        private TabControl tabControl1;
        private TabPage TabPage_Full;
        private TabPage TabPage_Simple;
        private FlowLayoutPanel flowLayoutPanel1;
        private RadioButton RadioButton_Root_Full;
        private RadioButton RadioButton_Root_Simple;
        private TableLayoutPanel tableLayoutPanel3;
        private CheckBox CheckBox_Simple_Left;
        private CheckBox CheckBox_Simple_Right;
        private TableLayoutPanel tableLayoutPanel2;
        private CheckBox CheckBox_Simple_Up;
        private CheckBox CheckBox_Simple_Down;
        private CheckBox CheckBox_Root_Run;
        private System.Windows.Forms.Timer Timer_Root_Send;
        private TextBox TextBox_Root_Data;
    }
}
