//
// Created by Peter Cong on 1/13/22.
//

#include <catch2/catch_test_macros.hpp>
#include <library.hpp>

TEST_CASE( "array_util" )
{
    SECTION( "arr_fill" )
    {
        constexpr auto arr = arr_fill<10>(5);
        REQUIRE(arr == std::array{5, 5, 5, 5, 5, 5, 5, 5, 5, 5});
    }
    SECTION( "arr_seq" )
    {
        constexpr auto arr = arr_seq<10>(3);
        REQUIRE(arr == std::array{3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
    }
    SECTION( "multi_invoke" )
    {
        REQUIRE(multi_invoke<5>([](int i)
                                { return i + 1; }, 0) == 5);
    }
    SECTION( "arr_gen" )
    {
        constexpr auto arr = arr_gen<10>(2, [](int i){ return i * 2; });
        REQUIRE(arr == std::array{2, 4, 8, 16, 32, 64, 128, 256, 512, 1024});
    }
    SECTION( "arr_equal true")
    {
        constexpr auto True = arr_equal(arr_seq<3>(1), std::array{1,2,3});
        REQUIRE(True == true);
    }
    SECTION( "arr_equal false")
    {
        constexpr auto False = arr_equal(arr_seq<3>(1), std::array{3,2,1});
        REQUIRE(False == false);
    }
}