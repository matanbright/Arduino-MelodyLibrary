using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Melody_Code_Generator
{
    public class Note
    {
        private PianoNote pianoNote;
        private int startBar;
        private int noteBars;

        public Note(PianoNote pianoNote, int startBar, int noteBars)
        {
            this.pianoNote = pianoNote;
            this.startBar = startBar;
            this.noteBars = noteBars;
        }

        public PianoNote GetPianoNote()
        {
            return this.pianoNote;
        }

        public int GetStartBar()
        {
            return this.startBar;
        }

        public int GetNoteBars()
        {
            return this.noteBars;
        }

        public void SetStartBar(int startBar)
        {
            this.startBar = startBar;
        }

        public void SetNoteBars(int noteBars)
        {
            this.noteBars = noteBars;
        }
    }
}
