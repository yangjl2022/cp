#include<cstdio>
#include<windows.h>
#include<ctime>

struct {
    const int T=10;	//延时(ms)
//-----------------------------------鼠标
    //移动鼠标到 (x,y)
    void setPosition(int x,int y) {
        SetCursorPos(x,y);
        Sleep(T);
    }
    //左击鼠标
    void click_lift() {
        mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
        Sleep(10);
        mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
        Sleep(T);
    }
    //右击鼠标
    void click_right() {
        mouse_event(MOUSEEVENTF_RIGHTDOWN,0,0,0,0);
        Sleep(10);
        mouse_event(MOUSEEVENTF_RIGHTUP,0,0,0,0);
        Sleep(T);
    }
    //鼠标移动到 (x,y) 并左击
    void moveAndClick(int x,int y) {
        this->setPosition(x,y);
        this->click_lift();
        Sleep(T);
    }
    //滑轮滚动,翻页
    void turnPage(int num=1) {
        mouse_event(MOUSEEVENTF_WHEEL,0,0,-120*num,0);
    }
//------------------------------------键盘
    //Ctrl系列
    void control(int x) {
        keybd_event(17,0,0,0);
        keybd_event(x,0,0,0);
        keybd_event(x,0,2,0);
        keybd_event(17,0,2,0);
        Sleep(T);
    }
    //全选
    void Ctrl_A() {
        this->control(65);
    }
    //复制
    void Ctrl_C() {
        this->control(67);
    }
    //粘贴
    void Ctrl_V() {
        this->control(86);
    }
    //单个小写字母
    void press(char ch) {
        ch+=-'a'+'A';
        keybd_event(ch,0,0,0);
        keybd_event(ch,0,2,0);
        Sleep(T);
    }
//-------------------------------------剪切板
    // 复制数据至剪切板
    bool setClipboard(const char *data) {
        bool res=false;			//操作结果
        int len = strlen(data) + 1;	//分配内存长度
        HGLOBAL clipBuffer;			//句柄
        LPTSTR p;				//指针
        if (OpenClipboard(NULL)) {	//打开剪切板
            if (EmptyClipboard()) {	//清空剪切板
                if (clipBuffer = GlobalAlloc(GMEM_MOVEABLE, len)) { //分配内存
                    if (p = (LPTSTR)GlobalLock(clipBuffer)) { //指针指向内存块
                        memcpy_s(p, len, data, len);   //通过指针复制数据
                        if (SetClipboardData(CF_TEXT, clipBuffer)) { //剪切板
                            // printf("成功复制【%s】到剪切板，字符串长度为%d。\n",data,len);
                            res=true;
                        }
                    }
                    GlobalUnlock(clipBuffer); 	//解锁句柄
                    GlobalFree(p);			//使指针无效
                }
            }
            CloseClipboard();
        }
        return res;
    }
    //读取剪切板
    char* getClipboard() {
        if (OpenClipboard(NULL)) {
            HANDLE h = GetClipboardData(CF_TEXT);//获取剪切板数据
            char* p =  (char*)GlobalLock(h);
            char* res=strdup(p);
            GlobalUnlock(h);
            GlobalFree(p);
            CloseClipboard();
            return res;
        }
        return NULL;
    }
//-----------------------------------------时间
    void waitingUtilOver(int hour,int min,int sec) {
        time_t nowT;
        struct tm *T;
        while (true) {
            time(&nowT);
            T=localtime(&nowT);
            printf("当前时间：%d:%d:%d \n",T->tm_hour,T->tm_min,T->tm_sec);
            if (T->tm_hour>hour||T->tm_hour==hour&&T->tm_min>min||T->tm_hour==hour&&T->tm_min==min&&T->tm_sec>=sec)
                break;
            Sleep(500);
        }
    }
} op;

int main() {
    while(1) {
        for(int k=0; k<2; ++k) {
            for(int i=1; i<=10; ++i) {
                Sleep(1000*5);
                op.turnPage((k&1?-1:1)*2);
            }
        }
    }
    return 0;
}
/*
编译运行指令：
cd D:/CPPCODE/tool/mouse
g++ .\simulate.cpp -o .\simulate
.\simulate

*/