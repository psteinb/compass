#ifndef DETAIL_DETECT_OS_H
#define DETAIL_DETECT_OS_H

//for reference see: https://sourceforge.net/p/predef/wiki/OperatingSystems/
#define COMPASS_CT_OS_UNSUPPORTED

#if (defined(__linux__) || defined(__gnu_linux__))
#define COMPASS_CT_OS_LINUX
#undef  COMPASS_CT_OS_UNSUPPORTED
#endif

#if (defined(__APPLE__) && defined(__MACH__))
#define COMPASS_CT_OS_MACOS
#undef  COMPASS_CT_OS_UNSUPPORTED
#endif

#if (defined(_WIN16) || defined(_WIN32) || defined(_WIN64) || defined(__WIN32__))
#define COMPASS_CT_OS_WINDOWS
#undef  COMPASS_CT_OS_UNSUPPORTED
#endif

#include "detail/definitions.hpp"

namespace compass {

    namespace compiletime {

        struct linux_tag  {};
        struct macos_tag {};
        struct windows_tag {};

        struct platform {

#ifdef COMPASS_CT_OS_LINUX
            typedef linux_tag type;
#endif

#ifdef COMPASS_CT_OS_MACOS
            typedef macos_tag type;
#endif

#ifdef COMPASS_CT_OS_WINDOWS
            typedef windows_tag type;
#endif

#ifdef COMPASS_CT_OS_UNSUPPORTED
            typedef unsupported_tag type;
#endif

            static_assert(std::is_same<type,unsupported_tag>::value, "\n\ncompass is not aware of this operating system \nPlease create an issue under https://github.com/psteinb/compass\n\n");

        };

    }  // compiletime

}  // compass
#endif /* DETAIL_DETECT_OS_H */
