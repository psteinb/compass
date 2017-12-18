#ifndef COMPASS_TAGS_H_
#define COMPASS_TAGS_H_


namespace compass {


    namespace feature {


        //SIMD instruction sets
        //128bit wide
        struct sse  {};
        struct sse2 {};
        struct sse3 {};
        struct sse4 {};

        //256bit wide
        struct avx  {};
        struct avx2 {};


    };


};
#endif /* COMPASS_TAGS_H_ */
