#include <spark_macros.hpp>
#include "../src/main.h"
#include <catch2/catch.hpp>


//will need custom epsilon for these tests

SPARK_TEST_CASE("test_sum", "Test that the sum function works.", "sum", "Sums doubles specified by a lambda"){
	REQUIRE(sum([](unsigned int i){
		return (double)i;
	},0,101) == Approx(5050.0));
}

SPARK_TEST_CASE ("test_complicated_factorial", "Test that the complicated_factorial function works.", "complicated_factorial", "Calculates factorial of integers"){
	REQUIRE(complicated_factorial(1) == Approx(1));
	REQUIRE(complicated_factorial(5) == Approx(120.0));
	REQUIRE(complicated_factorial(10) == Approx(3628800.0));
	REQUIRE(complicated_factorial(50) == Approx(3.0414093e+64));
}

SPARK_TEST_CASE ("test_very_complicated_factorial", "Test that the very_complicated_factorial function works.", "very_complicated_factorial", "Calculates factorial of positive doubles"){
	REQUIRE(very_complicated_factorial(1) == Approx(1).epsilon(0.1));
	REQUIRE(very_complicated_factorial(5) == Approx(120.0).margin(5.0));
	REQUIRE(very_complicated_factorial(10) == Approx(3628800.0).margin(100000));
	REQUIRE(very_complicated_factorial(50) == Approx(3.0414093e+64).margin(1e63));
	REQUIRE(very_complicated_factorial(2.5) == Approx(3.32335097045).epsilon(0.1));
	REQUIRE(very_complicated_factorial(0.5) == Approx(0.88622692545).epsilon(0.05));

}
