#ifndef COMPASS_RT_X86_CPUID_H

#include "detail/ct/detect_arch.hpp"

#ifdef COMPASS_CT_ARCH_X86
#define COMPASS_RT_X86_CPUID_H

#include "detail/rt/x86/llvm_cpuid.hpp"
#include "detail/rt/x86/gnu_cpuid.hpp"
#include "detail/rt/x86/msvc_cpuid.hpp"
#include "detail/rt/x86/intel_cpuid.hpp"

#include <array>
#include <bitset>
#include <cstdint>

namespace compass {


	namespace runtime {

		static std::array<std::bitset<32>, 4> cpuid(std::uint32_t in_eax = 0,
													std::uint32_t in_ebx = 0,
													std::uint32_t in_ecx = 0,
													std::uint32_t in_edx = 0) {

			auto regs = cpuid_to_int(in_eax, in_ebx, in_ecx, in_edx);

			static std::array<std::bitset<32>, 4> value;

			value[ct::eax] = regs[ct::eax];
			value[ct::ebx] = regs[ct::ebx];
			value[ct::ecx] = regs[ct::ecx];
			value[ct::edx] = regs[ct::edx];

			return value;

		}

	};

};

#endif /* COMPASS_CT_ARCH_X86 */

#endif /* X86_CPUID_H */
