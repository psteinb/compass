#ifndef DETAIL_DETECT_ARCHITECTURE_H
#define DETAIL_DETECT_ARCHITECTURE_H

//for reference see: https://sourceforge.net/p/predef/wiki/Architectures/

#define COMPASS_CT_ARCH_UNSUPPORTED

#if (defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64) || defined(_M_X64) || defined(_M_AMD64))
#define COMPASS_CT_ARCH_X86
#define COMPASS_CT_ARCH_64BITS
#undef  COMPASS_CT_ARCH_UNSUPPORTED
#endif

#if (defined(i386) || defined(__i386) || defined(__i386__) || defined(__i486__) || defined(__i586__) || defined(__i686__) || defined(__M_I86) || defined(_M_IX86))
#define COMPASS_CT_ARCH_X86
#undef  COMPASS_CT_ARCH_UNSUPPORTED
#endif

#if (defined(__powerpc64__) || defined(_ARCH_PPC64) || defined(__ppc64__))
#define COMPASS_CT_ARCH_POWER
#define COMPASS_CT_ARCH_64BITS
#undef  COMPASS_CT_ARCH_UNSUPPORTED
#endif

#if (defined(__powerpc)  || defined(__powerpc__) || defined(__POWERPC__) || defined(__PPC__) || defined(__ppc__))
#define COMPASS_CT_ARCH_POWER
#undef  COMPASS_CT_ARCH_UNSUPPORTED
#endif

#include "detail/definitions.hpp"

#include <climits> //for CHAR_BIT

namespace compass {

    namespace compiletime {

        //architectures

        struct x86_tag {};
        struct power_tag {};

        struct arch {

#ifdef COMPASS_CT_ARCH_X86
            typedef x86_tag type;
#endif

#ifdef COMPASS_CT_ARCH_POWER
            //NOTE  power has no direct support for cpuid like registers for unprivileged users
            //      any information needs to be retrieved through the OS
            typedef through_os_tag type;
#endif

#ifdef COMPASS_CT_ARCH_UNSUPPORTED
            typedef unsupported_tag type;
            static_assert(std::is_same<compass::ct::arch::type,compass::ct::unsupported_tag>::value,
                          "\n\ncompass is not aware of this architecture \nPlease create an issue under https://github.com/psteinb/compass\n\n");
#endif
            //32 or 64bit?
            const static int bitness = sizeof(void*)*CHAR_BIT;



        };

    }  // compiletime

}  // compass

#endif /* DETAIL_DETECT_ARCHITECTURE_H */
