#include <windows.h>
#include <winuser.h>
#include <conio.h>
#include <stdio.h>

int main()
{
  BlockInput(true);
  Sleep(5000);
  BlockInput(false);
}
