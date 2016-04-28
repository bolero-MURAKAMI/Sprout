//
// Sprout C++ Library
//
// Copyright (c) 2013
// bolero-MURAKAMI : http://d.hatena.ne.jp/boleros/
// osyo-manga : http://d.hatena.ne.jp/osyo-manga/
// 
// Readme:
// https://github.com/bolero-MURAKAMI/Sprout/blob/master/README
//
// License:
// Boost Software License - Version 1.0
// <http://www.boost.org/LICENSE_1_0.txt>
//
#include <sprout/random.hpp>
#include <sprout/array.hpp>
#include <sprout/algorithm.hpp>

int
main(){
	static constexpr sprout::default_random_engine engine;
	static constexpr sprout::uniform_smallint<int> dist(1, 6);

	static constexpr auto result = sprout::generate
		<sprout::array<int, 10> /* Result type */>
		(sprout::random::ccombine(engine, dist) /*Random generator*/)
		;

	static_assert(
		result == sprout::make_array<int>(1, 1, 5, 2, 4, 2, 6, 2, 5, 1),
		"");

	return 0;
}
