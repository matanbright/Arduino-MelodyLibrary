using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using System.IO;
using System.Diagnostics;

namespace Melody_Code_Generator
{
    public partial class Form1 : Form
    {
        const int NOTES_GROUP_OCTAVES = 12;
        const int BEATS_PER_SEGMENT = 4;
        const int SEGMENTS_PER_SECTION = 4;
        const int FORM_MINIMUM_WIDTH = 900;
        const int FORM_MINIMUM_HEIGHT = 600;
        const int DEFAULT_TEMPO = 120;
        const int DEFAULT_SNAP = 4;

        PianoNote[] pianoNotes = new PianoNote[]
        {
            #region Notes declaration
            new PianoNote("C8", 4186),

            new PianoNote("B7", 3951),
            new PianoNote("AB7", 3729),
            new PianoNote("A7", 3520),
            new PianoNote("GA7", 3322),
            new PianoNote("G7", 3136),
            new PianoNote("FG7", 2960),
            new PianoNote("F7", 2794),
            new PianoNote("E7", 2637),
            new PianoNote("DE7", 2489),
            new PianoNote("D7", 2349),
            new PianoNote("CD7", 2217),
            new PianoNote("C7", 2093),

            new PianoNote("B6", 1976),
            new PianoNote("AB6", 1865),
            new PianoNote("A6", 1760),
            new PianoNote("GA6", 1661),
            new PianoNote("G6", 1568),
            new PianoNote("FG6", 1480),
            new PianoNote("F6", 1397),
            new PianoNote("E6", 1319),
            new PianoNote("DE6", 1245),
            new PianoNote("D6", 1175),
            new PianoNote("CD6", 1109),
            new PianoNote("C6", 1047),

            new PianoNote("B5", 988),
            new PianoNote("AB5", 932),
            new PianoNote("A5", 880),
            new PianoNote("GA5", 831),
            new PianoNote("G5", 784),
            new PianoNote("FG5", 740),
            new PianoNote("F5", 698),
            new PianoNote("E5", 659),
            new PianoNote("DE5", 622),
            new PianoNote("D5", 587),
            new PianoNote("CD5", 554),
            new PianoNote("C5", 523),

            new PianoNote("B4", 494),
            new PianoNote("AB4", 466),
            new PianoNote("A4", 440),
            new PianoNote("GA4", 415),
            new PianoNote("G4", 392),
            new PianoNote("FG4", 370),
            new PianoNote("F4", 349),
            new PianoNote("E4", 330),
            new PianoNote("DE4", 311),
            new PianoNote("D4", 294),
            new PianoNote("CD4", 277),
            new PianoNote("C4", 262),

            new PianoNote("B3", 247),
            new PianoNote("AB3", 233),
            new PianoNote("A3", 220),
            new PianoNote("GA3", 208),
            new PianoNote("G3", 196),
            new PianoNote("FG3", 185),
            new PianoNote("F3", 175),
            new PianoNote("E3", 165),
            new PianoNote("DE3", 156),
            new PianoNote("D3", 147),
            new PianoNote("CD3", 139),
            new PianoNote("C3", 131),

            new PianoNote("B2", 123),
            new PianoNote("AB2", 117),
            new PianoNote("A2", 110),
            new PianoNote("GA2", 104),
            new PianoNote("G2", 98),
            new PianoNote("FG2", 92),
            new PianoNote("F2", 87),
            new PianoNote("E2", 82),
            new PianoNote("DE2", 78),
            new PianoNote("D2", 73),
            new PianoNote("CD2", 69),
            new PianoNote("C2", 65),

            new PianoNote("B1", 62),
            new PianoNote("AB1", 58),
            new PianoNote("A1", 55),
            new PianoNote("GA1", 52),
            new PianoNote("G1", 49),
            new PianoNote("FG1", 46),
            new PianoNote("F1", 44),
            new PianoNote("E1", 41),
            new PianoNote("DE1", 39),
            new PianoNote("D1", 37),
            new PianoNote("CD1", 35),
            new PianoNote("C1", 33),

            new PianoNote("NULL", 0)
            #endregion
        };

