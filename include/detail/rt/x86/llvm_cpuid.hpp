#ifndef COMPASS_RT_X86_LLVM_CPUID_H_
#define COMPASS_RT_X86_LLVM_CPUID_H_

#include "detail/ct/detect_compiler.hpp"

#ifdef COMPASS_CT_COMP_CLANG

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

      if (level >= 13)
        __cpuid_count (level, 1, regs[ct::eax], regs[ct::ebx], regs[ct::ecx], regs[ct::edx]);
      else if (level >= 7)
        __cpuid_count (level, 0, regs[ct::eax], regs[ct::ebx], regs[ct::ecx], regs[ct::edx]);
      else
        __cpuid (level, regs[ct::eax], regs[ct::ebx], regs[ct::ecx], regs[ct::edx]);

      return regs;

    }



  };

};
#endif /* COMPASS_CT_COMP_CLANG */
#endif /* COMPASS_CT_LLVM_IMPL_H_ */
