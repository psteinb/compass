#ifndef COMPASS_DISPATCH_H_
#define COMPASS_DISPATCH_H_

#include "detail/ct/detect_os.hpp"
#include "detail/ct/detect_compiler.hpp"
#include "detail/ct/detect_arch.hpp"

#include "detail/definitions.hpp"

#ifdef COMPASS_CT_ARCH_X86
#include "rt/x86_impl.hpp"
#include "rt/x86_sizes.hpp"
#endif


#endif /* COMPASS_DISPATCH_H_ */
