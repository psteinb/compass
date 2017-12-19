#include "catch.hpp"
#include "compass_fixture.hpp"

#include "compass.hpp"

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>




TEST_CASE_METHOD( host_reference, "machine_specific" ){

  SECTION( "L1d_cacheline_size" ){

    auto value = compass::runtime::size::cacheline::level(1);

    REQUIRE(value==expected_L1d_linesize);

  }

  SECTION( "L1d_cache_size" ){

    auto value = compass::runtime::size::cache::level(1);

    REQUIRE(value==expected_L1d_size_kB);

  }
}
