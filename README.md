[![Build Status](https://travis-ci.org/psteinb/compass.svg?branch=master)](https://travis-ci.org/psteinb/compass)
[![Build status](https://ci.appveyor.com/api/projects/status/dvgk88ynuuvx1ldi/branch/master?svg=true)](https://ci.appveyor.com/project/psteinb/compass/branch/master)

# compass 

A drop-in header-only C++ library to detect hardware capabilities at runtime and at compiletime.

## How to use it?

You have 2 options:

1. you can just copy the contents of `include` into your project and off you go

2. you use the cmake build infrastructure to put compass in a desired folder

    - on *NIX platforms and macOS/OSX
    ```
    $ cd repo
    $ mkdir build && cd build
    $ cmake -DCMAKE_INSTALL_PREFIX=/path/where/compass/needs/to/go ..
    $ make && ctest
    $ make install #depending on the contents of CMAKE_INSTALL_PREFIX, you may use sudo
    ```

    - on Windows platforms (assuming that `cmake` and `boost\lib` are in your `PATH`)
	```
	> cd repo
	> mkdir build
	> cd build
	> cmake.exe -G "Visual Studio 14 2015 Win64" -DBOOST_ROOT=C:\path\to\boost\1_59_0 ..
	> cmake.exe --build . --target ALL_BUILD --config Release
	> ctest.exe -C Release
	```

(3.) tests can only be run if you have access to the test machines and it requires boost to be installed (if boost is not detected, the tests are skipped and a warning is issued)

## Compass API

Here is a minimal code example that tries to detect SSE4 at runtime:

```
#include <iostream>
#include "compass.hpp"

using namespace compass;

int main(int argc, char** argv){

    if(runtime::has(feature::sse4()))
        std::cout << "SSE4 found!!\n";
    else
        std::cout << "This is an old machine. I hope I don't break anything.\n";
        
    return 0;

}

```

if you want to learn more supported features, check this [test file](tests/test_build_machine.cpp).

## Help needed 

This project is quite small, so here is your chance to boost open-source to the benefit of the entire C++ community.

- [ ] code review the model to extend compass for new compilers/platforms/OSes
- [ ] code review the model to extend compass for new features
- [ ] contribute adding detection of the cache hierarchy and associated cache sizes on x86 
- [ ] is thread-safety an issue of the current implementation ?
- [ ] contribute for adding Intel compiler on x86
- [ ] contribute for GPUs (nvcc)
- [ ] extend support for OpenPower (gcc)
- [ ] contribute for ARM (gcc/clang) if you have according hardware available

A good place to start and to see what is needed, is llvm [`Host.cpp`](http://llvm.org/docs/doxygen/html/Host_8cpp_source.html) file

## License

This project is licensed under the BSD 3-clause open source license. See [LICENSE](LICENSE) for details.
