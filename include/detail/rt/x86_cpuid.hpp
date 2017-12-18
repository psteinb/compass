#ifndef COMPASS_RT_X86_CPUID_H

#include "detail/ct/detect_arch.hpp"

#ifdef COMPASS_CT_ARCH_X86
#define COMPASS_RT_X86_CPUID_H

#include "detail/rt/x86/llvm_cpuid.hpp"
#include "detail/rt/x86/gnu_cpuid.hpp"
#include "detail/rt/x86/msvc_cpuid.hpp"
#include "detail/rt/x86/intel_cpuid.hpp"

#endif /* COMPASS_CT_ARCH_X86 */

#endif /* X86_CPUID_H */
