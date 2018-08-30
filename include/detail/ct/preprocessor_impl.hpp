#ifndef COMPASS_CT_PREPROCESSOR_IMPL_H_
#define COMPASS_CT_PREPROCESSOR_IMPL_H_



#ifndef WIN32

#if defined(__SSE2__) || defined(__SSE2_MATH__) //  && __SSE2__ != 0 && __SSE2_MATH__ != 0
    #define COMPASS_CT_HAS_SSE2 1
   #endif

#if defined(__SSE3__) && defined(__SSSE3__)
    #define COMPASS_CT_HAS_SSE3 1
   #endif

#if defined(__SSE4_2__) && defined(__SSE4_1__)
    #define COMPASS_CT_HAS_SSE4 1
   #endif

#else
//TODO: try to warn users on Windows that we are enabling SSE3 + SSE4 upon assumption here
    #ifdef _M_IX86_FP
		#if _M_IX86_FP >= 2
			#define COMPASS_CT_HAS_SSE2 1
			#define COMPASS_CT_HAS_SSE3 1
			#define COMPASS_CT_HAS_SSE4 1
		#endif
	#else
		#if defined(__AVX__) || defined(__AVX2__)
			#define COMPASS_CT_HAS_SSE2 1
			#define COMPASS_CT_HAS_SSE3 1
			#define COMPASS_CT_HAS_SSE4 1
		#endif
    #endif
#endif


#include "detail/tags.hpp"

namespace compass {

  namespace compiletime {

    template<typename feature_t>
    struct has{
      static const bool enabled = false;
    };

    template<>
    struct has<x86::feature::sse2>{
      static const bool enabled=
#ifdef COMPASS_CT_HAS_SSE2
     true;
#else
     false;
#endif

    };

    template<>
    struct has<x86::feature::sse3>{
      static const bool enabled=
#ifdef COMPASS_CT_HAS_SSE3
     true;
#else
     false;
#endif

    };

    template<>
    struct has<x86::feature::sse4>{
      static const bool enabled=
#ifdef COMPASS_CT_HAS_SSE4
     true;
#else
     false;
#endif

    };

  };
};

#endif /* COMPASS_CT_PREPROCESSOR_IMPL_H_ */
