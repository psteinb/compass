#ifndef COMPASS_DETAIL_H_
#define COMPASS_DETAIL_H_


#include "tags.hpp"

//compiletime code
#if defined(__linux__)

    #if (defined(__powerpc64__) || defined(__powerpc__))
        #include "ct/power_impl.hpp"
    #else
        #if defined(__clang__)
            #include "ct/llvm_impl.hpp"
        #else if defined(__GNUC__)
                #include "ct/gnu_impl.hpp"
            #endif
        #endif
    #endif

#else //not linux

    #ifdef __APPLE__
        #include "ct/llvm_impl.hpp"
    #else //not __APPLE__
        #ifdef _MSC_BUILD
            #include "ct/msvc_impl.hpp"
        #endif
    #endif

#endif

#include "ct/preprocessor_impl.hpp"

//runtime code
#if defined(__x86_64) || defined(__x86_64__) || defined(__x86)
    #include "rt/x86_impl.hpp"
#endif

#if (defined(__powerpc64__) || defined(__powerpc__))
    #include "rt/power_impl.hpp"
#else

#endif /* COMPASS_DETAIL_H_ */
