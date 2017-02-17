#ifndef COMPASS_RT_X86_INTEL_CPUID_H_

#include "detail/ct/detect_compiler.hpp"

#ifdef COMPASS_CT_COMP_INTEL

#define COMPASS_RT_X86_INTEL_CPUID_H_


#include <array>
#include <bitset>
#include <cstdint>

#include "detail/tags.hpp"
#include "detail/definitions.hpp"
#include "detail/rt/x86/cpuid_common.hpp"

namespace compass {


  namespace runtime {



    static std::array<std::uint32_t,4> cpuid_to_int(std::uint32_t in_eax = 0,
                                                    std::uint32_t in_ebx = 0,
                                                    std::uint32_t in_ecx = 0,
                                                    std::uint32_t in_edx = 0){

      static std::array<std::uint32_t,4> value = {~0};

      int cpuid_rvalue = extended_get_cpuid(&value[0],in_eax,in_ecx);

      if(cpuid_rvalue < 1){
        value = {0,0,0,0};
        return value;
      } else {
        return value;
      }

    }


  };

};
#endif /* COMPASS_CT_COMP_INTEL */
#endif /* COMPASS_CT_INTEL_IMPL_H_ */
