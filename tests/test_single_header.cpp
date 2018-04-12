#include "catch.hpp"
#include "compass-sh.hpp"

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>


TEST_CASE( "compass_single_header" ){

  SECTION( "compass_works_at_runtime" ){

    auto value = compass::runtime::works();

    REQUIRE(value);

  }

  SECTION( "compass_yields_vendor_name" ){

    auto value = compass::runtime::vendor();
    REQUIRE(value.size()!=0u);

  }
}
