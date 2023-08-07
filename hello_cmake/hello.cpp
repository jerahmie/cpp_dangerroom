#include <iostream>
#include <netcdf>

int main(void)
{
  std::cout << "Hello World!\n";
  int fh = 0;
  int retval = 0;
  retval = nc_open("fake_file.nc");
  std::cout << "retval: " << retval << '\n';
}
