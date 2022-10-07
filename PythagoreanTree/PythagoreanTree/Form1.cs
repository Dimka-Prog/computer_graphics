using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PythagoreanTree
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            
        }

        private void buttonDraw_Click(object sender, EventArgs e)
        {
            Draw(280, 460, 100, 0);
        }

        private void buttonErase_Click(object sender, EventArgs e)
        {
            pictureBox1.Invalidate();
        }

        public void Rect(double x1, double y1, double treeHeight, double angle)
        {
            Graphics graphics = pictureBox1.CreateGraphics();
            Random random = new Random();
            graphics.SmoothingMode = SmoothingMode.HighQuality;
            graphics.CompositingQuality = CompositingQuality.HighQuality;
            Brush brush = new SolidBrush(Color.FromArgb(random.Next(0, 251), random.Next(0, 251), random.Next(0, 251)));
            Pen pen = new Pen(brush, 2);

            double x2 = Math.Round(x1 + (treeHeight * Math.Cos(angle)));
            double y2 = Math.Round(y1 - (treeHeight * Math.Sin(angle)));
            double x3 = Math.Round(x1 + (treeHeight * Math.Sqrt(2) * Math.Cos(angle + Math.PI / 4)));
            double y3 = Math.Round(y1 - (treeHeight * Math.Sqrt(2) * Math.Sin(angle + Math.PI / 4)));

            double x4 = Math.Round(x1 + (treeHeight * Math.Cos(angle + Math.PI / 2)));
            double y4 = Math.Round(y1 - (treeHeight * Math.Sin(angle + Math.PI / 2)));

            graphics.DrawLine(pen, (int)x1, (int)y1, (int)x2, (int)y2);
            graphics.DrawLine(pen, (int)x2, (int)y2, (int)x3, (int)y3);
            graphics.DrawLine(pen, (int)x3, (int)y3, (int)x4, (int)y4);
            graphics.DrawLine(pen, (int)x4, (int)y4, (int)x1, (int)y1);

        }

        public void Draw(double x, double y, double treeHeight, double angle)
        {
            if (treeHeight > 8)
            {
                Rect(x, y, treeHeight, angle);

                Draw(
                    x - treeHeight * Math.Sin(angle),
                    y - treeHeight * Math.Cos(angle),
                    treeHeight / Math.Sqrt(2),
                    angle + Math.PI / 4
                );

                Draw(
                    x - treeHeight * Math.Sin(angle) + treeHeight / Math.Sqrt(2) * Math.Cos(angle + Math.PI / 4),
                    y - treeHeight * Math.Cos(angle) - treeHeight / Math.Sqrt(2) * Math.Sin(angle + Math.PI / 4),
                    treeHeight / Math.Sqrt(2),
                    angle - Math.PI / 4
                );

            }
        }
    }
}
