#ifndef COMPASS_RT_X86_LLVM_CPUID_H_
#define COMPASS_RT_X86_LLVM_CPUID_H_

#include "detail/ct/detect_compiler.hpp"

#ifdef COMPASS_CT_COMP_CLANG

#include <array>
#include <bitset>
#include <cstdint>


#include "detail/tags.hpp"
#include "detail/definitions.hpp"
#include "detail/rt/x86/cpuid_common.hpp"

namespace compass {


  namespace runtime {


    static std::array<std::bitset<32>,4> cpuid(std::uint32_t level,
					       std::uint32_t in_eax = 0,
					       std::uint32_t in_ebx = 0,
					       std::uint32_t in_ecx = 0,
					       std::uint32_t in_edx = 0){

      std::uint32_t regs[4] = {in_eax,in_ebx,in_ecx,in_edx};
      int cpuid_rvalue = __get_cpuid(level,
				 &regs[eax],
				 &regs[ebx],
				 &regs[ecx],
				 &regs[edx]
				 );

      static std::array<std::bitset<32>,4> value;

      if(cpuid_rvalue < 1){
        return value;
      }

      if (level >= 13)
        __cpuid_count (level, 1, regs[eax], regs[ebx], regs[ecx], regs[edx]);
      else if (level >= 7)
        __cpuid_count (level, 0, regs[eax], regs[ebx], regs[ecx], regs[edx]);
      else
        __cpuid (level, regs[eax], regs[ebx], regs[ecx], regs[edx]);

      if(level>=7)

      value[eax] = regs[eax];
      value[ebx] = regs[ebx];
      value[ecx] = regs[ecx];
      value[edx] = regs[edx];

      return value;

    }

    static std::array<std::uint32_t,4> cpuid_to_int(std::uint32_t level,
						    std::uint32_t in_eax = 0,
						    std::uint32_t in_ebx = 0,
						    std::uint32_t in_ecx = 0,
						    std::uint32_t in_edx = 0){

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
#endif /* COMPASS_CT_COMP_CLANG */
#endif /* COMPASS_CT_LLVM_IMPL_H_ */
