/*
 *
 *
 */

#include <iostream>
#include <unistd.h>


int main(int argc, char* argv[])
{
  char curr_path[100];
  getcwd(curr_path, sizeof(curr_path));
  std::string mypwd(curr_path);
  std::cout << "Test getcwd: " << mypwd << '\n';
}
