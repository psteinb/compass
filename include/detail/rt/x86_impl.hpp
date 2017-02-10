#ifndef _COMPASS_X86_IMPL_H_
#define _COMPASS_X86_IMPL_H_

#include <iostream>
#include <string>
#include <bitset>

#include "../compass_tags.hpp"



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

        // std::uint32_t bit25 = (1<<25);
        // bool value = (regs[3] & bit25) > 0;
        bool value = regs[ct::edx].test(25);
        return value;
      }

      static bool has(feature::sse2 , _compass_x86_impl_h_tag_t){

        std::array<std::bitset<32>,4> regs = ct::cpuid(1);

        if(regs.empty()){
          std::cerr << "unsupported cpuid level detected\n";
        }

        // std::uint32_t bit26 = (1<<26);
        // bool value = (regs[3] & bit26) > 0;
        bool value = regs[ct::edx].test(26);
        return value;
      }

      static bool has(feature::sse3 , _compass_x86_impl_h_tag_t){

        std::array<std::bitset<32>,4> regs = ct::cpuid(1);

        if(regs.empty()){
          std::cerr << "unsupported cpuid level detected\n";
        }

        // std::uint32_t check_bits = (1<<9) | 1 | (1<<3);
        // bool value = (regs[2] & check_bits) > 0;
        bool value = regs[ct::ecx].test(9) | regs[ct::ecx].test(0) | regs[ct::ecx].test(3);
        return value;
      }


      static bool has(feature::sse4 , _compass_x86_impl_h_tag_t){

        std::array<std::bitset<32>,4> regs = ct::cpuid(1);

        if(regs.empty()){
          std::cerr << "unsupported cpuid level detected\n";
        }

        // std::uint32_t check_bits = (1<<19) | (1<<20);
        // bool value = (regs[2] & check_bits) > 0;
        bool value = regs[ct::ecx].test(19) | regs[ct::ecx].test(20);

        //TODO: check sse4a if AMD is detected?

        return value;
      }

      static bool has(feature::avx , _compass_x86_impl_h_tag_t){

        std::array<std::bitset<32>,4> regs = ct::cpuid(1);

        if(regs.empty()){
          std::cerr << "unsupported cpuid level detected\n";
        }


        // std::uint32_t check_bits = (1<<28);
        // bool value = (regs[2] & check_bits) > 0;
        bool value = regs[ct::ecx].test(28);

        return value;
      }

      static bool has(feature::avx2 , _compass_x86_impl_h_tag_t){

        std::array<std::bitset<32>,4> regs = ct::cpuid(7);

        // std::uint32_t check_bits = (1<<5);
        // bool value = (regs[1] & check_bits) > 0;
        bool value = regs[ct::ebx].test(5);

        return value;
      }

    };
  };

};
#endif /* _COMPASS_X86_IMPL_H_ */
