#include "catch.hpp"
#include "compass_fixture.hpp"

#include "compass.hpp"

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

TEST_CASE_METHOD( host_reference, "machine_specific" ){

  SECTION( "vendor_right" ){

    auto value = compass::runtime::vendor();

    REQUIRE(value.size()!=0u);

    std::transform(value.begin(), value.end(),
                   value.begin(),
                   ::tolower);

    REQUIRE(value.find(expected_vendor)!=std::string::npos);

  }


  SECTION( "brand_right" ){

    auto value = compass::runtime::brand();

    REQUIRE(value.empty()!=true);
    REQUIRE_THAT(value, Catch::Matchers::Contains(expected_brand) );

  }

  SECTION( "device_name_right" ){

    auto value = compass::runtime::device_name();

    REQUIRE(value.empty()!=true);
    REQUIRE_THAT(value, Catch::Matchers::Contains(expected_device_name) );

  }

  SECTION( "ncores_right" ){

    auto value = compass::runtime::threads();

    REQUIRE(value!=0);
    REQUIRE(value==expected_ncores);
  }

  // SECTION( "physical_cores_right" ){

  //   auto value = compass::runtime::physical_threads();

  //   REQUIRE(value!=0);
  //   REQUIRE(value==expected_nphyscores);
  // }


  SECTION( "has_sse_right" ){

    auto value = compass::runtime::has(compass::x86::feature::sse());

    REQUIRE(value==expected_has_sse);

  }

  SECTION( "has_sse2_right" ){

    auto value = compass::runtime::has(compass::x86::feature::sse2());

    REQUIRE(value==expected_has_sse2);

  }

  SECTION( "has_sse3_right" ){

    auto value = compass::runtime::has(compass::x86::feature::sse3());

    REQUIRE(value==expected_has_sse3);

  }

  SECTION( "has_sse4_right" ){

    auto value = compass::runtime::has(compass::x86::feature::sse4());

    REQUIRE(value==expected_has_sse4);

  }

  SECTION( "has_avx_right" ){

    auto value = compass::runtime::has(compass::x86::feature::avx());

    REQUIRE(value==expected_has_avx);

  }


  SECTION( "has_avx2_right" ){

    auto value = compass::runtime::has(compass::x86::feature::avx2());

    REQUIRE(value==expected_has_avx2);

  }


}
