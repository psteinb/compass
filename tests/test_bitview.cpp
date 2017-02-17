#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TEST_BITVIEW
#include "boost/test/unit_test.hpp"

#include <bitset>


#include "detail/bit_view.hpp"


BOOST_AUTO_TEST_SUITE( basics )

BOOST_AUTO_TEST_CASE( construction ){

  int num = 7;
  compass::utility::bit_view<int> view(num);

  BOOST_CHECK(view.value_ == 7);

}

BOOST_AUTO_TEST_CASE( assignment ){

  int num = 7;
  compass::utility::bit_view<int> view(num);
  compass::utility::bit_view<int> temp = view;

  BOOST_CHECK(temp.value_ == 7);

}

BOOST_AUTO_TEST_CASE( copy ){

  int num = 7;
  compass::utility::bit_view<int> view(num);
  compass::utility::bit_view<int> temp(view);

  BOOST_CHECK(temp.value_ == 7);

}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE( logical )

BOOST_AUTO_TEST_CASE( single_test_within_bounds ){
  int num = 42;

  std::bitset<32> bs_num(num);
  compass::utility::bit_view<int> view(num);


  BOOST_CHECK(bs_num.any());
  BOOST_CHECK_EQUAL(bs_num.test(1),view.test(1));
}

BOOST_AUTO_TEST_CASE( test_all_within_bounds ){

  int num = 42;

  std::bitset<32> bs_num(num);
  compass::utility::bit_view<int> view(num);

  for(int i = 0;i<32;++i)
    BOOST_CHECK_EQUAL(bs_num.test(i),view.test(i));
}

BOOST_AUTO_TEST_CASE( test_outof_bounds ){

  int num = 42;

  compass::utility::bit_view<int> view(num);

  BOOST_CHECK_NE(view.test(50),true);
}


BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE( mutation )

BOOST_AUTO_TEST_CASE( set_lsb ){

  int num = 42;

  compass::utility::bit_view<int> view(num);
  view.set(0);

  BOOST_CHECK_NE(num,42);
}

BOOST_AUTO_TEST_CASE( set_msb ){

  int num = 42;

  compass::utility::bit_view<int> view(num);
  view.set(31);

  BOOST_CHECK_NE(num,42);
}

BOOST_AUTO_TEST_CASE( set_lsb_correct ){

  int num = 42;

  std::bitset<32> bs_num(num);
  bs_num.set(0);
  int rnum = bs_num.to_ulong();

  compass::utility::bit_view<int> view(num);
  view.set(0);

  BOOST_CHECK_NE(rnum,42);
  BOOST_CHECK_NE(num,42);
  BOOST_CHECK_EQUAL(num,rnum);
}

BOOST_AUTO_TEST_CASE( set_msb_correct ){

  int num = 42;

  std::bitset<32> bs_num(num);
  bs_num.set(31);
  int rnum = bs_num.to_ulong();

  compass::utility::bit_view<int> view(num);
  view.set(31);


  BOOST_CHECK_NE(num,42);
  BOOST_CHECK_NE(rnum,42);
  BOOST_CHECK_EQUAL(num,rnum);
}


BOOST_AUTO_TEST_SUITE_END()
