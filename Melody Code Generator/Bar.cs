using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace Melody_Code_Generator
{
    struct Bar
    {
        int xIndex;
        int yIndex;

        public Bar(int xIndex, int yIndex)
        {
            this.xIndex = xIndex;
            this.yIndex = yIndex;
        }

        public int GetXIndex()
        {
            return this.xIndex;
        }

        public int GetYIndex()
        {
            return this.yIndex;
        }
    }
}
