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
  std::random_device rd; // obtain a random number from hardware
  std::mt19937 eng(rd()); // seed the generator
  std::uniform_int_distribution<> distr(15000, 45000); //hp regens each minute
  std::uniform_int_distribution<> distr2(1000, 2000); //To flick off
  int count = 0;

  //Seeding
  for(int i = 0; i<0; i++){
    distr2(eng);
    distr(eng);
  }

  std::cout<<"starting"<<std::endl;
  int waitTime;
  int clickSpeed;
  while(1){
    waitTime = distr(eng);
    clickSpeed = distr2(eng);
    std::cout<<"waiting "<<waitTime/1000<<" seconds.\n";
    Sleep(waitTime);
    LeftClick();
    std::cout<<"clicked, flicking off in "<<clickSpeed/1000<<" seconds.\n";
    Sleep(clickSpeed);
    LeftClick();
    count++;
    std::cout<<"clicks: " << count<<std::endl;
  }
std::cout<<"Done";
  return 0;
}
