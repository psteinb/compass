#ifndef COMPASS_DISPATCH_H_
#define COMPASS_DISPATCH_H_

#include "detail/ct/detect_os.hpp"
#include "detail/ct/detect_compiler.hpp"
#include "detail/ct/detect_arch.hpp"

#include "rt/unsupported_impl.hpp"

#ifdef COMPASS_CT_ARCH_X86
    #include "rt/x86_impl.hpp"
#endif

#ifdef COMPASS_CT_ARCH_POWER
    #include "rt/power_impl.hpp"
#endif

#endif /* COMPASS_DISPATCH_H_ */