        Size formCurrentSize;
        float barsWidth, barsHeight;
        public static List<Note> notes;
        public static int tempo;
        public static int snap;
        bool holdingNote;
        Point mouseDownLocation;
        Point mouseMoveLocation;
        volatile bool playing;
        Thread playingThread;
        int highlightedNoteIndex;
        bool measuringtempo;
        Stopwatch tempoMeasureStopWatch;
        long tempoMeasureCurrentMillisecondsForRecordingInterval;
        long tempoMeasureCurrentMillisecondsForEndingMeasurement;
        List<long> tempoMeasureIntervals;



        public Form1()
        {
            InitializeComponent();
            formCurrentSize = this.Size;
            this.MinimumSize = new Size(FORM_MINIMUM_WIDTH, FORM_MINIMUM_HEIGHT);
            numericUpDown_tempo.Value = DEFAULT_TEMPO;
            numericUpDown_snap.Value = DEFAULT_SNAP;
            tempo = DEFAULT_TEMPO;
            snap = DEFAULT_SNAP;
            barsWidth = (float)panel_bars.Width / (snap * BEATS_PER_SEGMENT * SEGMENTS_PER_SECTION);
            barsHeight = (float)panel_bars.Height / (pianoNotes.Length - 1);
            notes = new List<Note>();
            holdingNote = false;
            mouseDownLocation = new Point();
            mouseMoveLocation = new Point();
            playing = false;
            playingThread = null;
            highlightedNoteIndex = -1;
            measuringtempo = false;
            tempoMeasureStopWatch = new Stopwatch();
            tempoMeasureCurrentMillisecondsForRecordingInterval = 0;
            tempoMeasureCurrentMillisecondsForEndingMeasurement = 0;
            tempoMeasureIntervals = new List<long>();
        }

        private void panel_bars_Paint(object sender, PaintEventArgs e)
        {
            for (int i = 0; i < pianoNotes.Length - 1; i++)
            {
                Pen pen;
                if ((i - 1) % NOTES_GROUP_OCTAVES == 0)
                    pen = new Pen(Color.Blue, 1);
                else
                    pen = new Pen(Color.Gray, 1);
                e.Graphics.DrawLine(pen, new Point(0, (int)(barsHeight * i)), new Point(panel_bars.Width, (int)(barsHeight * i)));
                if (i == highlightedNoteIndex)
                    e.Graphics.FillRectangle(Brushes.Yellow, new Rectangle(new Point(0, (int)(barsHeight * i) + 1), new Size(panel_bars.Width, (int)barsHeight - 1)));
            }

            for (int i = 0; i < snap * BEATS_PER_SEGMENT * SEGMENTS_PER_SECTION; i++)
            {
                Pen pen;
                if (i % snap == 0)
                {
                    if ((i / snap) % BEATS_PER_SEGMENT == 0)
                        pen = new Pen(Color.Red, 3);
                    else
                        pen = new Pen(Color.Red, 1);
                }
                else
                    pen = new Pen(Color.Gray, 1);
                e.Graphics.DrawLine(pen, new Point((int)(barsWidth * i), 0), new Point((int)(barsWidth * i), panel_bars.Height));
            }

            foreach (Note note in notes)
                e.Graphics.FillRectangle(Brushes.Blue, new Rectangle(new Point((int)(note.GetStartBar() * barsWidth) + 1, (int)(note.GetPianoNote().GetNoteIndex() * barsHeight) + 1), new Size((int)(note.GetNoteBars() * barsWidth) - 2, (int)barsHeight - 2)));

            if (holdingNote)
            {
                Bar startBar = GetBarAtLocation(new Point(mouseDownLocation.X, mouseDownLocation.Y));
                int noteBars = GetBarsCountBetweenXLocations(mouseDownLocation.X, mouseMoveLocation.X);
                Note noteInHold = new Note(pianoNotes[startBar.GetYIndex()], startBar.GetXIndex(), noteBars);
                e.Graphics.FillRectangle(Brushes.Blue, new Rectangle(new Point((int)(noteInHold.GetStartBar() * barsWidth) + 1, (int)(noteInHold.GetPianoNote().GetNoteIndex() * barsHeight) + 1), new Size((int)(noteInHold.GetNoteBars() * barsWidth) - 2, (int)barsHeight - 2)));
            }
        }

