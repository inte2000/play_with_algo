// jitutonglong.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

/*对头的个数进行枚举，然后检查脚的个数确定是否是符合条件的解*/
void Jitutonglong(int tou, int jiao)
{
    for (int ji = 0; ji < tou; ji++)
    {
        int tu = tou - ji;
        if ((ji * 2 + tu * 4) == jiao)
        {
            std::cout << "鸡：" << ji << "    "
                      << "兔：" << tu << std::endl;
        }
    }
}

int main()
{
    //Jitutonglong(50, 120);
    Jitutonglong(35, 94);
    return 0;
}

