#include <windows.h>
#include <random>
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
  std::string input;
  std::cout<<"Enter random number for seed\n";
  std::cin>>input;

  std::random_device rd; // obtain a random number from hardware
  std::mt19937 eng(rd()); // seed the generator
  std::uniform_int_distribution<> distr(30000, 60000);
  for (int i = 0; i < stoi(input); i++)
    distr(eng);
  std::cout<<"running, ctrl+c to stop\n";
  int count = 0;
  while(1){
    Sleep(distr(eng));
    LeftClick();
    count++;
    std::cout<<"clicks: " << count<<std::endl;
    if(GetKeyState(VK_SHIFT) < 0)
      break;
  }
std::cout<<"Done";
  return 0;
}
