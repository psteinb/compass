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

    auto value = compass::runtime::size::cacheline::level(1);
    REQUIRE(value>0u);

  }
}


