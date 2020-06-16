using System;
using System.Globalization;

namespace Solution
{
    class Program
    {
        static void Main(string[] args)
        {
            NumberFormatInfo format = new NumberFormatInfo();
            format.NumberDecimalSeparator = ".";
            string[] e = Console.ReadLine().Split(' ');
            double s = Double.Parse(e[0]);
            double m = Double.Parse(e[1]);
            double p = Double.Parse(e[2]) / 100.0;
            double k = (p == 0.0) ? 1 / m : p * Math.Pow(1 + p, m) / (Math.Pow(1 + p, m) - 1);
            Console.Write(Convert.ToString(k * s, format));
        }
    }
}