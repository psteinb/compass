#ifndef COMPASS_RT_X86_LLVM_CPUID_H_
#define COMPASS_RT_X86_LLVM_CPUID_H_

#include "detail/ct/detect_compiler.hpp"

#ifdef COMPASS_CT_COMP_CLANG

#include "cpuid.h"

#include <array>
#include <bitset>
#include <cstdint>


#include "detail/tags.hpp"

#include "detail/definitions.hpp"


namespace compass {


  namespace runtime {


    static std::array<std::uint32_t,4> cpuid_to_int(std::uint32_t level,
                                                    std::uint32_t in_eax = 0,
                                                    std::uint32_t in_ebx = 0,
                                                    std::uint32_t in_ecx = 0,
                                                    std::uint32_t in_edx = 0){

      static std::array<std::uint32_t,4> value = {in_eax,in_ebx,in_ecx,in_edx};

      int cpuid_rvalue = __get_cpuid(level,
                                     &value[ct::eax],
                                     &value[ct::ebx],
                                     &value[ct::ecx],
                                     &value[ct::edx]);
      if(cpuid_rvalue < 1){
        value = {0,0,0,0};
        return value;
      } else {
        return value;
      }
    }

    static std::array<std::bitset<32>,4> cpuid(std::uint32_t level,
                                               std::uint32_t in_eax = 0,
                                               std::uint32_t in_ebx = 0,
                                               std::uint32_t in_ecx = 0,
                                               std::uint32_t in_edx = 0){


      auto regs = cpuid_to_int(level, in_eax, in_ebx, in_ecx, in_edx);

      static std::array<std::bitset<32>,4> value;

      value[ct::eax] = regs[ct::eax];
      value[ct::ebx] = regs[ct::ebx];
      value[ct::ecx] = regs[ct::ecx];
      value[ct::edx] = regs[ct::edx];

      return value;
    }

  };

};
#endif /* COMPASS_CT_COMP_CLANG */
#endif /* COMPASS_CT_LLVM_IMPL_H_ */
