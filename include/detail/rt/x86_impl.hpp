#ifndef COMPASS_RT_X86_IMPL_H_
#define COMPASS_RT_X86_IMPL_H_

#include "detail/ct/detect_os.hpp"
#include "detail/ct/detect_compiler.hpp"
#include "detail/ct/detect_arch.hpp"

#include "detail/tags.hpp"
#include "detail/bit_view.hpp"
#include "detail/definitions.hpp"

#include "detail/rt/x86_cpuid.hpp"
#include "detail/rt/x86_meta.hpp"
#include "detail/rt/x86_sizes.hpp"

#include <iostream>
#include <string>
#include <algorithm>
#include <thread>

namespace compass {

  namespace runtime {

    namespace detail {

      using bitview = compass::utility::bit_view<std::uint32_t>;

      static bool works(ct::x86_tag) {

        auto regs = rt::cpuid(0);

        if(regs.size())
          return true;
        else
          return false;

      }

      template <typename feature_t>
      bool has(feature_t , ct::x86_tag){

        auto regs = rt::cpuid(feature_t::leaf_id);

        if(std::count(regs.cbegin(), regs.cend(),0) == regs.size()){
          std::cerr << "unsupported cpuid level detected\n";
        }

        bool value = bitview(regs[feature_t::reg_index]).test(feature_t::bit_index);
        return value;
      }

      // //too difficult for now
      // //https://stackoverflow.com/questions/2901694/programmatically-detect-number-of-physical-processors-cores-or-if-hyper-threadin
      // static std::uint32_t physical_threads(ct::x86_tag) {

      //   std::uint32_t value = 0;

      //   for(std::uint32_t c = 0;c<std::thread::hardware_concurrency();++c){
      //     auto regs = rt::cpuid(11);
      //     if(!(regs[ct::edx]&1)) value++;
      //   }


      //   return value;

      // }

      /////////////////////////////////////////////////////////
      // SPECIAL CASES
      ///////////////////

      static bool has(x86::feature::ssse3 , ct::x86_tag){

        auto regs = rt::cpuid(x86::feature::ssse3::leaf_id);

        if(regs.empty()){
          std::cerr << "unsupported cpuid level detected\n";
        }

        bool value = bitview(regs[x86::feature::ssse3::reg_index]).test(9) |
          bitview(regs[x86::feature::ssse3::reg_index]).test(0) |
          bitview(regs[x86::feature::ssse3::reg_index]).test(3);
        return value;
      }

      static bool has(x86::feature::sse4 , ct::x86_tag){

        bool value = has(x86::feature::sse4_1(), ct::x86_tag()) && has(x86::feature::sse4_2(), ct::x86_tag());
        return value;
      }


      static bool has(x86::feature::avx512 , ct::x86_tag){

        auto regs = rt::cpuid(7);
        bool value = true;
        value &= has(x86::feature::avx512f        () , ct::x86_tag());
        value &= has(x86::feature::avx512cd       () , ct::x86_tag());
        value &= has(x86::feature::avx512er       () , ct::x86_tag());
        value &= has(x86::feature::avx512pf       () , ct::x86_tag());
        value &= has(x86::feature::avx512bw       () , ct::x86_tag());
        value &= has(x86::feature::avx512dq       () , ct::x86_tag());
        value &= has(x86::feature::avx512vl       () , ct::x86_tag());
        value &= has(x86::feature::avx512ifma     () , ct::x86_tag());
        value &= has(x86::feature::avx512vbmi     () , ct::x86_tag());
        value &= has(x86::feature::avx512vbmi2    () , ct::x86_tag());
        value &= has(x86::feature::avx512vnni     () , ct::x86_tag());
        value &= has(x86::feature::avx512bitalg   () , ct::x86_tag());
        value &= has(x86::feature::avx512vpopcntdq() , ct::x86_tag());
        value &= has(x86::feature::avx512_4vnniw  () , ct::x86_tag());
        value &= has(x86::feature::avx512_4vbmi2  () , ct::x86_tag());

        return value;
      }

    };//detail

  };//runtime

};
#endif /* COMPASS_RT_X86_IMPL_H_ */
