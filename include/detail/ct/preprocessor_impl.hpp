#ifndef COMPASS_CT_PREPROCESSOR_IMPL_H_
#define COMPASS_CT_PREPROCESSOR_IMPL_H_

#ifndef WIN32
    #if defined __SSE2__ && defined __SSE2_MATH__
        #define COMPASS_HAS_SSE2
    #endif
#else
    #if _M_IX86_FP >= 2
        #define COMPASS_HAS_SSE2
    #endif
#endif

#ifndef WIN32
    #if defined __SSE3__ && defined __SSSE3__
        #define COMPASS_HAS_SSE3
    #endif

    #if defined __SSE4_2__ && defined __SSE4_1__
        #define COMPASS_HAS_SSE4
    #endif
#else
//TODO: try to warn users on Windows that we are enabling SSE3 + SSE4 upon assumption here
    #define COMPASS_HAS_SSE3
    #define COMPASS_HAS_SSE4
#endif

#include "../tags.hpp"


namespace compass {

  namespace compiletime {

    template<typename feature_t>
    struct has{
      static const bool enabled = false;
    };

    template<>
    struct has<feature::sse2>{
      static const bool enabled=
#ifdef COMPASS_CT_HAS_SSE2
     true;
#else
     false;
#endif

    };

    template<>
    struct has<feature::sse3>{
      static const bool enabled=
#ifdef COMPASS_CT_HAS_SSE3
     true;
#else
     false;
#endif

    };

    template<>
    struct has<feature::sse4>{
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
