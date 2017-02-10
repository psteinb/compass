#ifndef _COMPASS_TAGS_H_
#define _COMPASS_TAGS_H_

#include <string>
#include <climits>

namespace compass {


  namespace feature {

    //SIMD instruction sets
    //128bit wide
    struct sse {};
    struct sse2 {};
    struct sse3 {};
    struct sse4 {};

    //256bit wide
    struct avx {};
    struct avx2 {};


  };


  namespace compiletime {

    struct gnu_tag  {};
    struct llvm_tag {};
    struct msvc_tag {};

    struct toolchain {

#ifdef __clang__
      typedef llvm_tag type;
#else
#ifdef __GNUC__
      typedef gnu_tag type;
#endif
#endif


#ifdef _MSC_BUILD
      typedef msvc_tag type;
#endif

    };

    //architectures
    struct x86_tag {};
    struct arm_tag {};


    struct platform {

#if __x86_64 || __x86_64__ || __i386 || i386 || __i386__ || _M_IX86 == 600 | _M_X64 == 100
      typedef x86_tag type;
#endif

      //32 or 64bit?
      const static int bitness = sizeof(void*)*CHAR_BIT;

    };


    //cpuid register locations
    static const int eax = 0;
    static const int ebx = 1;
    static const int ecx = 2;
    static const int edx = 3;


  };

  namespace ct = compiletime;

};
#endif /* _COMPASS_TAGS_H_ */
