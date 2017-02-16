#ifndef COMPASS_RT_LINUX_BASED_IMPL_H_


#include "detail/ct/detect_os.hpp"

#ifdef COMPASS_CT_OS_LINUX

#define COMPASS_RT_LINUX_BASED_IMPL_H_
#include "detail/ct/detect_arch.hpp"

#include "detail/definitions.hpp"
#include "detail/tags.hpp"

#include <iostream>
#include <string>
#include <bitset>



namespace compass {

  namespace runtime {

    namespace detail {


      static bool works(ct::through_os_tag) {

        std::fstream proc_cpuinfo("/proc/cpuinfo");

        if(proc_cpuinfo.is_open())
          return true;
        else
          return false;

      }


      static std::string vendor(ct::through_os_tag) {


        std::string vendor_name = "";

        return vendor_name;


      }

      static std::string brand(ct::through_os_tag) {

        std::string value = "";
        return value;

      }

      static std::string device_name(ct::through_os_tag) {

        std::string vendor_name = "";
        return vendor_name;

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
#endif /* COMPASS_RT_LINUX_BASED_IMPL_H_ */
