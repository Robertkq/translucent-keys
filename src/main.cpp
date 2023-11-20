#include "main.h"
#include "kqlog.h"
#include "kqnet.h"

kq::logger Logger("logs.txt", "output/");

int main()
{
    for (int i = 0; i < 10; ++i)
    {
        Logger.out(KQINFO, { "{%C} {0:5} {%g}START", i + 10 });
        Logger.out(KQDEBUG, { "{%g} {0:5} {%R}CONTINUE", i + 10 });
        Logger.out(KQCRITICAL, { "{%R} {0:5} {%E}END", i + 10 });
    }

    return 0;
}