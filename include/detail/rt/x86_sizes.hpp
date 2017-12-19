#ifndef COMPASS_RT_X86_SIZES_H_
#define COMPASS_RT_X86_SIZES_H_

#include "detail/ct/detect_os.hpp"
#include "detail/ct/detect_compiler.hpp"
#include "detail/ct/detect_arch.hpp"

#include "detail/rt/x86_cpuid.hpp"
#include "detail/tags.hpp"
#include "detail/bit_view.hpp"
#include "detail/definitions.hpp"

#include <iostream>
#include <string>
#include <algorithm>

namespace compass {

  namespace runtime {

    namespace detail {

      using bitview = compass::utility::bit_view<std::uint32_t>;

      namespace size{

        struct cacheline{

          static std::uint32_t level(int _lvl, ct::x86_tag){

            auto regs = cpuid(0,0x4);


            return regs[ct::ebx];
          }
        };

      };
    };//detail

  };//runtime

};
#endif /* COMPASS_RT_X86_SIZES_H_ */
