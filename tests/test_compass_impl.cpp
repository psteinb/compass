#include "catch.hpp"

#include "compass.hpp"

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>


TEST_CASE( "compass_fundamentals" ){

  SECTION( "compass_works_at_runtime" ){

    auto value = compass::runtime::works();

    REQUIRE(value);

  }

  SECTION( "compass_yields_vendor_name" ){

    auto value = compass::runtime::vendor();
    REQUIRE(value.size()!=0u);

  }

  SECTION( "compass_yields_non_zero_corecount" ){

    auto value = compass::runtime::threads();
    REQUIRE(value>0u);

  }

  SECTION( "compass_yields_non_zero_L1size" ){

    if(compass::runtime::size::cache::levels_available()){
      auto value = compass::runtime::size::cache::level(1);
      REQUIRE(value>0u);
    } else {
      SUCCEED("no cache architecture available on this host");
    }

  }


}
