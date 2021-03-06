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


      static bool has(feature::sse , ct::x86_tag){

        auto regs = rt::cpuid(1);

        if(std::count(regs.cbegin(), regs.cend(),0) == regs.size()){
          std::cerr << "unsupported cpuid level detected\n";
        }

        bool value = bitview(regs[ct::edx]).test(25);
        return value;
      }

      static bool has(feature::sse2 , ct::x86_tag){

        auto regs = rt::cpuid(1);

        if(regs.empty()){
          std::cerr << "unsupported cpuid level detected\n";
        }

        bool value = bitview(regs[ct::edx]).test(26);
        return value;
      }

      static bool has(feature::sse3 , ct::x86_tag){

        auto regs = rt::cpuid(1);

        if(regs.empty()){
          std::cerr << "unsupported cpuid level detected\n";
        }

        bool value = bitview(regs[ct::ecx]).test(9) |
          bitview(regs[ct::ecx]).test(0) |
          bitview(regs[ct::ecx]).test(3);
        return value;
      }


      static bool has(feature::sse4 , ct::x86_tag){

        auto regs = rt::cpuid(1);

        if(regs.empty()){
          std::cerr << "unsupported cpuid level detected\n";
        }

        bool value = bitview(regs[ct::ecx]).test(19) |
          bitview(regs[ct::ecx]).test(20);

        return value;
      }

      static bool has(feature::avx , ct::x86_tag){

        auto regs = rt::cpuid(1);

        if(regs.empty()){
          std::cerr << "unsupported cpuid level detected\n";
        }

        bool value = bitview(regs[ct::ecx]).test(28);

        return value;
      }

      static bool has(feature::avx2 , ct::x86_tag){

        auto regs = rt::cpuid(7,0,0,0);

        bool value = bitview(regs[ct::ebx]).test(5);

        return value;
      }

    };//detail

  };//runtime

};
#endif /* COMPASS_RT_X86_IMPL_H_ */
