/*
 * Try using assert for debug and disable for release.
 *
 */

#include <iostream>
#define NDEBUG
#include <cassert>

int fn_with_assert(void) {
  assert(5 == 2+2);
  return 0;
}

int main(int argc, char* argv[]) 
{
  std::cout << "Hello World!\n";
  int result;
  result = fn_with_assert();
  std::cout << "Done.  Return status: " << result << '\n';
}
