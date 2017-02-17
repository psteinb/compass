#ifndef COMPASS_RT_X86_GNU_CPUID_H_

#include "detail/ct/detect_compiler.hpp"

#ifdef COMPASS_CT_COMP_GCC

#define COMPASS_RT_X86_GNU_CPUID_H_


#include "cpuid.h"

#include <array>
#include <bitset>
#include <cstdint>

#include "detail/tags.hpp"
#include "detail/definitions.hpp"

namespace compass {


  namespace runtime {

    static int extended_get_cpuid(std::uint32_t* regs, std::uint32_t in_eax = 0,std::uint32_t in_ecx = 0){

      unsigned int clean_level = in_eax & 0x80000000;

      if (__get_cpuid_max (clean_level, 0) < in_eax)
        return 0;

      __cpuid_count(in_eax, in_ecx,
                    regs[ct::eax],
                    regs[ct::ebx],
                    regs[ct::ecx],
                    regs[ct::edx]
        );

      return 1;
    }

    static std::array<std::uint32_t,4> cpuid_to_int(std::uint32_t in_eax = 0,
                                                    std::uint32_t in_ebx = 0,
                                                    std::uint32_t in_ecx = 0,
                                                    std::uint32_t in_edx = 0){

      static std::array<std::uint32_t,4> value = {in_eax,in_ebx,in_ecx,in_edx};

#ifdef __get_cpuid_count
      int cpuid_rvalue = __get_cpuid_count(in_eax,
                                           in_ecx,
                                           &value[ct::eax],
                                           &value[ct::ebx],
                                           &value[ct::ecx],
                                           &value[ct::edx]);
#else
      int cpuid_rvalue = extended_get_cpuid(&value[0],in_eax,in_ecx);
#endif

      if(cpuid_rvalue < 1){
        value = {0,0,0,0};
        return value;
      } else {
        return value;
      }

    }


  };

};
#endif /* COMPASS_CT_COMP_GCC */
#endif /* COMPASS_CT_GNU_IMPL_H_ */
