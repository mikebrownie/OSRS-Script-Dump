#include <windows.h>
#include <winuser.h>
#include <vector>
#include <TCHAR.H>
#include <random>
#include <iostream>
#include <unistd.h>
#include <string>
#include <fstream>
#include <cstring>

#include <windows.h>

// bool KeyUsesShift(const int iKey)
// {
//     return wislower(iKey);
// }


// void SendKey(HWND hWnd, const int iVKcode)
// {
//     if (KeyUsesShift(iVKcode))
//         PostMessage(hWnd,    WM_CHAR,     static_cast<char>(iVKcode),                 0x00140001);
//     else
//     {
//         PostMessage(hWnd,    WM_KEYDOWN,  VkKeyScanW(static_cast<WCHAR>(iVKcode)),    0x00140001);
//         PostMessage(hWnd,    WM_KEYUP,    VkKeyScanW(static_cast<WCHAR>(iVKcode)),    0xC0140001);
//     }
// }
//
// void SendKey(HWND hWnd, const char iKey)
// {
//     if (KeyUsesShift(iKey))
//         PostMessage(hWnd,    WM_CHAR,     iKey,              0x00140001);
//     else
//     {
//         PostMessage(hWnd,    WM_KEYDOWN,  VkKeyScanW(iKey),  0x00140001);
//         PostMessage(hWnd,    WM_KEYUP,    VkKeyScanW(iKey),  0xC0140001);
//     }
// }

void SendKey(HWND hWnd, const wchar_t iKey)
{

    PostMessageA(hWnd,    0xC20D,  0, 0);

    PostMessageA(hWnd,    WM_KEYDOWN,  VkKeyScanW(iKey),  0x00140001);
    PostMessageA(hWnd,    0xC20D,  0, 0);

    PostMessageA(hWnd,    WM_KEYUP,    VkKeyScanW(iKey),  0xC0140001);
    PostMessageA(hWnd,    0xC20D,  0, 0);

    PostMessageA(hWnd,    WM_CHAR,  VkKeyScanW(iKey),  0x00140001);
}

void SendText(HWND hWnd, const std::wstring wsTextToBeSend)
{
    // SendMessage(hWnd, WM_ACTIVATEAPP, 1,  0x5650);//activate 00005650 child pid
    // SendMessage(hWnd, WM_NCACTIVATE, 1,  0);
    // SendMessage(hWnd, WM_ACTIVATE, 1, 0);
    // SendMessage(hWnd, WM_IME_SETCONTEXT, 1, 0xC000000F);
    // SendMessage(hWnd, WM_IME_NOTIFY, IMN_OPENSTATUSWINDOW, 0);
    // SendMessage(hWnd, WM_SETFOCUS, 0,0); //line 16

    // SendMessage(hWnd, WM_NCACTIVATE, 0, 0);
    // SendMessage(hWnd, WM_ACTIVATE, 0, 0);
    // SendMessage(hWnd, WM_ACTIVATEAPP, 1,  0x5650);//activate 00005650 child pid

    SendMessage(hWnd, 0x9807, 0,0);
    for (std::wstring::const_iterator wsCItr = wsTextToBeSend.begin(); wsCItr != wsTextToBeSend.end(); ++wsCItr)
    {
        Sleep(1000);
        SendKey(hWnd, *wsCItr);
    }
}

//@function getHandle: gets handle to runescae game
//Param: rs className and rs windowName
//Output: returns handle to rs game if found, or quits if not
HWND getHandle(LPCTSTR windowName, LPCSTR className){
  HWND hwnd_rs = FindWindowA(className, windowName);
  if(hwnd_rs == NULL)
  {
    std::cout <<"Cannot find window."<< std::endl;
    Sleep(3000);
    exit(-1);
  }else{
    return hwnd_rs;
  }
}

int main(){
  LPCTSTR windowName = "Old School Runescape";
  LPCTSTR className = "SunAwtFrame";
  HWND hwnd_rs = getHandle(windowName,className);
  const wchar_t msg[] = L"test";
  SendText(hwnd_rs, msg);
}
