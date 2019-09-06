using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace Melody_Code_Generator
{
    public partial class Form2 : Form
    {
        string code;

        public Form2()
        {
            InitializeComponent();
            code = "";
            generateCodeAndUpdate();
        }

        private void Form2_FormClosed(object sender, FormClosedEventArgs e)
        {
            if (Form1.notes[Form1.notes.Count() - 1].GetPianoNote().GetFrequency() == 0)
                Form1.notes.RemoveAt(Form1.notes.Count() - 1);
        }

        private void textBox_songName_TextChanged(object sender, EventArgs e)
        {
            string newText = "";
            foreach (char character in textBox_melodyName.Text)
                if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z') || (character >= '0' && character <= '9'))
                    newText += character;
            textBox_melodyName.Text = newText;
            generateCodeAndUpdate();
        }

        private void checkBox_immediatelyStartSong_CheckedChanged(object sender, EventArgs e)
        {
            generateCodeAndUpdate();
        }

        private void checkBox_usePianoNotesFrequencies_CheckedChanged(object sender, EventArgs e)
        {
            generateCodeAndUpdate();
        }

        private void button_close_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void button_copy_Click(object sender, EventArgs e)
        {
            Clipboard.SetText(code);
            MessageBox.Show("Copied to clipboard successfully!");
        }

        private void button_save_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            saveFileDialog.Filter = "Text file (.txt)|*.txt";
            saveFileDialog.FileName = textBox_melodyName.Text;
            if (saveFileDialog.ShowDialog() == DialogResult.OK)
            {
                File.WriteAllText(saveFileDialog.FileName, code);
                MessageBox.Show("File created successfully!");
            }
        }

        private void generateCodeAndUpdate()
        {
            code = "";
            code += "void initializeMelody" + (textBox_melodyName.Text).Replace(" ", "") + "(Melody &melody) {" + Environment.NewLine;
            code += "\tmelody.clear();" + Environment.NewLine;
            code += "\tmelody.setTempo(" + Form1.tempo + ");" + Environment.NewLine;
            code += "\tmelody.setSnap(" + Form1.snap + ");" + Environment.NewLine;
            for (int i = 0; i < Form1.notes.Count; i++)
            {
                if (!(i == Form1.notes.Count() - 1 && checkBox_removeFreeSpaceAfterTheLastNote.Checked && Form1.notes[Form1.notes.Count() - 1].GetPianoNote().GetFrequency() == 0))
                {
                    if (checkBox_usePianoNotesFrequencies.Checked)
                        code += "\tmelody.addNote(" + Form1.notes[i].GetPianoNote().GetFrequency() + ", " + Form1.notes[i].GetNoteBars() + ");" + Environment.NewLine;
                    else
                        code += "\tmelody.addNote(" + "NOTE_" + Form1.notes[i].GetPianoNote().GetName() + ", " + Form1.notes[i].GetNoteBars() + ");" + Environment.NewLine;
                }
            }
            code += "}" + Environment.NewLine;
            richTextBox_generatedCode.Text = code;
        }
    }
}
