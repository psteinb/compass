#ifndef COMPASS_TAGS_H_
#define COMPASS_TAGS_H_

namespace compass {


        namespace x86 {

                namespace feature {

                        ///////////////////////////
                        //x86 based features
                        ///////////////////////////

                        //SIMD instruction sets
                        //128bit wide
                        struct sse  {};
                        struct sse2 {};
                        struct sse3 {};
                        using  ssse3 = sse3;

                        struct sse4_1 {};
                        struct sse4_2 {};
                        struct sse4 {}; //logical and of sse4_1 and sse4_1

                        //256bit wide
                        struct avx  {};
                        struct avx2 {};

                        //512bit wide
                        struct avx512f          {};
                        struct avx512cd         {};
                        struct avx512er         {};
                        struct avx512pf         {};
                        struct avx512bw         {};
                        struct avx512dq         {};
                        struct avx512vl         {};
                        struct avx512ifma       {};
                        struct avx512vbmi       {};
                        struct avx512vbmi2      {};
                        struct avx512vnni       {};
                        struct avx512bitalg     {};
                        struct avx512vpopcntdq  {};
                        struct avx512_4vnniw    {};
                        struct avx512_4vbmi2    {};
                        struct avx512           {}; //logical and of the above

                };

        }; //x86
};
#endif /* COMPASS_TAGS_H_ */
