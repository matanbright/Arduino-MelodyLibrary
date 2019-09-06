namespace Melody_Code_Generator
{
    partial class Form2
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
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
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form2));
            this.label_melodyName = new System.Windows.Forms.Label();
            this.textBox_melodyName = new System.Windows.Forms.TextBox();
            this.checkBox_usePianoNotesFrequencies = new System.Windows.Forms.CheckBox();
            this.richTextBox_generatedCode = new System.Windows.Forms.RichTextBox();
            this.label_generatedCode = new System.Windows.Forms.Label();
            this.button_save = new System.Windows.Forms.Button();
            this.button_copy = new System.Windows.Forms.Button();
            this.button_close = new System.Windows.Forms.Button();
            this.checkBox_removeFreeSpaceAfterTheLastNote = new System.Windows.Forms.CheckBox();
            this.SuspendLayout();
            // 
            // label_melodyName
            // 
            this.label_melodyName.AutoSize = true;
            this.label_melodyName.Location = new System.Drawing.Point(12, 15);
            this.label_melodyName.Name = "label_melodyName";
            this.label_melodyName.Size = new System.Drawing.Size(73, 13);
            this.label_melodyName.TabIndex = 0;
            this.label_melodyName.Text = "Melody name:";
            // 
            // textBox_melodyName
            // 
            this.textBox_melodyName.Location = new System.Drawing.Point(91, 12);
            this.textBox_melodyName.Name = "textBox_melodyName";
            this.textBox_melodyName.Size = new System.Drawing.Size(279, 20);
            this.textBox_melodyName.TabIndex = 1;
            this.textBox_melodyName.TextChanged += new System.EventHandler(this.textBox_songName_TextChanged);
            // 
            // checkBox_usePianoNotesFrequencies
            // 
            this.checkBox_usePianoNotesFrequencies.AutoSize = true;
            this.checkBox_usePianoNotesFrequencies.Location = new System.Drawing.Point(12, 72);
            this.checkBox_usePianoNotesFrequencies.Name = "checkBox_usePianoNotesFrequencies";
            this.checkBox_usePianoNotesFrequencies.Size = new System.Drawing.Size(289, 17);
            this.checkBox_usePianoNotesFrequencies.TabIndex = 2;
            this.checkBox_usePianoNotesFrequencies.Text = "Use piano notes frequencies instead of notes definitions";
            this.checkBox_usePianoNotesFrequencies.UseVisualStyleBackColor = true;
            this.checkBox_usePianoNotesFrequencies.CheckedChanged += new System.EventHandler(this.checkBox_usePianoNotesFrequencies_CheckedChanged);
            // 
            // richTextBox_generatedCode
            // 
            this.richTextBox_generatedCode.AcceptsTab = true;
            this.richTextBox_generatedCode.Location = new System.Drawing.Point(12, 128);
            this.richTextBox_generatedCode.Name = "richTextBox_generatedCode";
            this.richTextBox_generatedCode.ReadOnly = true;
            this.richTextBox_generatedCode.Size = new System.Drawing.Size(358, 276);
            this.richTextBox_generatedCode.TabIndex = 3;
            this.richTextBox_generatedCode.Text = "";
            // 
            // label_generatedCode
            // 
            this.label_generatedCode.AutoSize = true;
            this.label_generatedCode.Location = new System.Drawing.Point(12, 112);
            this.label_generatedCode.Name = "label_generatedCode";
            this.label_generatedCode.Size = new System.Drawing.Size(87, 13);
            this.label_generatedCode.TabIndex = 8;
            this.label_generatedCode.Text = "Generated code:";
            // 
            // button_save
            // 
            this.button_save.Location = new System.Drawing.Point(12, 410);
            this.button_save.Name = "button_save";
            this.button_save.Size = new System.Drawing.Size(75, 23);
            this.button_save.TabIndex = 9;
            this.button_save.Text = "Save";
            this.button_save.UseVisualStyleBackColor = true;
            this.button_save.Click += new System.EventHandler(this.button_save_Click);
            // 
            // button_copy
            // 
            this.button_copy.Location = new System.Drawing.Point(93, 410);
            this.button_copy.Name = "button_copy";
            this.button_copy.Size = new System.Drawing.Size(75, 23);
            this.button_copy.TabIndex = 9;
            this.button_copy.Text = "Copy";
            this.button_copy.UseVisualStyleBackColor = true;
            this.button_copy.Click += new System.EventHandler(this.button_copy_Click);
            // 
            // button_close
            // 
            this.button_close.Location = new System.Drawing.Point(295, 410);
            this.button_close.Name = "button_close";
            this.button_close.Size = new System.Drawing.Size(75, 23);
            this.button_close.TabIndex = 10;
            this.button_close.Text = "Close";
            this.button_close.UseVisualStyleBackColor = true;
            this.button_close.Click += new System.EventHandler(this.button_close_Click);
            // 
            // checkBox_removeFreeSpaceAfterTheLastNote
            // 
            this.checkBox_removeFreeSpaceAfterTheLastNote.AutoSize = true;
            this.checkBox_removeFreeSpaceAfterTheLastNote.Location = new System.Drawing.Point(12, 49);
            this.checkBox_removeFreeSpaceAfterTheLastNote.Name = "checkBox_removeFreeSpaceAfterTheLastNote";
            this.checkBox_removeFreeSpaceAfterTheLastNote.Size = new System.Drawing.Size(222, 17);
            this.checkBox_removeFreeSpaceAfterTheLastNote.TabIndex = 2;
            this.checkBox_removeFreeSpaceAfterTheLastNote.Text = "Remove the free space after the last note";
            this.checkBox_removeFreeSpaceAfterTheLastNote.UseVisualStyleBackColor = true;
            this.checkBox_removeFreeSpaceAfterTheLastNote.CheckedChanged += new System.EventHandler(this.checkBox_usePianoNotesFrequencies_CheckedChanged);
            // 
            // Form2
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(382, 445);
            this.Controls.Add(this.button_close);
            this.Controls.Add(this.button_copy);
            this.Controls.Add(this.button_save);
            this.Controls.Add(this.label_generatedCode);
            this.Controls.Add(this.richTextBox_generatedCode);
            this.Controls.Add(this.checkBox_removeFreeSpaceAfterTheLastNote);
            this.Controls.Add(this.checkBox_usePianoNotesFrequencies);
            this.Controls.Add(this.textBox_melodyName);
            this.Controls.Add(this.label_melodyName);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Form2";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Generate melody code";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form2_FormClosed);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label_melodyName;
        private System.Windows.Forms.TextBox textBox_melodyName;
        private System.Windows.Forms.CheckBox checkBox_usePianoNotesFrequencies;
        private System.Windows.Forms.RichTextBox richTextBox_generatedCode;
        private System.Windows.Forms.Label label_generatedCode;
        private System.Windows.Forms.Button button_save;
        private System.Windows.Forms.Button button_copy;
        private System.Windows.Forms.Button button_close;
        private System.Windows.Forms.CheckBox checkBox_removeFreeSpaceAfterTheLastNote;
    }
}