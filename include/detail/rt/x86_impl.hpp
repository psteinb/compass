#ifndef COMPASS_RT_X86_IMPL_H_
#define COMPASS_RT_X86_IMPL_H_

#include "detail/ct/detect_os.hpp"
#include "detail/ct/detect_compiler.hpp"
#include "detail/ct/detect_arch.hpp"

#include "detail/rt/x86_cpuid.hpp"
#include "detail/tags.hpp"
#include "detail/definitions.hpp"

#include <iostream>
#include <string>
#include <bitset>

namespace compass {

  namespace runtime {

    namespace detail {


      static bool works(ct::x86_tag) {

        auto regs = rt::cpuid(0);

        if(regs.size())
          return true;
        else
          return false;

      }


      static std::string vendor(ct::x86_tag) {


        std::array<std::uint32_t,4> regs = rt::cpuid_to_int(0);

        std::string vendor_name = "";

        if(!regs.empty()){
          vendor_name.resize(3*4);

          std::copy(reinterpret_cast<char*>(&regs[ct::ebx]),reinterpret_cast<char*>(&regs[ct::ebx])+4,
                    vendor_name.begin());
          std::copy(reinterpret_cast<char*>(&regs[ct::edx]),reinterpret_cast<char*>(&regs[ct::edx])+4,
                    vendor_name.begin()+4);
          std::copy(reinterpret_cast<char*>(&regs[ct::ecx]),reinterpret_cast<char*>(&regs[ct::ecx])+4,
                    vendor_name.begin()+8);
        }

        return vendor_name;


      }

      static std::string brand(ct::x86_tag) {

        std::string value = "";
        auto regs = rt::cpuid(0x80000000);
        if(regs[ct::eax].to_ulong() >= 0x80000004){
          value = "found something";
          std::uint32_t readcpuid[3] = {regs[ct::ebx].to_ulong(),
                                        regs[ct::edx].to_ulong(),
                                        regs[ct::ecx].to_ulong()
          };
          value.resize(3*4);
          std::copy(reinterpret_cast<char*>(&readcpuid[0]),reinterpret_cast<char*>(&readcpuid[0])+value.size(),
                    value.begin());
        }
        return value;

      }


      static std::string device_name(ct::x86_tag) {

        std::string value = compass::runtime::detail::brand(ct::x86_tag());

        return value;

      }


      static bool has(feature::sse , ct::x86_tag){

        std::array<std::bitset<32>,4> regs = rt::cpuid(1);

        if(regs.empty()){
          std::cerr << "unsupported cpuid level detected\n";
        }

        bool value = regs[ct::edx].test(25);
        return value;
      }

      static bool has(feature::sse2 , ct::x86_tag){

        std::array<std::bitset<32>,4> regs = rt::cpuid(1);

        if(regs.empty()){
          std::cerr << "unsupported cpuid level detected\n";
        }

        bool value = regs[ct::edx].test(26);
        return value;
      }

      static bool has(feature::sse3 , ct::x86_tag){

        std::array<std::bitset<32>,4> regs = rt::cpuid(1);

        if(regs.empty()){
          std::cerr << "unsupported cpuid level detected\n";
        }

        bool value = regs[ct::ecx].test(9) | regs[ct::ecx].test(0) | regs[ct::ecx].test(3);
        return value;
      }


      static bool has(feature::sse4 , ct::x86_tag){

        std::array<std::bitset<32>,4> regs = rt::cpuid(1);

        if(regs.empty()){
          std::cerr << "unsupported cpuid level detected\n";
        }

        bool value = regs[ct::ecx].test(19) | regs[ct::ecx].test(20);

        return value;
      }

      static bool has(feature::avx , ct::x86_tag){

        std::array<std::bitset<32>,4> regs = rt::cpuid(1);

        if(regs.empty()){
          std::cerr << "unsupported cpuid level detected\n";
        }

        bool value = regs[ct::ecx].test(28);

        return value;
      }

      static bool has(feature::avx2 , ct::x86_tag){

        std::array<std::bitset<32>,4> regs = rt::cpuid(7);

        bool value = regs[ct::ebx].test(5);

        return value;
      }

    };
  };

};
#endif /* COMPASS_RT_X86_IMPL_H_ */
