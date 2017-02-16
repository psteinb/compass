#ifndef COMPASS_RT_UNSUPPORTED_IMPL_H_
#define COMPASS_RT_UNSUPPORTED_IMPL_H_

#include "detail/ct/detect_os.hpp"
#include "detail/ct/detect_compiler.hpp"
#include "detail/ct/detect_arch.hpp"

#include "detail/definitions.hpp"
#include "detail/tags.hpp"

#include <iostream>
#include <string>
#include <bitset>



namespace compass {

  namespace runtime {

    namespace detail {


      static bool works(ct::unsupported_tag) {

        return false;

      }


      static std::string vendor(ct::unsupported_tag) {


        std::string vendor_name = "";

        return vendor_name;


      }

      static std::string brand(ct::unsupported_tag) {

        std::string value = "";
        return value;

      }

      static std::string device_name(ct::unsupported_tag) {

        std::string vendor_name = "";
        return vendor_name;

      }


      static bool has(feature::sse , ct::unsupported_tag){

        return false;

      }

      static bool has(feature::sse2 , ct::unsupported_tag){

        return false;

      }

      static bool has(feature::sse3 , ct::unsupported_tag){


        return false;
      }


      static bool has(feature::sse4 , ct::unsupported_tag){

        return false;
      }

      static bool has(feature::avx , ct::unsupported_tag){


        return false;
      }

      static bool has(feature::avx2 , ct::unsupported_tag){

        return false;
      }

    };
  };

};
#endif /* COMPASS_RT_UNSUPPORTED_IMPL_H_ */
