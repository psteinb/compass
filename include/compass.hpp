#ifndef _COMPASS_HPP_
#define _COMPASS_HPP_

#include <type_traits>
#include <cstdint>
#include <string>
#include <thread>
#include "detail/compass_detail.hpp"

namespace compass {


  namespace compiletime {

    static const bool is_gnu(){

      using current_toolchain_t = toolchain::type;

      bool value = std::is_same<current_toolchain_t,gnu_tag>::value;
      return value;

    }

    static const bool is_llvm(){

      using current_toolchain_t = toolchain::type;
      bool value = std::is_same<current_toolchain_t,llvm_tag>::value;
      return value;

    }

    static const bool is_msvc(){

      using current_toolchain_t = toolchain::type;
      bool value = std::is_same<current_toolchain_t,msvc_tag>::value;
      return value;

    }

  };



  namespace runtime {


    static bool works() {

      using current_platform_t = ct::platform::type;
      return detail::works(current_platform_t());

    }

    static std::string vendor() {

      using current_platform_t = ct::platform::type;
      return detail::vendor(current_platform_t());

    }

    static int ncores() {

      return std::thread::hardware_concurrency();

    }

    template <typename feature_t>
    static bool has(feature_t) {

      using current_platform_t = ct::platform::type;
      return detail::has(feature_t(),current_platform_t());

    }

  };//namespace runtime


};//namespace compass

#endif /* _COMPASS_H_ */
