#ifndef COMPASS_RT_X86_IMPL_H_
#define COMPASS_RT_X86_IMPL_H_

#include "../tags.hpp"

#include <iostream>
#include <string>
#include <bitset>


namespace compass {

  typedef ct::x86_tag _compass_x86_impl_h_tag_t;

  namespace runtime {

    namespace detail {

      static bool works(_compass_x86_impl_h_tag_t) {

        auto regs = ct::cpuid(0);

        if(regs.size())
          return true;
        else
          return false;

      }


      static std::string vendor(_compass_x86_impl_h_tag_t) {


        std::array<std::uint32_t,4> regs = ct::cpuid_to_int(0);

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


      static bool has(feature::sse , _compass_x86_impl_h_tag_t){

        std::array<std::bitset<32>,4> regs = ct::cpuid(1);

        if(regs.empty()){
          std::cerr << "unsupported cpuid level detected\n";
        }

        bool value = regs[ct::edx].test(25);
        return value;
      }

      static bool has(feature::sse2 , _compass_x86_impl_h_tag_t){

        std::array<std::bitset<32>,4> regs = ct::cpuid(1);

        if(regs.empty()){
          std::cerr << "unsupported cpuid level detected\n";
        }

        bool value = regs[ct::edx].test(26);
        return value;
      }

      static bool has(feature::sse3 , _compass_x86_impl_h_tag_t){

        std::array<std::bitset<32>,4> regs = ct::cpuid(1);

        if(regs.empty()){
          std::cerr << "unsupported cpuid level detected\n";
        }

        bool value = regs[ct::ecx].test(9) | regs[ct::ecx].test(0) | regs[ct::ecx].test(3);
        return value;
      }


      static bool has(feature::sse4 , _compass_x86_impl_h_tag_t){

        std::array<std::bitset<32>,4> regs = ct::cpuid(1);

        if(regs.empty()){
          std::cerr << "unsupported cpuid level detected\n";
        }

        bool value = regs[ct::ecx].test(19) | regs[ct::ecx].test(20);

        return value;
      }

      static bool has(feature::avx , _compass_x86_impl_h_tag_t){

        std::array<std::bitset<32>,4> regs = ct::cpuid(1);

        if(regs.empty()){
          std::cerr << "unsupported cpuid level detected\n";
        }

        bool value = regs[ct::ecx].test(28);

        return value;
      }

      static bool has(feature::avx2 , _compass_x86_impl_h_tag_t){

        std::array<std::bitset<32>,4> regs = ct::cpuid(7);

        bool value = regs[ct::ebx].test(5);

        return value;
      }

    };
  };

};
#endif /* COMPASS_RT_X86_IMPL_H_ */
