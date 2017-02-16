#ifndef COMPASS_DISPATCH_H_
#define COMPASS_DISPATCH_H_

#include "detail/ct/detect_os.hpp"
#include "detail/ct/detect_compiler.hpp"
#include "detail/ct/detect_arch.hpp"

#ifdef COMPASS_CT_ARCH_X86
    #include "rt/x86_impl.hpp"
#endif

#ifdef COMPASS_CT_ARCH_POWER

#ifdef COMPASS_CT_OS_LINUX
    #include "rt/through_os_impl.hpp"
#enif

#endif

#endif /* COMPASS_DISPATCH_H_ */
