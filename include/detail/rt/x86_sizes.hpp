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

        struct cacheline
        {

          static std::uint32_t level(int _lvl, ct::x86_tag){

            auto regs = cpuid(4,0,_lvl - 1);

            if(!bitview(regs[ct::eax]).test(0))
              return 0;//bitview(regs[ct::eax]).test(0) set if cache level does not exist

            std::uint32_t value = bitview(regs[ct::ebx]).range(0,11);

            return value + 1;
          }
        };

        struct cache
        {

          static std::uint32_t level(int _lvl, ct::x86_tag){

            auto regs = cpuid(4,0,_lvl - 1);

            if(!bitview(regs[ct::eax]).test(0))
              return 0;//bitview(regs[ct::eax]).test(0) set if cache level does not exist

            std::uint32_t ways = 1 + bitview(regs[ct::ebx]).range(22,31);
            std::uint32_t partitions = 1 + bitview(regs[ct::ebx]).range(12,21);
            std::uint32_t line_size = 1 + bitview(regs[ct::ebx]).range(0,11);
            std::uint32_t sets = 1 + regs[ct::ecx];


            std::uint32_t value = ways*partitions*line_size*sets;

            return value;
          }
        };



      };
    };//detail

  };//runtime

};
#endif /* COMPASS_RT_X86_SIZES_H_ */
