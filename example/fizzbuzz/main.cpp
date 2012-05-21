//
// Sprout C++ Library
//
// Copyright (c) 2012
// bolero-MURAKAMI : http://d.hatena.ne.jp/boleros/
// osyo-manga : http://d.hatena.ne.jp/osyo-manga/
//
// Readme:
// https://github.com/osyo-manga/cpp-half/blob/master/README
//
// License:
// Boost Software License - Version 1.0
// <http://www.boost.org/LICENSE_1_0.txt>
//
#include <sprout/algorithm/transform.hpp>
#include <sprout/array.hpp>
#include <sprout/string.hpp>
#include <sprout/numeric/iota.hpp>
#include <sprout/pit.hpp>
#include <iostream>


struct fizzbuzz{
	typedef sprout::string<12> result_type;

	constexpr result_type
	operator ()(int n) const{
		return n % 15 == 0 ? sprout::to_string("FizzBuzz")
				: n %  3 == 0 ? sprout::to_string("Fizz")
				: n %  5 == 0 ? sprout::to_string("Buzz")
				: sprout::to_string(n);
	}
};


int
main(){
	typedef fizzbuzz::result_type string;

	//
	// Test
	//
	static_assert(fizzbuzz()( 1) == "1", "");
	static_assert(fizzbuzz()( 2) == "2", "");
	static_assert(fizzbuzz()( 3) == "Fizz", "");
	static_assert(fizzbuzz()( 5) == "Buzz", "");
	static_assert(fizzbuzz()(15) == "FizzBuzz", "");

	//
	// Sequence [1..15]
	//
	constexpr auto source = sprout::iota(
		sprout::pit<sprout::array<int, 15> >(),
		1
	);

	//
	// Transform to FizzBuzz
	//
	constexpr auto result = sprout::transform(
		sprout::begin(source),
		sprout::end(source),
		sprout::pit<sprout::array<string, 15> >(),
		fizzbuzz()
	);

	//
	// Check result
	//
	constexpr auto fizzbuzz_result = sprout::make_array<string>(
		sprout::to_string("1"),
		sprout::to_string("2"),
		sprout::to_string("Fizz"),
		sprout::to_string("4"),
		sprout::to_string("Buzz"),
		sprout::to_string("Fizz"),
		sprout::to_string("7"),
		sprout::to_string("8"),
		sprout::to_string("Fizz"),
		sprout::to_string("Buzz"),
		sprout::to_string("11"),
		sprout::to_string("Fizz"),
		sprout::to_string("13"),
		sprout::to_string("14"),
		sprout::to_string("FizzBuzz")
	);
	// Equal result sequence
	static_assert(result == fizzbuzz_result, "");

	//
	// Output
	//
	for(auto&& str : result){
		std::cout << str << ", ";
	}
	std::cout << std::endl;

	return 0;
}
