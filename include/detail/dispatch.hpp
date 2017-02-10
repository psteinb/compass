#ifndef _COMPASS_DETAIL_H_
#define _COMPASS_DETAIL_H_


#include "tags.hpp"

//compiletime code

#ifdef __clang__
#include "ct/llvm_impl.hpp"
#else
#ifdef __GNUC__
#include "ct/gnu_impl.hpp"
#endif
#endif

#ifdef _MSC_BUILD
#include "ct/msvc_impl.hpp"
#endif

#include "ct/preprocessor_impl.hpp"

//runtime code

#include "rt/x86_impl.hpp"


#endif /* _COMPASS_DETAIL_H_ */
