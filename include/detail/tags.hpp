#ifndef COMPASS_TAGS_H_
#define COMPASS_TAGS_H_

#include "detail/definitions.hpp"

namespace compass {


        namespace x86 {

                namespace feature {

                        struct xsave       { static constexpr std::uint32_t leaf_id = 1; static constexpr std::uint32_t reg_index = ct::ecx; static constexpr std::uint32_t bit_index = 26; };
                        struct osxsave     { static constexpr std::uint32_t leaf_id = 1; static constexpr std::uint32_t reg_index = ct::ecx; static constexpr std::uint32_t bit_index = 27; };

                        struct smx         { static constexpr std::uint32_t leaf_id = 1; static constexpr std::uint32_t reg_index = ct::ecx; static constexpr std::uint32_t bit_index = 6; };
                        struct cx16        { static constexpr std::uint32_t leaf_id = 1; static constexpr std::uint32_t reg_index = ct::ecx; static constexpr std::uint32_t bit_index = 13;};
                        struct aes         { static constexpr std::uint32_t leaf_id = 1; static constexpr std::uint32_t reg_index = ct::ecx; static constexpr std::uint32_t bit_index = 25;};
                        struct f16c        { static constexpr std::uint32_t leaf_id = 1; static constexpr std::uint32_t reg_index = ct::ecx; static constexpr std::uint32_t bit_index = 29;};
                        struct sgx         { static constexpr std::uint32_t leaf_id = 7; static constexpr std::uint32_t reg_index = ct::ebx; static constexpr std::uint32_t bit_index = 2; };
                        struct bmi1        { static constexpr std::uint32_t leaf_id = 7; static constexpr std::uint32_t reg_index = ct::ebx; static constexpr std::uint32_t bit_index = 3; };
                        struct bmi2        { static constexpr std::uint32_t leaf_id = 7; static constexpr std::uint32_t reg_index = ct::ebx; static constexpr std::uint32_t bit_index = 8; };
                        struct erms        { static constexpr std::uint32_t leaf_id = 7; static constexpr std::uint32_t reg_index = ct::ebx; static constexpr std::uint32_t bit_index = 9; };
                        struct vpclmulqdq  { static constexpr std::uint32_t leaf_id = 7; static constexpr std::uint32_t reg_index = ct::ecx; static constexpr std::uint32_t bit_index = 10;};

                        //SIMD instruction sets
                        //128bit wide
                        struct sse   { static constexpr std::uint32_t leaf_id = 1; static constexpr std::uint32_t reg_index = ct::edx; static constexpr std::uint32_t bit_index = 25; };
                        struct sse2  { static constexpr std::uint32_t leaf_id = 1; static constexpr std::uint32_t reg_index = ct::edx; static constexpr std::uint32_t bit_index = 26; };
                        struct ssse3 { static constexpr std::uint32_t leaf_id = 1; static constexpr std::uint32_t reg_index = ct::ecx; static constexpr std::uint32_t bit_index = ~0; };
                        using  sse3 = ssse3;

                        struct sse4_1 { static constexpr std::uint32_t leaf_id = 1; static constexpr std::uint32_t reg_index = ct::ecx; static constexpr std::uint32_t bit_index = 19; };
                        struct sse4_2 { static constexpr std::uint32_t leaf_id = 1; static constexpr std::uint32_t reg_index = ct::ecx; static constexpr std::uint32_t bit_index = 20; };
                        struct sse4 {}; //logical and of sse4_1 and sse4_1

                        //256bit wide
                        struct fma3 {static constexpr std::uint32_t leaf_id = 1; static constexpr std::uint32_t reg_index = ct::ecx; static constexpr std::uint32_t bit_index = 12;};
                        struct avx  {static constexpr std::uint32_t leaf_id = 1; static constexpr std::uint32_t reg_index = ct::ecx; static constexpr std::uint32_t bit_index = 28;};
                        struct avx2 {static constexpr std::uint32_t leaf_id = 7; static constexpr std::uint32_t reg_index = ct::ebx; static constexpr std::uint32_t bit_index =  5;};

                        //512bit wide
                        struct avx512f          {static constexpr std::uint32_t leaf_id = 7; static constexpr std::uint32_t reg_index = ct::ebx; static constexpr std::uint32_t bit_index = 16;};
                        struct avx512cd         {static constexpr std::uint32_t leaf_id = 7; static constexpr std::uint32_t reg_index = ct::ebx; static constexpr std::uint32_t bit_index = 28;};
                        struct avx512er         {static constexpr std::uint32_t leaf_id = 7; static constexpr std::uint32_t reg_index = ct::ebx; static constexpr std::uint32_t bit_index = 27;};
                        struct avx512pf         {static constexpr std::uint32_t leaf_id = 7; static constexpr std::uint32_t reg_index = ct::ebx; static constexpr std::uint32_t bit_index = 26;};
                        struct avx512bw         {static constexpr std::uint32_t leaf_id = 7; static constexpr std::uint32_t reg_index = ct::ebx; static constexpr std::uint32_t bit_index = 30;};
                        struct avx512dq         {static constexpr std::uint32_t leaf_id = 7; static constexpr std::uint32_t reg_index = ct::ebx; static constexpr std::uint32_t bit_index = 17;};
                        struct avx512vl         {static constexpr std::uint32_t leaf_id = 7; static constexpr std::uint32_t reg_index = ct::ebx; static constexpr std::uint32_t bit_index = 31;};
                        struct avx512ifma       {static constexpr std::uint32_t leaf_id = 7; static constexpr std::uint32_t reg_index = ct::ebx; static constexpr std::uint32_t bit_index = 21;};
                        struct avx512vbmi       {static constexpr std::uint32_t leaf_id = 7; static constexpr std::uint32_t reg_index = ct::ecx; static constexpr std::uint32_t bit_index =  1;};
                        struct avx512vbmi2      {static constexpr std::uint32_t leaf_id = 7; static constexpr std::uint32_t reg_index = ct::ecx; static constexpr std::uint32_t bit_index =  6;};
                        struct avx512vnni       {static constexpr std::uint32_t leaf_id = 7; static constexpr std::uint32_t reg_index = ct::ecx; static constexpr std::uint32_t bit_index = 11;};
                        struct avx512bitalg     {static constexpr std::uint32_t leaf_id = 7; static constexpr std::uint32_t reg_index = ct::ecx; static constexpr std::uint32_t bit_index = 12;};
                        struct avx512vpopcntdq  {static constexpr std::uint32_t leaf_id = 7; static constexpr std::uint32_t reg_index = ct::ecx; static constexpr std::uint32_t bit_index = 14;};
                        struct avx512_4vnniw    {static constexpr std::uint32_t leaf_id = 7; static constexpr std::uint32_t reg_index = ct::edx; static constexpr std::uint32_t bit_index =  2;};
                        struct avx512_4vbmi2    {static constexpr std::uint32_t leaf_id = 7; static constexpr std::uint32_t reg_index = ct::edx; static constexpr std::uint32_t bit_index =  3;};
                        struct avx512           {}; //logical and of the above

                };

        }; //x86
};
#endif /* COMPASS_TAGS_H_ */
