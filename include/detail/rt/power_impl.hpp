#ifndef COMPASS_RT_POWER_IMPL_H_
#define COMPASS_RT_POWER_IMPL_H_

#include "../tags.hpp"

#include <iostream>
#include <string>
#include <fstream>


namespace compass {

  typedef ct::power_tag _compass_power_impl_h_tag_t;

  namespace runtime {

    namespace detail {

      static bool works(_compass_power_impl_h_tag_t) {

        std::ifstream cpuinfo("/proc/cpuinfo");

        if(cpuinfo.is_open())
          return true;
        else
          return false;

      }


      static std::string vendor(_compass_power_impl_h_tag_t) {


        std::string vendor_name = "IBM";

        return vendor_name;


      }

      template <typename feature_t>
      static bool has(feature_t , _compass_power_impl_h_tag_t){

        return false;
      }


    };
  };

};
#endif /* COMPASS_RT_POWER_IMPL_H_ */
