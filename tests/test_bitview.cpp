#include "catch.hpp"

#include "detail/bit_view.hpp"

#include <bitset>

TEST_CASE( "basics" ){

  SECTION( "construction" ){

    int num = 7;
    compass::utility::bit_view<int> view(num);

    REQUIRE(view.value_ == 7);

  }

  SECTION( "assignment" ){

    int num = 7;
    compass::utility::bit_view<int> view(num);
    compass::utility::bit_view<int> temp = view;

    REQUIRE(temp.value_ == 7);

  }

  SECTION( "copy" ){

    int num = 7;
    compass::utility::bit_view<int> view(num);
    compass::utility::bit_view<int> temp(view);

    REQUIRE(temp.value_ == 7);

  }
}


TEST_CASE( "logical" ){

  SECTION( "single_test_within_bounds" ){
    int num = 42;

    std::bitset<32> bs_num(num);
    compass::utility::bit_view<int> view(num);


    REQUIRE(bs_num.any());
    REQUIRE(bs_num.test(1) == view.test(1));
  }

  SECTION( "test_all_within_bounds" ){

    int num = 42;

    std::bitset<32> bs_num(num);
    compass::utility::bit_view<int> view(num);

    for(int i = 0;i<32;++i)
      REQUIRE(bs_num.test(i) == view.test(i));
  }

  SECTION( "test_outof_bounds" ){

    int num = 42;

    compass::utility::bit_view<int> view(num);

    REQUIRE(view.test(50)!=true);
  }

}

TEST_CASE( "mutation" ){

SECTION( "set_lsb" ){

  int num = 42;

  compass::utility::bit_view<int> view(num);
  view.set(0);

  REQUIRE(num!=42);
}

SECTION( "set_msb" ){

  int num = 42;

  compass::utility::bit_view<int> view(num);
  view.set(31);

  REQUIRE(num!=42);
}

SECTION( "set_lsb_correct" ){

  int num = 42;

  std::bitset<32> bs_num(num);
  bs_num.set(0);
  int rnum = bs_num.to_ulong();

  compass::utility::bit_view<int> view(num);
  view.set(0);

  REQUIRE(rnum!=42);
  REQUIRE(num !=42);
  REQUIRE(num==rnum);
}

SECTION( "set_msb_correct" ){

  int num = 42;

  std::bitset<32> bs_num(num);
  bs_num.set(31);
  int rnum = bs_num.to_ulong();

  compass::utility::bit_view<int> view(num);
  view.set(31);


  REQUIRE(num !=42);
  REQUIRE(rnum!=42);
  REQUIRE(num==rnum);
}

}
