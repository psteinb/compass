#ifndef COMPASS_RT_X86_META_H_
#define COMPASS_RT_X86_META_H_

#include "detail/ct/detect_os.hpp"
#include "detail/ct/detect_compiler.hpp"
#include "detail/ct/detect_arch.hpp"

#include "detail/rt/x86_cpuid.hpp"

#include <iostream>
#include <string>
#include <algorithm>
#include <thread>

namespace compass {

  namespace runtime {

    namespace detail {

      static std::string vendor(ct::x86_tag) {


        std::array<std::uint32_t,4> regs = rt::cpuid(0);

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

      //for details, see https://en.wikipedia.org/wiki/CPUID#EAX=80000002h,80000003h,80000004h:_Processor_Brand_String
      static std::string brand(ct::x86_tag) {

        std::string value = "";
        auto regs = rt::cpuid(0x80000000);
        if(regs[ct::eax] < 0x80000004)
          return value;

        value.resize(48);
        char* value_begin = &value[0];
        for(std::uint32_t i = 2; i<5;++i){
          auto ret = rt::cpuid(0x80000000 + i);

          for(std::uint32_t r = 0; r<4;++r){
            std::uint32_t* tgt = reinterpret_cast<std::uint32_t*>(value_begin + (i-2)*16u + r*4u);
            *tgt = ret[r];
          }

        }

        return value;

      }


      static std::string device_name(ct::x86_tag) {

        std::string brand_str = compass::runtime::detail::brand(ct::x86_tag());
        std::string vendor = compass::runtime::detail::vendor(ct::x86_tag());
        std::size_t find_pos = 0;

        bool is_intel = false;
        bool is_amd = false;

        //remove Genuine in Vendor string if present, Intel host
        if((find_pos = vendor.find("Genuine"))!=std::string::npos){
            vendor.erase(find_pos,7);
            is_intel = true;
        }

        //remove Authentic in Vendor string if present, AMD host, e.g. AMD EPYC 7401P 24-Core Processor
        if((find_pos = vendor.find("Authentic"))!=std::string::npos){
            vendor.erase(find_pos,9);
            is_amd = true;
        }

        std::string value = "";

        if((find_pos = brand_str.find(vendor)) != std::string::npos){

          if(is_intel){
            //based on the Intel chip test strings that are known
            auto second_bracket_itr = brand_str.rfind(")");
            auto last_at_itr = brand_str.rfind("@");
            value = brand_str.substr(second_bracket_itr+1,last_at_itr-(second_bracket_itr+1));

            if((find_pos = value.find(" CPU "))!=std::string::npos){
              value.erase(find_pos,5);
            }

            //TODO: why run this 2 times?
            if((find_pos = value.find(" CPU "))!=std::string::npos){
              value.erase(find_pos,5);
            }

            value.erase(std::remove_if(value.begin(), value.end(), isspace), value.end());
          }

          if(is_amd){

            auto end_itr = brand_str.rfind("Processor");
            value = brand_str.substr(find_pos+4,end_itr-4);

          }
        }
        return value;

      }

    };//detail

  };//runtime

};//compass
#endif /* COMPASS_RT_X86_META_H_ */
