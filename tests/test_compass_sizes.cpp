#include "catch.hpp"
#include "compass_fixture.hpp"

#include "compass.hpp"

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>


TEST_CASE_METHOD( host_reference, "cacheline_size" ){

  SECTION( "L1d" ){

    auto value = compass::runtime::size::cacheline::level(1);

    REQUIRE(value==expected_L1d_linesize);

  }

  SECTION( "L2" ){

    auto value = compass::runtime::size::cacheline::level(2);

    REQUIRE(value==expected_L2_linesize);

  }

  SECTION( "L3" ){

    auto value = compass::runtime::size::cacheline::level(3);

    REQUIRE(value==expected_L3_linesize);

  }


}


TEST_CASE_METHOD( host_reference, "cache_size" ){

  SECTION( "L1d_cache_size" ){

    auto value = compass::runtime::size::cache::level(1);

    REQUIRE(value==expected_L1d_size_kB*1024);

  }

  SECTION( "L2_cache_size" ){

    auto value = compass::runtime::size::cache::level(2);

    REQUIRE(value==expected_L2_size_kB*1024);

  }

  SECTION( "L3_cache_size" ){

    auto value = compass::runtime::size::cache::level(3);

    REQUIRE(value==expected_L3_size_kB*1024);

  }

}
