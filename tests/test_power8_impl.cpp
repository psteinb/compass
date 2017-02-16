#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TEST_POWER8_IMPL
#include "boost/test/unit_test.hpp"

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

#include "compass.hpp"
#include "compass_fixture.hpp"

BOOST_AUTO_TEST_SUITE( compass_fundamentals )

BOOST_AUTO_TEST_CASE( compass_works_at_runtime ){

  auto value = compass::runtime::works();

  BOOST_CHECK(value);

}

// BOOST_AUTO_TEST_CASE( compass_yields_vendor_name ){

//   auto value = compass::runtime::vendor();
//   BOOST_CHECK_NE(value.size(),0u);

// }
// BOOST_AUTO_TEST_SUITE_END()

// BOOST_FIXTURE_TEST_SUITE( machine_specific, host_reference )

// BOOST_AUTO_TEST_CASE( vendor_right  ){

//   auto value = compass::runtime::vendor();

//   BOOST_CHECK_NE(value.size(),0u);

//   std::transform(value.begin(), value.end(),
//          value.begin(),
//          ::tolower);

//   BOOST_CHECK(value.find(expected_vendor)!=std::string::npos);

// }

// BOOST_AUTO_TEST_CASE( ncores_right  ){

//   auto value = compass::runtime::ncores();

//   BOOST_CHECK_NE(value,0);
//   BOOST_CHECK_EQUAL(value,expected_ncores);
// }

// BOOST_AUTO_TEST_CASE( has_sse_right  ){

//   auto value = compass::runtime::has(compass::feature::sse());

//   BOOST_CHECK_EQUAL(value,expected_has_sse);

// }

// BOOST_AUTO_TEST_CASE( has_sse2_right  ){

//   auto value = compass::runtime::has(compass::feature::sse2());

//   BOOST_CHECK_EQUAL(value,expected_has_sse2);

// }

// BOOST_AUTO_TEST_CASE( has_sse3_right  ){

//   auto value = compass::runtime::has(compass::feature::sse3());

//   BOOST_CHECK_EQUAL(value,expected_has_sse3);

// }

// BOOST_AUTO_TEST_CASE( has_sse4_right  ){

//   auto value = compass::runtime::has(compass::feature::sse4());

//   BOOST_CHECK_EQUAL(value,expected_has_sse4);

// }

// BOOST_AUTO_TEST_CASE( has_avx_right  ){

//   auto value = compass::runtime::has(compass::feature::avx());

//   BOOST_CHECK_EQUAL(value,expected_has_avx);

// }


// BOOST_AUTO_TEST_CASE( has_avx2_right  ){

//   auto value = compass::runtime::has(compass::feature::avx2());

//   BOOST_CHECK_EQUAL(value,expected_has_avx2);

// }
BOOST_AUTO_TEST_SUITE_END()
