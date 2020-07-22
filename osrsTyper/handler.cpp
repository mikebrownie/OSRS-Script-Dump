
#include <iostream>
#include <Windows.h>

using namespace std;

int main(){
  //runescape username
  string username;
  //exact name of window
  LPCTSTR windowName = "RuneLite - MikeVrown";
  HWND hwnd = FindWindowA(NULL, windowName);
  if(hwnd == NULL)
  {
    cout <<"Cannot find window."<< endl;
    Sleep(3000);
    exit(-1);
  }
  else
  {
    DWORD procID;
    GetWindowThreadProcessId(hwnd, &procID);
    HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);

    if(procID == NULL)
    {
      cout <<"Cannot find process ID."<< endl;
      Sleep(3000);
      exit(-1);
    }
    else
    {
      cout<<procID<<endl;
      SetForegroundWindow(hwnd);
      cout<<"fged"<<endl;
      Sleep(5000);
    }
}
return 0;
}
