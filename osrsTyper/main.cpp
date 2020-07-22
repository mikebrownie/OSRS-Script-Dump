#include <windows.h>
#include <winuser.h>
#include <vector>
#include <TCHAR.H>
#include <random>
#include <iostream>
#include <unistd.h>
#include <string>
#include <fstream>

//@function typeChar: types individual characters
//Param: char to be emulated on keyboard
//Output: true if sent, else false
BOOL typeChar(char lpctszText );

//@function pressEnter: types ENTER character
//Param: none
//Output: true if sent, else false
BOOL pressEnter();

//@function sendMsg: types message key at a time with random delays, also
//presses enter at end of string
//Param: msg to be sent
//Output: none
void sendMsg(std::string msg);

//@function sendMsgRS: sendMsgRs grab rs handle
//Param: msg to be sent
//Output: none
void sendMsgRS(std::string msg);

//@function loadMsgList: loads msgs from filename, stores in msg_array
//Param: message_array to be loaded, filename to read from
//Output: none
void loadMsgList(std::string message_arr[], int size, std::string filename);

//@function loopMsgList: sends numMessages random messages, 3-5mins between ea
//Param: message_arr to be read, size of message_arr, numMessages to send
//Output: writes to log file, messages sent
void loopMsgList(std::string message_arr[], int message_arr_size, int numMessages);


int main(int argc, char const *argv[]) {
  int numMessages = 100; //numer of messages to be sent
  std::string message_arr[100];   //defining possible outputs
  int message_arr_size=100;
  loadMsgList(message_arr, message_arr_size, "message_list.txt");

  //starting typer
  std::cout<<"First message in 5 seconds"<<std::endl;
  sleep(5); //wait until rs is pulled up
  sendMsgRS("okaaa"); //send text
  loopMsgList(message_arr, message_arr_size, numMessages);
return 0;
}


//@function loopMsgList: sends numMessages random messages, 3-5mins between ea
//Param: message_arr to be read, size of message_arr, numMessages to send
//Output: writes to log file, messages sent
void loopMsgList(std::string message_arr[], int message_arr_size, int numMessages){
  std::random_device rd, rd2; // obtain a random number from hardware
  std::mt19937 eng(rd()); // seed the generators
  std::mt19937 eng2(rd2());

   //150, 223 -> 3-5mins between messages
   //900,1080 -> 15-18 mins
  std::uniform_int_distribution<> distr(900,1080);
  std::uniform_int_distribution<> distr2(0, message_arr_size); // msg indx
  std::ofstream log;
  log.open("log.txt");
  if(log.is_open()){
    std::cout<<"Opened log file...\n";
  }else{
    std::cout<<"Failed to open log file. \n";
  }
  for(int i=0;i<100;i++){
    distr2(eng2);
    distr(eng);
  }
  std::cout<<"Starting autotyper"<<std::endl;
  log << "\n\n\n\n\n\nStarting auto-type\n";
  log << "==================================================================";

  for(int i = 0; i<numMessages; i++){
    int wait_time=distr(eng);
    std::cout<<"Minutes to next message: "<<float(wait_time)/(60)<<std::endl;
    log << "Wating for "<<float(wait_time)/(60)<<" minutes\n";
    sleep(wait_time); //wait for random time
    std::cout<<"10 second warning"<<std::endl;
    int msg_index=distr2(eng2);
    std::cout<<"Message index: "<<msg_index<<std::endl;
    std::cout<<message_arr[msg_index]<<std::endl;
    log << "Sending message #"<<msg_index<<", " + message_arr[msg_index] + "\n";
    sendMsgRS(message_arr[msg_index]);
  }
}


