#ifndef _COMPASS_MSVC_IMPL_H_
#define _COMPASS_MSVC_IMPL_H_

#include <array>
#include <bitset>
#include <cstdint>

#include "intrin.h"
#include "../compass_tags.hpp"

namespace compass {

  namespace compiletime {
    
    
	  static std::array<std::bitset<32>, 4> cpuid(std::uint32_t level,
		  std::uint32_t in_eax = 0,
		  std::uint32_t in_ebx = 0,
		  std::uint32_t in_ecx = 0,
		  std::uint32_t in_edx = 0) {

		  std::int32_t regs[4] = { static_cast<std::int32_t>(in_eax),
			  static_cast<std::int32_t>(in_ebx),
				  static_cast<std::int32_t>(in_ecx),
					  static_cast<std::int32_t>(in_edx)
		  };

		  __cpuid(regs,
			  (std::int32_t)level);


		  static std::array<std::bitset<32>, 4> value;

		  if (!(regs[eax] || regs[ebx] || regs[ecx] || regs[edx])) {
			  return value;
		  }


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
#endif /* _COMPASS_MSVC_IMPL_H_ */
