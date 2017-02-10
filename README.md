# compass

A drop-in header-only C++ library to detect hardware capabilities at runtime and at compiletime.

## How to use

You have 2 options:

1. you can just copy the contents of `include` into your project and off you go

2. you use the cmake build infrastructure

    - on *NIX platforms
    ```
    $ cd repo
    $ mkdir build && cd build
    $ cmake -DCMAKE_INSTALL_PREFIX=/path/where/compass/needs/to/go ..
    $ make && ctest
    $ make install #depending on the contents of CMAKE_INSTALL_PREFIX, you may use sudo
    ```
    
## Compass API

Here is a minimal code example that tries to detect SSE4 at runtime:

```
#include <iostream>
#include "compass.hpp"

int main(int argc, char** argv){

    if(compass::runtime::has(compass::feature::sse4()))
        std::cout << "SSE4 found!!\n";
    else
        std::cout << "this is an old machine!!\n";
        
    return 0;

}

```


## Help needed 

This project is quite small, so here is your chance to boost open-source to the benefit of the entire C++ community.

- [ ] code review the model to extend compass to new compilers/platforms
- [ ] code review the model to extend compass to new features
- [ ] is thread-safety an issue of the current implementation
- [ ] contribute/check Intel compiler
- [ ] contribute for GPUs and nvcc
- [ ] contribute for OpenPower (started)
- [ ] contribute for ARM

A good place to start and to see what is needed, is llvm [`host.cpp`](http://llvm.org/docs/doxygen/html/Host_8cpp_source.html) file
