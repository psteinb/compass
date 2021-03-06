#include "catch.hpp"
#include "build_machine.hpp"

#include "compass.hpp"

#include <bitset>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

TEST_CASE_METHOD( host_reference, "machine_specific" ){

  SECTION( "vendor_right" ){

    auto value = compass::runtime::vendor();

    REQUIRE(value.size()!=0u);

    // std::transform(value.begin(), value.end(),
    //                value.begin(),
    //                ::tolower);

    REQUIRE(value.find(expected_vendor)!=std::string::npos);

  }


  SECTION( "brand_right" ){

    auto value = compass::runtime::brand();

    REQUIRE(value.empty()!=true);
    REQUIRE_THAT(value, Catch::Matchers::Contains(expected_brand) );

  }

  SECTION( "device_name_right" ){

    auto value = compass::runtime::device_name();
    auto brand = compass::runtime::brand();

    if(expected_device_name.size()>0){
        REQUIRE(value.size() == expected_device_name.size());
        REQUIRE_THAT(value, Catch::Matchers::Contains(expected_device_name) );
    } else {
        REQUIRE(value.size()>=0);
        REQUIRE(value.size() <= brand.size());
    }

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

  SECTION( "has_sse_right_at_ct" ){

    auto value = compass::compiletime::has<compass::feature::sse()>::enabled;

    REQUIRE(true);//this just needs to compile

  }

  SECTION( "has_sse_right" ){

    auto value = compass::runtime::has(compass::feature::sse());

    REQUIRE(value==expected_has_sse);


  }

  SECTION( "has_sse2_right" ){

    auto value = compass::runtime::has(compass::feature::sse2());

    REQUIRE(value==expected_has_sse2);
    if(expected_has_sse2){
      REQUIRE(compass::compiletime::has<compass::feature::sse2>::enabled==expected_has_sse2);
    }

  }

  SECTION( "has_sse3_right" ){

    auto value = compass::runtime::has(compass::feature::sse3());

    REQUIRE(value==expected_has_sse3);
    if(expected_has_sse3)
      REQUIRE(compass::compiletime::has<compass::feature::sse3>::enabled==expected_has_sse3);

  }

  SECTION( "has_sse4_right" ){

    auto value = compass::runtime::has(compass::feature::sse4());

    REQUIRE(value==expected_has_sse4);
    if(expected_has_sse4)
      REQUIRE(compass::compiletime::has<compass::feature::sse4>::enabled==expected_has_sse4);

  }

  SECTION( "has_avx_right" ){

    auto value = compass::runtime::has(compass::feature::avx());

    REQUIRE(value==expected_has_avx);

  }

  SECTION( "has_multiple_features" ){

    auto value = compass::runtime::accumulate(compass::feature::avx(),compass::feature::sse4(),compass::feature::sse3());

    const bool expected = (expected_has_avx || expected_has_sse4 || expected_has_sse3 );
    REQUIRE(bool(value) == expected );
    std::bitset<3> mask((unsigned long)value);

    REQUIRE(mask[0] ==  expected_has_avx);
    REQUIRE(mask[1] ==  expected_has_sse4);
    REQUIRE(mask[2] ==  expected_has_sse3);

  }


  SECTION( "has_avx2_right" ){

    auto value = compass::runtime::has(compass::feature::avx2());

    REQUIRE(value==expected_has_avx2);

  }

  SECTION( "correct_l2_cache_size" ){

    auto value = compass::runtime::size::cache::level(2);

    REQUIRE(value > 0);
    if(expected_L2_size_kB){
      REQUIRE(value >> 10 ==expected_L2_size_kB);
    }

  }
}
