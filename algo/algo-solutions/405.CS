using System;

namespace Solution
{
    class Program
    {
        static void Main(string[] args)
        {
            string s = Console.ReadLine();
            int n = int.Parse(s);
            int prevTime = Int32.MaxValue;
            int dayCount = 0, w = 0;
            while (n-- > 0)
            {
                s = Console.ReadLine();
                string h = "" + s[1] + s[2], m = "" + s[4] + s[5], j = "" + s[7];
                if (h == "12") h = "00";
                int curTime = int.Parse(h) * 60 + int.Parse(m);
                if (j == "p") curTime += 720;
                if (curTime == prevTime) ++w;
                if (curTime < prevTime || w == 11)
                {
                    ++dayCount;
                    w = 1;
                }
                if (curTime > prevTime) w = 1;
                prevTime = curTime;
            }
            Console.Write(dayCount);
        }
    }
}