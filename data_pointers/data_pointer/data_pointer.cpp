#include <iostream>
#include <chrono>


// Class to hold data
// Note: This could easily be accomplished with a Vector<double>
class Data1D {
public:
  Data1D(int s) :elem{new double[s]}, sz{s}
  {
    for (int i=0; i!=s; ++i)
      {
	elem[i] = i;
      }
  }
  ~Data1D() { delete[] elem; }
  double& operator[](int i);
  int size() const { return this->sz; };

private:
  double *elem;  // elem pointer to array of sz doubles
  int sz;
};

//int Data1D::size(void) const 
double& Data1D::operator[](int i) {
  if (i < this->sz) {
    return *(this->elem+i);
  }
  else {
    return *this->elem;
  }
}

int main(int argc, char * argv[])
{
  auto t1 = std::chrono::high_resolution_clock::now();
  auto d1 = Data1D(100);  // 100 data points of type double
  // function with data pointers
  std::cout << "data size: " << d1.size() << '\n';
  d1[50] = 1111.0;
  std::cout << "data point: " << d1[200] << '\n';
  
  
  auto t2 = std::chrono::high_resolution_clock::now();

  // get number of milliseconds as integer
  auto ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

  // gett number of milliseconds as double
  std::chrono::duration<double, std::milli> ms_double = t2 - t1;
  std::cout << ms_int.count()  << "ms\n";
  std::cout << ms_double.count()  << "ms\n";
  return 0;
  
}


