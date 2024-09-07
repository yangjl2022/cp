#include<iostream>
#include<windows.h>

int main() {
    POINT mouse;
    puts("获得鼠标位置,按空格暂停");
    system("pause");
    while(1) {          
        if(GetKeyState(32)<0) {
            system("pause");
        }

        GetCursorPos(&mouse);
        printf("鼠标当前位置：( %d,%d )\n",mouse.x,mouse.y);
        Sleep(100);  // 降低监控精度,不然会一直输出一下暂停一下
    }
    return 0;
} 
/*
g++ -finput-charset=UTF-8 -fexec-charset=GBK .\simulate_getMousePosition.cpp -o .\simulate_getMousePosition
.\simulate_getMousePosition


*/