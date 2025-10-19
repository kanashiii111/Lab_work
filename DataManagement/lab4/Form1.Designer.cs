namespace lab4
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
        private void InitializeComponent()
        {
            dataGridView1 = new DataGridView();
            Id = new DataGridViewTextBoxColumn();
            name = new DataGridViewTextBoxColumn();
            lastName = new DataGridViewTextBoxColumn();
            Age = new DataGridViewTextBoxColumn();
            Faculty = new DataGridViewTextBoxColumn();
            facultyID = new DataGridViewTextBoxColumn();
            label1 = new Label();
            textBox1 = new TextBox();
            label2 = new Label();
            textBox2 = new TextBox();
            textBox3 = new TextBox();
            label3 = new Label();
            label4 = new Label();
            label5 = new Label();
            label6 = new Label();
            comboBox1 = new ComboBox();
            AddRowButton = new Button();
            DeleteRowButton = new Button();
            textBox4 = new TextBox();
            textBox5 = new TextBox();
            textBox6 = new TextBox();
            label7 = new Label();
            label8 = new Label();
            label9 = new Label();
            label10 = new Label();
            FilterButton = new Button();
            comboBox2 = new ComboBox();
            label11 = new Label();
            ((System.ComponentModel.ISupportInitialize)dataGridView1).BeginInit();
            SuspendLayout();
            // 
            // dataGridView1
            // 
            dataGridView1.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataGridView1.Columns.AddRange(new DataGridViewColumn[] { Id, name, lastName, Age, Faculty, facultyID });
            dataGridView1.Location = new Point(194, 176);
            dataGridView1.Name = "dataGridView1";
            dataGridView1.RowHeadersWidth = 51;
            dataGridView1.Size = new Size(804, 306);
            dataGridView1.TabIndex = 0;
            // 
            // Id
            // 
            Id.HeaderText = "ID";
            Id.MinimumWidth = 6;
            Id.Name = "Id";
            Id.Width = 125;
            // 
            // name
            // 
            name.HeaderText = "Имя";
            name.MinimumWidth = 6;
            name.Name = "name";
            name.Width = 125;
            // 
            // lastName
            // 
            lastName.HeaderText = "Фамилия";
            lastName.MinimumWidth = 6;
            lastName.Name = "lastName";
            lastName.Width = 125;
            // 
            // Age
            // 
            Age.HeaderText = "Возраст";
            Age.MinimumWidth = 6;
            Age.Name = "Age";
            Age.Width = 125;
            // 
            // Faculty
            // 
            Faculty.HeaderText = "Факультет";
            Faculty.MinimumWidth = 6;
            Faculty.Name = "Faculty";
            Faculty.Width = 125;
            // 
            // facultyID
            // 
            facultyID.HeaderText = "ID Факультета";
            facultyID.MinimumWidth = 6;
            facultyID.Name = "facultyID";
            facultyID.Width = 125;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Font = new Font("Segoe UI", 16F);
            label1.Location = new Point(12, 9);
            label1.Name = "label1";
            label1.Size = new Size(266, 37);
            label1.TabIndex = 1;
            label1.Text = "Таблица \"Студенты\"";
            // 
            // textBox1
            // 
            textBox1.Location = new Point(194, 606);
            textBox1.Name = "textBox1";
            textBox1.Size = new Size(159, 27);
            textBox1.TabIndex = 2;
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Font = new Font("Segoe UI", 16F);
            label2.Location = new Point(12, 521);
            label2.Name = "label2";
            label2.Size = new Size(263, 37);
            label2.TabIndex = 3;
            label2.Text = "Добавление записи";
            // 
            // textBox2
            // 
            textBox2.Location = new Point(359, 606);
            textBox2.Name = "textBox2";
            textBox2.Size = new Size(159, 27);
            textBox2.TabIndex = 4;
            // 
            // textBox3
            // 
            textBox3.Location = new Point(524, 607);
            textBox3.Name = "textBox3";
            textBox3.Size = new Size(152, 27);
            textBox3.TabIndex = 5;
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new Point(194, 578);
            label3.Name = "label3";
            label3.Size = new Size(39, 20);
            label3.TabIndex = 7;
            label3.Text = "Имя";
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.Location = new Point(359, 578);
            label4.Name = "label4";
            label4.Size = new Size(73, 20);
            label4.TabIndex = 8;
            label4.Text = "Фамилия";
            // 
            // label5
            // 
            label5.AutoSize = true;
            label5.Location = new Point(524, 578);
            label5.Name = "label5";
            label5.Size = new Size(64, 20);
            label5.TabIndex = 9;
            label5.Text = "Возраст";
            // 
            // label6
            // 
            label6.AutoSize = true;
            label6.Location = new Point(682, 578);
            label6.Name = "label6";
            label6.Size = new Size(78, 20);
            label6.TabIndex = 10;
            label6.Text = "Факультет";
            // 
            // comboBox1
            // 
            comboBox1.FormattingEnabled = true;
            comboBox1.Items.AddRange(new object[] { "ФАВТ", "ФКиФМН", "ФПиП", "ФФКиС" });
            comboBox1.Location = new Point(682, 606);
            comboBox1.Name = "comboBox1";
            comboBox1.Size = new Size(159, 28);
            comboBox1.TabIndex = 11;
            // 
            // AddRowButton
            // 
            AddRowButton.Location = new Point(847, 603);
            AddRowButton.Name = "AddRowButton";
            AddRowButton.Size = new Size(230, 32);
            AddRowButton.TabIndex = 12;
            AddRowButton.Text = "Добавить запись";
            AddRowButton.UseVisualStyleBackColor = true;
            AddRowButton.Click += button1_Click;
            // 
            // DeleteRowButton
            // 
            DeleteRowButton.Location = new Point(847, 528);
            DeleteRowButton.Name = "DeleteRowButton";
            DeleteRowButton.Size = new Size(230, 30);
            DeleteRowButton.TabIndex = 13;
            DeleteRowButton.Text = "Удалить выбранную строку";
            DeleteRowButton.UseVisualStyleBackColor = true;
            DeleteRowButton.Click += button1_Click_1;
            // 
            // textBox4
            // 
            textBox4.Location = new Point(524, 111);
            textBox4.Name = "textBox4";
            textBox4.Size = new Size(152, 27);
            textBox4.TabIndex = 16;
            // 
            // textBox5
            // 
            textBox5.Location = new Point(359, 110);
            textBox5.Name = "textBox5";
            textBox5.Size = new Size(159, 27);
            textBox5.TabIndex = 15;
            // 
            // textBox6
            // 
            textBox6.Location = new Point(194, 110);
            textBox6.Name = "textBox6";
            textBox6.Size = new Size(159, 27);
            textBox6.TabIndex = 14;
            // 
            // label7
            // 
            label7.AutoSize = true;
            label7.Location = new Point(682, 87);
            label7.Name = "label7";
            label7.Size = new Size(78, 20);
            label7.TabIndex = 21;
            label7.Text = "Факультет";
            // 
            // label8
            // 
            label8.AutoSize = true;
            label8.Location = new Point(524, 87);
            label8.Name = "label8";
            label8.Size = new Size(64, 20);
            label8.TabIndex = 20;
            label8.Text = "Возраст";
            // 
            // label9
            // 
            label9.AutoSize = true;
            label9.Location = new Point(359, 87);
            label9.Name = "label9";
            label9.Size = new Size(73, 20);
            label9.TabIndex = 19;
            label9.Text = "Фамилия";
            // 
            // label10
            // 
            label10.AutoSize = true;
            label10.Location = new Point(194, 87);
            label10.Name = "label10";
            label10.Size = new Size(39, 20);
            label10.TabIndex = 18;
            label10.Text = "Имя";
            // 
            // FilterButton
            // 
            FilterButton.Location = new Point(847, 110);
            FilterButton.Name = "FilterButton";
            FilterButton.Size = new Size(230, 30);
            FilterButton.TabIndex = 22;
            FilterButton.Text = "Сохранить";
            FilterButton.UseVisualStyleBackColor = true;
            FilterButton.Click += button2_Click;
            // 
            // comboBox2
            // 
            comboBox2.FormattingEnabled = true;
            comboBox2.Items.AddRange(new object[] { "ФАВТ", "ФКиФМН", "ФПиП", "ФФКиС" });
            comboBox2.Location = new Point(682, 111);
            comboBox2.Name = "comboBox2";
            comboBox2.Size = new Size(159, 28);
            comboBox2.TabIndex = 23;
            // 
            // label11
            // 
            label11.AutoSize = true;
            label11.Font = new Font("Segoe UI", 12F);
            label11.Location = new Point(96, 109);
            label11.Name = "label11";
            label11.Size = new Size(80, 28);
            label11.TabIndex = 24;
            label11.Text = "Фильтр";
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(1255, 669);
            Controls.Add(label11);
            Controls.Add(comboBox2);
            Controls.Add(FilterButton);
            Controls.Add(label7);
            Controls.Add(label8);
            Controls.Add(label9);
            Controls.Add(label10);
            Controls.Add(textBox4);
            Controls.Add(textBox5);
            Controls.Add(textBox6);
            Controls.Add(DeleteRowButton);
            Controls.Add(AddRowButton);
            Controls.Add(comboBox1);
            Controls.Add(label6);
            Controls.Add(label5);
            Controls.Add(label4);
            Controls.Add(label3);
            Controls.Add(textBox3);
            Controls.Add(textBox2);
            Controls.Add(label2);
            Controls.Add(textBox1);
            Controls.Add(label1);
            Controls.Add(dataGridView1);
            Name = "Form1";
            Text = "Form1";
            Load += Form1_Load;
            ((System.ComponentModel.ISupportInitialize)dataGridView1).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private DataGridView dataGridView1;
        private Label label1;
        private TextBox textBox1;
        private Label label2;
        private TextBox textBox2;
        private TextBox textBox3;
        private Label label3;
        private Label label4;
        private Label label5;
        private Label label6;
        private ComboBox comboBox1;
        private Button AddRowButton;
        private DataGridViewTextBoxColumn Id;
        private DataGridViewTextBoxColumn name;
        private DataGridViewTextBoxColumn lastName;
        private DataGridViewTextBoxColumn Age;
        private DataGridViewTextBoxColumn Faculty;
        private DataGridViewTextBoxColumn facultyID;
        private Button DeleteRowButton;
        private TextBox textBox4;
        private TextBox textBox5;
        private TextBox textBox6;
        private Label label7;
        private Label label8;
        private Label label9;
        private Label label10;
        private Button FilterButton;
        private ComboBox comboBox2;
        private Label label11;
    }
}
