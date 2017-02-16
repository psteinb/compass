#ifndef COMPASS_RT_LINUX_OS_IMPL_H_


#include "detail/ct/detect_os.hpp"

#ifdef COMPASS_CT_OS_LINUX

#define COMPASS_RT_LINUX_OS_IMPL_H_
#include "detail/ct/detect_arch.hpp"

#include "detail/definitions.hpp"
#include "detail/tags.hpp"

#include <iostream>
#include <string>
#include <fstream>



namespace compass {

  namespace runtime {

    namespace detail {


      static bool works(ct::through_os_tag) {

        std::ifstream proc_cpuinfo("/proc/cpuinfo");

        if(proc_cpuinfo.is_open())
          return true;
        else
          return false;

      }


      static std::string vendor(ct::through_os_tag) {

        std::ifstream proc_cpuinfo("/proc/cpuinfo");
        std::string line;
        std::string value = "";
        while (std::getline(proc_cpuinfo, line))
        {
          if(line.find("vendor_id       :") == 0){
            value.resize(line.size()-15);
            std::copy(line.begin()+16,line.end(),value.begin());
            break;
          }
        }
        return value;


      }

      static std::string brand(ct::through_os_tag) {

        std::ifstream proc_cpuinfo("/proc/cpuinfo");
        std::string line;
        std::string value = "";
        while (std::getline(proc_cpuinfo, line))
        {

#ifdef COMPASS_CT_ARCH_POWER
          if(line.find("cpu             :") == 0){
            value.resize(line.size()-15);
            std::copy(line.begin()+16,line.end(),value.begin());
            break;
          }
#else
          if(line.find("model name      :") == 0){
            value.resize(line.size()-15);
            std::copy(line.begin()+16,line.end(),value.begin());
            break;
          }
#endif
        }

        return value;

      }

      static std::string device_name(ct::through_os_tag) {

        std::string brand_str = brand(ct::through_os_tag());
        std::string device_name = "";
#ifdef COMPASS_CT_ARCH_POWER
        device_name = brand_str.substr(brand_str.find(" "));
#else
        std::string vendor = compass::runtime::detail::vendor(ct::x86_tag());
        std::size_t find_pos = 0;
        if((find_pos = vendor.find("Genuine"))!=std::string::npos){
            vendor.erase(find_pos,7);
        }

        if(brand_str.find(vendor) != std::string::npos){
        //based on the Intel chip test strings that are known
          auto second_bracket_itr = brand_str.rfind(")");
          auto last_at_itr = brand_str.rfind("@");
          device_name = brand_str.substr(second_bracket_itr,last_at_itr-second_bracket_itr);

          if((find_pos = device_name.find(" CPU"))!=std::string::npos){
            device_name.erase(find_pos,4);
          }
        }
#endif
        return device_name;

      }


      static bool has(feature::sse , ct::through_os_tag){

        return false;

      }

      static bool has(feature::sse2 , ct::through_os_tag){

        return false;

      }

      static bool has(feature::sse3 , ct::through_os_tag){


        return false;
      }


      static bool has(feature::sse4 , ct::through_os_tag){

        return false;
      }

      static bool has(feature::avx , ct::through_os_tag){


        return false;
      }

      static bool has(feature::avx2 , ct::through_os_tag){

        return false;
      }

    };
  };

};

#endif /* COMPASS_CT_OS_LINUX */
#endif /* COMPASS_RT_LINUX_OS_IMPL_H_ */
