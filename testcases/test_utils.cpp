#include "../src/utils.h"
#include <catch2/catch.hpp>
#include <spark_macros.hpp>

static const double E = 2.71828182846;

SPARK_TEST_CASE("test_pow","Test that pow function works", "pow_", "Find a^b."){
    REQUIRE(pow_(1.0,100) == Approx(1.0));
    REQUIRE(pow_(1.0,100.0) == Approx(1.0));
    REQUIRE(pow_(2.0,3.0) == Approx(8.0));
//    REQUIRE(pow_(-2.0,3.0) == Approx(-8.0));
    REQUIRE(pow_(2.0,(unsigned int)3) == Approx(8.0));
//    REQUIRE(pow_(-2.0,(unsigned int)3) == Approx(-8.0));
}

SPARK_TEST_CASE("test_log_e","Tests that the log base e of a number function.", "log_e","Takes the log base e of an umber"){
    REQUIRE(log_e(E) == Approx(1.0));
    REQUIRE(log_e(1.0) == Approx(0.0));
    REQUIRE(log_e(100.0) == Approx(4.60517));
}

SPARK_TEST_CASE("test_exp","Tests the exp/antilog function","exp_","Find the exp_ of a number."){
    REQUIRE(exp_(1.0) == Approx(E));
    REQUIRE(exp_(0.0) == Approx(1.0));
    REQUIRE(exp_(4.60517) == Approx(100.0));
}