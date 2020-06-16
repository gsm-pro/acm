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
            int c = int.Parse(Console.ReadLine());
            int t = int.Parse(Console.ReadLine());
            double a = 0, b = 1e10, x = 0;
            for (int i = 0; i < 10000; i++)
            {
                x = (a + b) / 2;
                double time = c * x * Math.Log(x, 2.0);
                if (time > t) b = x; else a = x;
            }
            Console.Write(Convert.ToString(x, format));
        }
    }
}