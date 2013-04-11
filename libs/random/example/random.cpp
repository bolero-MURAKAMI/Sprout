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

//
// Compile Time Random
//
int
main(){
	//
	// Random engine
	//
	static constexpr sprout::hellekalek1995 engine;
	static_assert(engine()   == 2110608584, "");
	static_assert(engine()() == 239248507, "");

	// 
	// Distribution
	//
	static constexpr sprout::uniform_int_distribution<int> dist(100, 999);
	
	//
	// Get random value
	//
	// return int value
	static constexpr int n = *dist(engine);
	// or
	// operator int
// 	static constexpr int n = dist(engine);
	static_assert(n == 984, "");
	
	//
	// Next random value
	//
	static_assert(dist(engine)()       == 200, "");
	static_assert(dist(engine)()()     == 566, "");
	static_assert(dist(engine)()()()   == 255, "");
	static_assert(dist(engine)()()()() == 175, "");

	return 0;
}
