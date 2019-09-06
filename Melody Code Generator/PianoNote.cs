using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Melody_Code_Generator
{
    public struct PianoNote
    {
        static int notesCount = 0;

        private string name;
        private int frequency;
        private int noteIndex;

        public PianoNote(string name, int frequency)
        {
            this.name = name;
            this.frequency = frequency;
            this.noteIndex = notesCount;
            notesCount++;
        }

        public string GetName()
        {
            return this.name;
        }

        public int GetFrequency()
        {
            return this.frequency;
        }

        public int GetNoteIndex()
        {
            return this.noteIndex;
        }
    }
}
