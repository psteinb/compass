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


    static std::array<std::bitset<32>,4> cpuid(std::uint32_t level,
                           std::uint32_t in_eax = 0,
                           std::uint32_t in_ebx = 0,
                           std::uint32_t in_ecx = 0,
                           std::uint32_t in_edx = 0){

      std::uint32_t regs[4] = {in_eax,in_ebx,in_ecx,in_edx};
      int cpuid_rvalue = __get_cpuid(level,
                     &regs[ct::eax],
                     &regs[ct::ebx],
                     &regs[ct::ecx],
                     &regs[ct::edx]
                     );

      static std::array<std::bitset<32>,4> value;

      if(cpuid_rvalue < 1){
    return value;
      }


      value[ct::eax] = regs[ct::eax];
      value[ct::ebx] = regs[ct::ebx];
      value[ct::ecx] = regs[ct::ecx];
      value[ct::edx] = regs[ct::edx];

      return value;

    }

    static std::array<std::uint32_t,4> cpuid_to_int(std::uint32_t level,
                            std::uint32_t in_eax = 0,
                            std::uint32_t in_ebx = 0,
                            std::uint32_t in_ecx = 0,
                            std::uint32_t in_edx = 0){

      // static std::array<std::uint32_t,4> value = {in_eax, in_ebx, in_ecx, in_edx};
      // int cpuid_rvalue = __get_cpuid(level,
      //                     &value[eax],
      //                     &value[ebx],
      //                     &value[ecx],
      //                     &value[edx]
      //                     );

      // if(cpuid_rvalue < 1){
      //    value = std::array<std::uint32_t,4>();
      // }
      static std::array<std::bitset<32>,4> temp = cpuid(level,
                                in_eax,
                                in_ebx,
                                in_ecx,
                                in_edx);

      static std::array<std::uint32_t,4> value;
      for(std::uint32_t i = 0 ; i < temp.size();++i)
        value[i] = temp[i].to_ulong();

      return value;

    }

  };

};
#endif /* COMPASS_CT_COMP_GCC */
#endif /* COMPASS_CT_GNU_IMPL_H_ */