        private void panel_notes_Paint(object sender, PaintEventArgs e)
        {
            float barsVerticalMargin = (float)panel_bars.Height / (pianoNotes.Length - 1);

            for (int i = 0; i < pianoNotes.Length - 1; i++)
            {
                Brush brush;
                if (pianoNotes[i].GetName().Length == 2)
                    brush = Brushes.Black;
                else
                    brush = Brushes.Gray;
                e.Graphics.DrawString(pianoNotes[i].GetName(), new Font("Tahoma", barsVerticalMargin - 2), brush, new PointF(0, (int)(barsVerticalMargin * i)));
            }
        }

        private void Form1_SizeChanged(object sender, EventArgs e)
        {
            if (this.WindowState != FormWindowState.Minimized)
            {
                panel_notes.Size = new Size(panel_notes.Width, panel_notes.Height + (this.Height - formCurrentSize.Height));
                panel_bars.Size = new Size(panel_bars.Width + (this.Width - formCurrentSize.Width), panel_bars.Height + (this.Height - formCurrentSize.Height));
                button_exit.Location = new Point(button_exit.Location.X + (this.Width - formCurrentSize.Width), button_exit.Location.Y + (this.Height - formCurrentSize.Height));
                button_generate.Location = new Point(button_generate.Location.X, button_generate.Location.Y + (this.Height - formCurrentSize.Height));
                panel_playControls.Location = new Point(panel_playControls.Location.X, panel_playControls.Location.Y + (this.Height - formCurrentSize.Height));
                label_snap.Location = new Point(label_snap.Location.X, label_snap.Location.Y + (this.Height - formCurrentSize.Height));
                numericUpDown_snap.Location = new Point(numericUpDown_snap.Location.X, numericUpDown_snap.Location.Y + (this.Height - formCurrentSize.Height));
                button_clear.Location = new Point(button_clear.Location.X, button_clear.Location.Y + (this.Height - formCurrentSize.Height));
                button_undo.Location = new Point(button_undo.Location.X, button_undo.Location.Y + (this.Height - formCurrentSize.Height));
                formCurrentSize = this.Size;
                barsWidth = (float)panel_bars.Width / (snap * BEATS_PER_SEGMENT * SEGMENTS_PER_SECTION);
                barsHeight = (float)panel_bars.Height / (pianoNotes.Length - 1);
                this.Refresh();
            }
        }

