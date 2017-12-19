#ifndef COMPASS_RT_X86_GNU_CPUID_H_

#include "detail/ct/detect_compiler.hpp"

#ifdef COMPASS_CT_COMP_GCC

#define COMPASS_RT_X86_GNU_CPUID_H_

#include "detail/tags.hpp"
#include "detail/definitions.hpp"
#include "detail/rt/x86/cpuid_common.hpp"

#include <array>
#include <cstdint>


namespace compass {


  namespace runtime {

    static std::array<std::uint32_t,4> cpuid(std::uint32_t level,
                                             std::uint32_t in_eax = 0,
                                             std::uint32_t in_ebx = 0,
                                             std::uint32_t in_ecx = 0,
                                             std::uint32_t in_edx = 0){

      std::array<std::uint32_t,4> regs = {in_eax,in_ebx,in_ecx,in_edx};
      int cpuid_rvalue = __get_cpuid(level,
                                     &regs[ct::eax],
                                     &regs[ct::ebx],
                                     &regs[ct::ecx],
                                     &regs[ct::edx]
        );

      if(cpuid_rvalue < 1){
        return {0,0,0,0};
      }

      return regs;

    }

  };

};
#endif /* COMPASS_CT_COMP_GCC */
#endif /* COMPASS_CT_GNU_IMPL_H_ */