//@function typeChar: types individual characters
//Param: char to be emulated on keyboard
//Output: true if sent, else false
BOOL typeChar(char lpctszText )
{
  std::vector<INPUT> EventQueue;
  TCHAR Buff[120 * sizeof(TCHAR)] = {0};

  GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_ILANGUAGE, Buff, sizeof(Buff));

  HKL hKeyboardLayout = ::LoadKeyboardLayout( Buff, KLF_ACTIVATE );
	INPUT Event = { 0 };
	const SHORT Vk = VkKeyScanEx(lpctszText, hKeyboardLayout);
	const UINT VKey = ::MapVirtualKey( LOBYTE( Vk ), 0 );

	if( HIBYTE( Vk ) == 1 ) // Check if shift key needs to be pressed for this key
		{
		// Press shift key
		::ZeroMemory( &Event, sizeof( Event ));
		Event.type = INPUT_KEYBOARD;
		Event.ki.dwFlags = KEYEVENTF_SCANCODE;
		Event.ki.wScan = ::MapVirtualKey( VK_LSHIFT, 0 );
		EventQueue.push_back( Event );
		}

	// Keydown
	::ZeroMemory( &Event, sizeof( Event ));
	Event.type = INPUT_KEYBOARD;
	Event.ki.dwFlags = KEYEVENTF_SCANCODE;
	Event.ki.wScan = VKey;
	EventQueue.push_back( Event );

	// Keyup
	::ZeroMemory( &Event, sizeof( Event ));
	Event.type = INPUT_KEYBOARD;
	Event.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
	Event.ki.wScan = VKey;
	EventQueue.push_back( Event );

	if( HIBYTE( Vk ) == 1 )// Release if previously pressed
		{
		// Release shift key
		::ZeroMemory( &Event, sizeof( Event ));
		Event.type = INPUT_KEYBOARD;
		Event.ki.dwFlags = KEYEVENTF_SCANCODE| KEYEVENTF_KEYUP;
		Event.ki.wScan = ::MapVirtualKey( VK_LSHIFT, 0 );
		EventQueue.push_back( Event );
		}
	if( hKeyboardLayout )
		{
		UnloadKeyboardLayout( hKeyboardLayout );
    }
  return static_cast<BOOL>(::SendInput( static_cast<UINT>(EventQueue.size()), &EventQueue[0], sizeof( INPUT )));
}

//@function pressEnter: types ENTER character
//Param: none
//Output: true if sent, else false
BOOL pressEnter()
{
    std::vector<INPUT> EventQueue;
    TCHAR Buff[120 * sizeof(TCHAR)] = {0};
    GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_ILANGUAGE, Buff, sizeof(Buff));
    HKL hKeyboardLayout = ::LoadKeyboardLayout( Buff, KLF_ACTIVATE );
    INPUT Event = { 0 };

    //Enterkey down
    ::ZeroMemory( &Event, sizeof( Event ));
    Event.type = INPUT_KEYBOARD;
    Event.ki.dwFlags = KEYEVENTF_SCANCODE;
    Event.ki.wScan = ::MapVirtualKey( VK_RETURN, 0 );
    EventQueue.push_back( Event );

    //Release Enterkey
    ::ZeroMemory( &Event, sizeof( Event ));
    Event.type = INPUT_KEYBOARD;
    Event.ki.dwFlags = KEYEVENTF_SCANCODE| KEYEVENTF_KEYUP;
    Event.ki.wScan = ::MapVirtualKey( VK_RETURN, 0 );
    EventQueue.push_back( Event );

    if( hKeyboardLayout )
    {
      UnloadKeyboardLayout( hKeyboardLayout );
    }
    return static_cast<BOOL>(::SendInput( static_cast<UINT>(EventQueue.size()), &EventQueue[0], sizeof( INPUT )));
}


//@function sendMsg: types message key at a time with random delays, also
//presses enter at end of string
//Param: msg to be sent
//Output: none
void sendMsg(std::string msg){
  std::random_device rd; // obtain a random number from hardware
  std::mt19937 eng(rd()); // seed the generator
  std::uniform_int_distribution<> distr(81, 218); //avg human keystroke: 167 ms
  for (int i = 0; i < msg.length(); i++){
    typeChar(msg[i]);
    Sleep(distr(eng)); //pause between keystrokes
  }
  pressEnter();
  return;
}


//@function sendMsgRS: sendMsgRs grab rs handle
//Param: msg to be sent
//Output: none
void sendMsgRS(std::string msg){
  //runescape username
  std::string username;
  //exact name of window
  LPCTSTR windowName = "RuneLite - MikeVrown";
  HWND hwnd = FindWindowA(NULL, windowName);
  if(hwnd == NULL)
  {
    std::cout <<"Cannot find window."<< std::endl;
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
      std::cout <<"Cannot find process ID."<< std::endl;
      Sleep(3000);
      exit(-1);
    }
    else
    {
      std::cout<<procID<<std::endl;
      std::cout<<EnableWindow(hwnd, 1)<<std::endl;
      sendMsg(msg);
      std::cout<<"sent: " + msg<<std::endl;

    }
  }//end else
}

//@function loadMsgList: loads msgs from filename, stores in msg_array
//Param: message_array to be loaded, filename to read from
//Output: none
void loadMsgList(std::string message_arr[], int size, std::string filename)
{
  std::random_device rd; // obtain a random number from hardware
  std::mt19937 eng(rd()); // seed the generators
  //fill array with as many phrases as possible
  std::ifstream infile(filename);

  std::string line;
  int index=0;
  while (std::getline(infile, line))
  {
      message_arr[index++] = line;
  }
  int messages=index;

  //fill rest of arr with random chars
  for (int i=messages; i<size; i++){
    std::uniform_int_distribution<> distr(32, 126); //generate random character
    message_arr[i]=(char)(distr(eng));
  }
}