        private void panel_bars_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                if (notes.Count == 0)
                {
                    holdingNote = true;
                    numericUpDown_snap.Enabled = false;
                    highlightedNoteIndex = -1;
                    mouseDownLocation = e.Location;
                    int noteIndex = GetBarAtLocation(e.Location).GetYIndex();
                    playingThread = new Thread(new ParameterizedThreadStart(PlayNote));
                    playingThread.Start(pianoNotes[noteIndex].GetFrequency());
                    this.Refresh();
                }
                else
                {
                    if (GetBarAtLocation(e.Location).GetXIndex() > notes.Last().GetStartBar() + notes.Last().GetNoteBars() - 1)
                    {
                        holdingNote = true;
                        highlightedNoteIndex = -1;
                        mouseDownLocation = e.Location;
                        int noteIndex = GetBarAtLocation(e.Location).GetYIndex();
                        playingThread = new Thread(new ParameterizedThreadStart(PlayNote));
                        playingThread.Start(pianoNotes[noteIndex].GetFrequency());
                        this.Refresh();
                    }
                    else
                        MessageBox.Show("You can put notes only after the last note!");
                }
            }
        }

        private void panel_bars_MouseMove(object sender, MouseEventArgs e)
        {
            if (holdingNote)
            {
                if (e.Location.X < panel_bars.Width)
                    mouseMoveLocation = e.Location;
                else
                    mouseMoveLocation = new Point(panel_bars.Width - 1, e.Location.Y);
                this.Refresh();
            }
        }

        private void panel_bars_MouseUp(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                if (holdingNote)
                {
                    holdingNote = false;
                    Bar startBar = GetBarAtLocation(new Point(mouseDownLocation.X, mouseDownLocation.Y));
                    int noteBars = 0;
                    if (e.Location.X < panel_bars.Width)
                        noteBars = GetBarsCountBetweenXLocations(mouseDownLocation.X, e.Location.X);
                    else
                        noteBars = GetBarsCountBetweenXLocations(mouseDownLocation.X, panel_bars.Width - 1);
                    if (noteBars > 0)
                    {
                        Bar nullNoteStartBar;
                        int nullNoteBars;
                        if (notes.Count() == 0)
                        {
                            nullNoteStartBar = new Bar(0, pianoNotes.Length - 1);
                            nullNoteBars = startBar.GetXIndex();
                        }
                        else
                        {
                            nullNoteStartBar = new Bar(notes[notes.Count() - 1].GetStartBar() + notes[notes.Count() - 1].GetNoteBars(), pianoNotes.Length - 1);
                            nullNoteBars = startBar.GetXIndex() - (notes[notes.Count() - 1].GetStartBar() + notes[notes.Count() - 1].GetNoteBars());
                        }
                        if (nullNoteBars > 0)
                            notes.Add(new Note(pianoNotes[nullNoteStartBar.GetYIndex()], nullNoteStartBar.GetXIndex(), nullNoteBars));
                        notes.Add(new Note(pianoNotes[startBar.GetYIndex()], startBar.GetXIndex(), noteBars));
                    }
                    else if (notes.Count == 0)
                        numericUpDown_snap.Enabled = true;
                    mouseDownLocation = new Point();
                    mouseMoveLocation = new Point();
                    this.Refresh();
                }
            }
        }

        private void button_exit_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void button_generate_Click(object sender, EventArgs e)
        {
            OpenGenerationForm();
        }

        private void OpenGenerationForm()
        {
            int endNullNoteBars = 0;
            if (notes.Count() == 0)
            {
                endNullNoteBars = GetBarsCountBetweenXLocations(1, panel_bars.Width - 1);
                if (endNullNoteBars > 0)
                    notes.Add(new Note(pianoNotes[pianoNotes.Length - 1], 0, endNullNoteBars));
            }
            else
            {
                endNullNoteBars = GetBarsCountBetweenXLocations((int)(barsWidth * (notes[notes.Count() - 1].GetStartBar() + notes[notes.Count() - 1].GetNoteBars())) + 1, panel_bars.Width - 1);
                if (endNullNoteBars > 0)
                    notes.Add(new Note(pianoNotes[pianoNotes.Length - 1], notes[notes.Count() - 1].GetStartBar() + notes[notes.Count() - 1].GetNoteBars(), endNullNoteBars));
            }
            (new Form2()).ShowDialog(this);
        }

        private void button_play_Click(object sender, EventArgs e)
        {
            Play();
        }

        private void Play()
        {
            if (!playing)
            {
                if (tempo > 0)
                {
                    playing = true;
                    ChangeInterfaceToPlayMode(true);
                    playingThread = new Thread(new ParameterizedThreadStart(PlaySong));
                    playingThread.Start(tempo);
                }
                else
                    MessageBox.Show("tempo must be larger than 0!");
            }
            else
            {
                playing = false;
                ChangeInterfaceToPlayMode(false);
                playingThread.Abort();
            }
        }

        void PlaySong(object tempo)
        {
            float bps = (int)tempo / 60.0F;
            foreach (Note note in notes)
            {
                int noteDuration = (int)(1.0 / bps * 1000.0 / snap * note.GetNoteBars());
                if (note.GetPianoNote().GetFrequency() == 0)
                    Thread.Sleep(noteDuration);
                else
                    Console.Beep(note.GetPianoNote().GetFrequency(), noteDuration);
                
            }
            int endNullNoteBars = 0;
            if (notes.Count == 0)
                endNullNoteBars = GetBarsCountBetweenXLocations(1, panel_bars.Width - 1);
            else
                endNullNoteBars = GetBarsCountBetweenXLocations((int)(barsWidth * (notes[notes.Count() - 1].GetStartBar() + notes[notes.Count() - 1].GetNoteBars())) + 1, panel_bars.Width - 1);
            if (endNullNoteBars > 0)
            {
                int endNullNoteDuration = (int)(1.0 / bps * 1000.0 / snap * endNullNoteBars);
                Thread.Sleep(endNullNoteDuration);
            }
            playing = false;
            ChangeInterfaceToPlayMode(false);
        }

        void PlayNote(object frequency)
        {
            if ((int)frequency >= 37 && (int)frequency <= 32767)
                Console.Beep((int)frequency, 250);
        }

        private void button_clear_Click(object sender, EventArgs e)
        {
            Clear();
        }

        private void button_undo_Click(object sender, EventArgs e)
        {
            Undo();
        }

        private void Clear()
        {
            if (notes.Count() > 0)
            {
                notes.Clear();
                this.Refresh();
            }
            if (highlightedNoteIndex > -1)
            {
                highlightedNoteIndex = -1;
                this.Refresh();
            }
            numericUpDown_snap.Enabled = true;
        }

        private void Undo()
        {
            if (notes.Count() > 0)
            {
                notes.RemoveAt(notes.Count() - 1);
                if (notes.Count() > 0)
                    if (notes[notes.Count() - 1].GetPianoNote().GetFrequency() == 0)
                        notes.RemoveAt(notes.Count() - 1);
                this.Refresh();
            }
            if (notes.Count() == 0)
                numericUpDown_snap.Enabled = true;
        }

        private Bar GetBarAtLocation(Point location)
        {
            return new Bar((int)(location.X / barsWidth), (int)(location.Y / barsHeight));
        }

        private int GetBarsCountBetweenXLocations(int startXLocation, int endXLocation)
        {
            return ((int)(endXLocation / barsWidth)) - ((int)(startXLocation / barsWidth)) + 1;
        }

        private void ChangeInterfaceToPlayMode(bool isPlaying)
        {
            if (isPlaying)
                button_play.Text = "Stop";
            else
                button_play.Text = "Play";
            panel_notes.Enabled = !isPlaying;
            panel_bars.Enabled = !isPlaying;
            numericUpDown_tempo.Enabled = !isPlaying;
            button_measureTempoByTaps.Enabled = !isPlaying;
            button_generate.Enabled = !isPlaying;
            if (notes.Count == 0)
                numericUpDown_snap.Enabled = !isPlaying;
            button_clear.Enabled = !isPlaying;
            button_undo.Enabled = !isPlaying;
        }

        private void ChangeInterfaceToTempoMeasuringMode(bool isMeasuring)
        {
            if (isMeasuring)
                button_measureTempoByTaps.Text = "Measuring tempo...";
            else
                button_measureTempoByTaps.Text = "Measure tempo by taps";
            panel_notes.Enabled = !isMeasuring;
            panel_bars.Enabled = !isMeasuring;
            button_play.Enabled = !isMeasuring;
            numericUpDown_tempo.Enabled = !isMeasuring;
            button_generate.Enabled = !isMeasuring;
            if (notes.Count == 0)
                numericUpDown_snap.Enabled = !isMeasuring;
            button_clear.Enabled = !isMeasuring;
            button_undo.Enabled = !isMeasuring;
        }

        private void panel_notes_MouseDown(object sender, MouseEventArgs e)
        {
            int noteIndex = GetBarAtLocation(e.Location).GetYIndex();
            highlightedNoteIndex = noteIndex;
            playingThread = new Thread(new ParameterizedThreadStart(PlayNote));
            playingThread.Start(pianoNotes[noteIndex].GetFrequency());
            this.Refresh();
        }

        private void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            if (!holdingNote)
            {
                if (e.Control)
                {
                    switch (e.KeyCode)
                    {
                        case Keys.W:
                            this.Close();
                            break;
                        case Keys.Z:
                            if (button_undo.Enabled)
                                Undo();
                            break;
                        case Keys.N:
                            if (button_clear.Enabled)
                                Clear();
                            break;
                        case Keys.P:
                            if (button_play.Enabled)
                                Play();
                            break;
                        case Keys.G:
                            if (button_generate.Enabled)
                                OpenGenerationForm();
                            break;
                    }
                }
            }
        }

        private void button_measureTempoByTaps_Click(object sender, EventArgs e)
        {
            if (!measuringtempo)
            {
                measuringtempo = true;
                ChangeInterfaceToTempoMeasuringMode(true);
                tempoMeasureCurrentMillisecondsForRecordingInterval = 0;
                tempoMeasureCurrentMillisecondsForEndingMeasurement = 0;
                tempoMeasureStopWatch.Start();
                timer_tempoMeasure.Start();
            }
            else
            {
                tempoMeasureIntervals.Add(tempoMeasureStopWatch.ElapsedMilliseconds - tempoMeasureCurrentMillisecondsForRecordingInterval);
                tempoMeasureCurrentMillisecondsForRecordingInterval = tempoMeasureStopWatch.ElapsedMilliseconds;
                tempoMeasureCurrentMillisecondsForEndingMeasurement = tempoMeasureStopWatch.ElapsedMilliseconds;
            }
        }

        private void timer_tempoMeasure_Tick(object sender, EventArgs e)
        {
            if (measuringtempo)
            {
                if (tempoMeasureStopWatch.ElapsedMilliseconds - tempoMeasureCurrentMillisecondsForEndingMeasurement >= 2000)
                {
                    measuringtempo = false;
                    tempoMeasureStopWatch.Stop();
                    tempoMeasureStopWatch.Reset();
                    timer_tempoMeasure.Stop();
                    if (tempoMeasureIntervals.Count > 0)
                    {
                        int newTempo = Convert.ToInt32(1.0 / (tempoMeasureIntervals.Average() / 1000 / 60));
                        if (newTempo < numericUpDown_tempo.Minimum)
                            numericUpDown_tempo.Value = numericUpDown_tempo.Minimum;
                        else if (newTempo > numericUpDown_tempo.Maximum)
                            numericUpDown_tempo.Value = numericUpDown_tempo.Maximum;
                        else
                            numericUpDown_tempo.Value = newTempo;
                    }
                    tempoMeasureIntervals.Clear();
                    ChangeInterfaceToTempoMeasuringMode(false);
                }
            }
        }

        private void numericUpDown_snap_ValueChanged(object sender, EventArgs e)
        {
            snap = (int)numericUpDown_snap.Value;
            barsWidth = (float)panel_bars.Width / (snap * BEATS_PER_SEGMENT * SEGMENTS_PER_SECTION);
            this.Refresh();
        }

        private void numericUpDown_tempo_ValueChanged(object sender, EventArgs e)
        {
            tempo = (int)numericUpDown_tempo.Value;
        }
    }
}
