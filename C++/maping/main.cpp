#include <map>
#include <string>
#include <iostream>

#include "file.x"
#include "file.h"

using namespace std;
std::map<int, std::string> file_mapping;
int16_t file_name_string_size = 0;

/*
std::string file_name(int ID)
{
  if(file_mapping.count(ID) > 0)
    return file_mapping(ID);
  else
   return "unknown";
}
*/

int main()
{
  file_mapping.insert(std::make_pair(1,"/home/william/Documents/programming/ANSI_C/C++/maping/file.x"));
  file_mapping.insert(std::make_pair(2,"/home/william/Documents/programming/ANSI_C/C++/maping/file.h"));

  file_x newfile;

  newfile.nvalue = 90;

 cout<<"NEW VALUE from file X "<< newfile.nvalue << endl;
 cout<<"New value from file h "<< VALUE_FILEH << endl;

  return 0;
}
