/*
 * Reverse a string in C++
 */

#include <string>
#include <iostream>
#include <algorithm>


int main(int argc, char* argv[]) 
{
  const std::string mystring = "This is a C++ string.";
  std::string revstring = mystring;
  std::reverse(revstring.begin(), revstring.end()); 
  std::cout << "\"" << mystring << "\" " << " reversed is: " << revstring << '\n';
}
