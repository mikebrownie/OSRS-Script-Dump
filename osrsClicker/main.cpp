#include <windows.h>
#include <iostream>
void LeftClick ( )
{
  INPUT    Input={0};
  // left down
  Input.type      = INPUT_MOUSE;
  Input.mi.dwFlags  = MOUSEEVENTF_LEFTDOWN;
  ::SendInput(1,&Input,sizeof(INPUT));

  // left up
  ::ZeroMemory(&Input,sizeof(INPUT));
  Input.type      = INPUT_MOUSE;
  Input.mi.dwFlags  = MOUSEEVENTF_LEFTUP;
  ::SendInput(1,&Input,sizeof(INPUT));
}

int main()
{
  std::cout<<"Running... Press shift to auto-click";
  while(1){
    Sleep(15);
    if(GetKeyState(VK_SHIFT) < 0)
      LeftClick();
  }
std::cout<<"Done";
  return 0;
}
