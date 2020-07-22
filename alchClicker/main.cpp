#include <windows.h>
#include <random>
#include <iostream>
void LeftClick ( );
inline void wait();
TCHAR pressanykey( const TCHAR* prompt = NULL );




int main()
{
  std::random_device rd; // obtain a random number from hardware
  std::mt19937 eng(rd()); // seed the generator

  std::uniform_int_distribution<> distr(3000, 4000); //ms beteen alchs
  std::uniform_int_distribution<> distr2(150, 250); //ms betweem clicks
  std::string input;
  int seed;
  std::cout<<"Enter random number for seed:\n";
  getline(std::cin, input);
  seed=stoi(input)*7+11*(stoi(input)%79);
  for (int i =0; i<seed; i++){
    distr(eng);
    distr2(eng);
  }
  std::cout<<"Enter number of items:\n";
  getline(std::cin, input);
  std::cout<<"Starting in 3 seconds...\n";
  int count = 0;
  Sleep(3000);
  while(count<stoi(input)){
    Sleep(distr(eng));
    LeftClick();
    Sleep(distr2(eng));
    LeftClick();
    count++;
    std::cout<<"clicks: " << count<<std::endl;
    if(GetKeyState(VK_SHIFT) < 0)
      break;
  }
std::cout<<"Done";
  return 0;
}


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


void wait(){
  pressanykey();
}



TCHAR pressanykey( const TCHAR* prompt )
  {
  TCHAR  ch;
  DWORD  mode;
  DWORD  count;
  HANDLE hstdin = GetStdHandle( STD_INPUT_HANDLE );

  // Prompt the user
  if (prompt == NULL) prompt = TEXT( "Press any key to continue..." );
  WriteConsole(
    GetStdHandle( STD_OUTPUT_HANDLE ),
    prompt,
    lstrlen( prompt ),
    &count,
    NULL
    );

  // Switch to raw mode
  GetConsoleMode( hstdin, &mode );
  SetConsoleMode( hstdin, 0 );

  // Wait for the user's response
  WaitForSingleObject( hstdin, INFINITE );

  // Read the (single) key pressed
  ReadConsole( hstdin, &ch, 1, &count, NULL );

  // Restore the console to its previous state
  SetConsoleMode( hstdin, mode );

  // Return the key code
  return ch;
  }
