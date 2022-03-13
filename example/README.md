c++ -O3 -Wall -shared -std=c++11 -fPIC -I/usr/include/python3.8 -I/home/jerahmie/devenv/lib/python3.8/site-packages/pybind11/include -I ../small_data/test -I ../scientific_cpp/chapter5/cuberoot danger.cpp -L ../scientific_cpp/chapter5/cuberoot -lcuberoot  -o danger.cpython-38-x86_64-linux-gnu.so

LD_LIBRARY_PATH=../scientific_cpp/chapter5/cuberoot python
