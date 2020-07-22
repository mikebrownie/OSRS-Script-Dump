#include <string>
#include <random>
#include <iostream>
#include <fstream>


void loadMsgList(std::string message_arr[], int size, std::string filename);

int main(int argc, char const *argv[])
{
  std::string arr[100];
  int size = 100;
  loadMsgList(arr, size, "message_list.txt");
  for(int i=0; i<size; i++){
    std::cout<<i<<", "<<arr[i]<<std::endl;
  }
}

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
