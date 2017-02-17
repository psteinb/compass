#ifndef COMPASS_X86_CPUID_COMMON_H
#define COMPASS_X86_CPUID_COMMON_H

#include "cpuid.h"

namespace compass {


  namespace runtime {

    static int extended_get_cpuid(std::uint32_t* regs,
                                  std::uint32_t in_eax = 0,
                                  std::uint32_t in_ecx = 0){

#ifdef __get_cpuid_count
        return __get_cpuid_count(in_eax,
                                 in_ecx,
                                 &regs[ct::eax],
                                 &regs[ct::ebx],
                                 &regs[ct::ecx],
                                 &regs[ct::edx]);
#endif


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

  }; // runtime

}; //compass

#endif /* COMPASS_X86_CPUID_COMMON_H */
