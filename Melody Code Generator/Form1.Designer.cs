namespace Melody_Code_Generator
{
    partial class Form1
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.panel_bars = new System.Windows.Forms.Panel();
            this.panel_notes = new System.Windows.Forms.Panel();
            this.button_exit = new System.Windows.Forms.Button();
            this.button_generate = new System.Windows.Forms.Button();
            this.button_clear = new System.Windows.Forms.Button();
            this.button_undo = new System.Windows.Forms.Button();
            this.button_play = new System.Windows.Forms.Button();
            this.label_tempo = new System.Windows.Forms.Label();
            this.panel_playControls = new System.Windows.Forms.Panel();
            this.button_measureTempoByTaps = new System.Windows.Forms.Button();
            this.timer_tempoMeasure = new System.Windows.Forms.Timer(this.components);
            this.label_snap = new System.Windows.Forms.Label();
            this.numericUpDown_snap = new System.Windows.Forms.NumericUpDown();
            this.numericUpDown_tempo = new System.Windows.Forms.NumericUpDown();
            this.panel_playControls.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_snap)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_tempo)).BeginInit();
            this.SuspendLayout();
            // 
            // panel_bars
            // 
            this.panel_bars.BackColor = System.Drawing.Color.White;
            this.panel_bars.Location = new System.Drawing.Point(48, 12);
            this.panel_bars.Margin = new System.Windows.Forms.Padding(0, 3, 3, 3);
            this.panel_bars.Name = "panel_bars";
            this.panel_bars.Size = new System.Drawing.Size(832, 520);
            this.panel_bars.TabIndex = 8;
            this.panel_bars.Paint += new System.Windows.Forms.PaintEventHandler(this.panel_bars_Paint);
            this.panel_bars.MouseDown += new System.Windows.Forms.MouseEventHandler(this.panel_bars_MouseDown);
            this.panel_bars.MouseMove += new System.Windows.Forms.MouseEventHandler(this.panel_bars_MouseMove);
            this.panel_bars.MouseUp += new System.Windows.Forms.MouseEventHandler(this.panel_bars_MouseUp);
            // 
            // panel_notes
            // 
            this.panel_notes.BackColor = System.Drawing.Color.White;
            this.panel_notes.Location = new System.Drawing.Point(12, 12);
            this.panel_notes.Margin = new System.Windows.Forms.Padding(3, 3, 0, 3);
            this.panel_notes.Name = "panel_notes";
            this.panel_notes.Size = new System.Drawing.Size(36, 520);
            this.panel_notes.TabIndex = 9;
            this.panel_notes.Paint += new System.Windows.Forms.PaintEventHandler(this.panel_notes_Paint);
            this.panel_notes.MouseDown += new System.Windows.Forms.MouseEventHandler(this.panel_notes_MouseDown);
            // 
            // button_exit
            // 
            this.button_exit.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.button_exit.Location = new System.Drawing.Point(805, 538);
            this.button_exit.Name = "button_exit";
            this.button_exit.Size = new System.Drawing.Size(75, 23);
            this.button_exit.TabIndex = 0;
            this.button_exit.Text = "Exit";
            this.button_exit.UseVisualStyleBackColor = true;
            this.button_exit.Click += new System.EventHandler(this.button_exit_Click);
            // 
            // button_generate
            // 
            this.button_generate.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.button_generate.Location = new System.Drawing.Point(12, 538);
            this.button_generate.Name = "button_generate";
            this.button_generate.Size = new System.Drawing.Size(75, 23);
            this.button_generate.TabIndex = 7;
            this.button_generate.Text = "Generate";
            this.button_generate.UseVisualStyleBackColor = true;
            this.button_generate.Click += new System.EventHandler(this.button_generate_Click);
            // 
            // button_clear
            // 
            this.button_clear.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.button_clear.Location = new System.Drawing.Point(528, 538);
            this.button_clear.Name = "button_clear";
            this.button_clear.Size = new System.Drawing.Size(75, 23);
            this.button_clear.TabIndex = 2;
            this.button_clear.Text = "Clear";
            this.button_clear.UseVisualStyleBackColor = true;
            this.button_clear.Click += new System.EventHandler(this.button_clear_Click);
            // 
            // button_undo
            // 
            this.button_undo.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.button_undo.Location = new System.Drawing.Point(609, 538);
            this.button_undo.Name = "button_undo";
            this.button_undo.Size = new System.Drawing.Size(75, 23);
            this.button_undo.TabIndex = 1;
            this.button_undo.Text = "Undo";
            this.button_undo.UseVisualStyleBackColor = true;
            this.button_undo.Click += new System.EventHandler(this.button_undo_Click);
            // 
            // button_play
            // 
            this.button_play.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.button_play.Location = new System.Drawing.Point(249, 1);
            this.button_play.Name = "button_play";
            this.button_play.Size = new System.Drawing.Size(75, 19);
            this.button_play.TabIndex = 4;
            this.button_play.Text = "Play";
            this.button_play.UseVisualStyleBackColor = true;
            this.button_play.Click += new System.EventHandler(this.button_play_Click);
            // 
            // label_tempo
            // 
            this.label_tempo.AutoSize = true;
            this.label_tempo.Location = new System.Drawing.Point(139, 4);
            this.label_tempo.Name = "label_tempo";
            this.label_tempo.Size = new System.Drawing.Size(43, 13);
            this.label_tempo.TabIndex = 6;
            this.label_tempo.Text = "Tempo:";
            // 
            // panel_playControls
            // 
            this.panel_playControls.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel_playControls.Controls.Add(this.numericUpDown_tempo);
            this.panel_playControls.Controls.Add(this.button_measureTempoByTaps);
            this.panel_playControls.Controls.Add(this.button_play);
            this.panel_playControls.Controls.Add(this.label_tempo);
            this.panel_playControls.Location = new System.Drawing.Point(93, 538);
            this.panel_playControls.Name = "panel_playControls";
            this.panel_playControls.Size = new System.Drawing.Size(327, 23);
            this.panel_playControls.TabIndex = 3;
            // 
            // button_measureTempoByTaps
            // 
            this.button_measureTempoByTaps.FlatStyle = System.Windows.Forms.FlatStyle.System;
            this.button_measureTempoByTaps.Location = new System.Drawing.Point(2, 1);
            this.button_measureTempoByTaps.Name = "button_measureTempoByTaps";
            this.button_measureTempoByTaps.Size = new System.Drawing.Size(131, 19);
            this.button_measureTempoByTaps.TabIndex = 7;
            this.button_measureTempoByTaps.Text = "Measure Tempo by taps";
            this.button_measureTempoByTaps.UseVisualStyleBackColor = true;
            this.button_measureTempoByTaps.Click += new System.EventHandler(this.button_measureTempoByTaps_Click);
            // 
            // timer_tempoMeasure
            // 
            this.timer_tempoMeasure.Interval = 20;
            this.timer_tempoMeasure.Tick += new System.EventHandler(this.timer_tempoMeasure_Tick);
            // 
            // label_snap
            // 
            this.label_snap.AutoSize = true;
            this.label_snap.Location = new System.Drawing.Point(426, 543);
            this.label_snap.Name = "label_snap";
            this.label_snap.Size = new System.Drawing.Size(35, 13);
            this.label_snap.TabIndex = 6;
            this.label_snap.Text = "Snap:";
            // 
            // numericUpDown_snap
            // 
            this.numericUpDown_snap.Location = new System.Drawing.Point(467, 540);
            this.numericUpDown_snap.Maximum = new decimal(new int[] {
            16,
            0,
            0,
            0});
            this.numericUpDown_snap.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numericUpDown_snap.Name = "numericUpDown_snap";
            this.numericUpDown_snap.Size = new System.Drawing.Size(55, 20);
            this.numericUpDown_snap.TabIndex = 10;
            this.numericUpDown_snap.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numericUpDown_snap.ValueChanged += new System.EventHandler(this.numericUpDown_snap_ValueChanged);
            // 
            // numericUpDown_tempo
            // 
            this.numericUpDown_tempo.Location = new System.Drawing.Point(188, 1);
            this.numericUpDown_tempo.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.numericUpDown_tempo.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numericUpDown_tempo.Name = "numericUpDown_tempo";
            this.numericUpDown_tempo.Size = new System.Drawing.Size(55, 20);
            this.numericUpDown_tempo.TabIndex = 10;
            this.numericUpDown_tempo.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numericUpDown_tempo.ValueChanged += new System.EventHandler(this.numericUpDown_tempo_ValueChanged);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(892, 573);
            this.Controls.Add(this.numericUpDown_snap);
            this.Controls.Add(this.panel_playControls);
            this.Controls.Add(this.button_undo);
            this.Controls.Add(this.label_snap);
            this.Controls.Add(this.button_clear);
            this.Controls.Add(this.button_generate);
            this.Controls.Add(this.button_exit);
            this.Controls.Add(this.panel_notes);
            this.Controls.Add(this.panel_bars);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.KeyPreview = true;
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Arduino \"Melody\" Library - Melody Code Generator";
            this.SizeChanged += new System.EventHandler(this.Form1_SizeChanged);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.Form1_KeyDown);
            this.panel_playControls.ResumeLayout(false);
            this.panel_playControls.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_snap)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_tempo)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Panel panel_bars;
        private System.Windows.Forms.Panel panel_notes;
        private System.Windows.Forms.Button button_exit;
        private System.Windows.Forms.Button button_generate;
        private System.Windows.Forms.Button button_clear;
        private System.Windows.Forms.Button button_undo;
        private System.Windows.Forms.Button button_play;
        private System.Windows.Forms.Label label_tempo;
        private System.Windows.Forms.Panel panel_playControls;
        private System.Windows.Forms.Button button_measureTempoByTaps;
        private System.Windows.Forms.Timer timer_tempoMeasure;
        private System.Windows.Forms.Label label_snap;
        private System.Windows.Forms.NumericUpDown numericUpDown_snap;
        private System.Windows.Forms.NumericUpDown numericUpDown_tempo;
    }
}

