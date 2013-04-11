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
#include <iostream>

int
main(){
	//
	// Random engine
	//
	static constexpr sprout::default_random_engine engine;

	// 
	// Distribution
	//
	// 1 ~ 6
	{
		static constexpr sprout::uniform_int_distribution<> dist(1, 6);
		static_assert(dist(engine)       == 1, "");
		static_assert(dist(engine)()     == 1, "");
		static_assert(dist(engine)()()   == 5, "");
		static_assert(dist(engine)()()() == 3, "");
	}

	// 0.0 ~ 1.0
	{
		static constexpr sprout::uniform_real_distribution<double> dist(0.0, 1.0);
// 		static_assert(dist(engine) == 0.7.8259e-006, "");
// 		static_assert(dist(engine) == 0.131538, "");
// 		static_assert(dist(engine) == 0.755605, "");
// 		static_assert(dist(engine) == 0.45865, "");
		std::cout << dist(engine) << std::endl;
		std::cout << dist(engine)() << std::endl;
		std::cout << dist(engine)()() << std::endl;
		std::cout << dist(engine)()()() << std::endl;
	}

	// Returns true with probability 50%
	{
		static constexpr sprout::bernoulli_distribution<> dist(0.5);
		static_assert(dist(engine)       == 1, "");
		static_assert(dist(engine)()     == 1, "");
		static_assert(dist(engine)()()   == 0, "");
		static_assert(dist(engine)()()() == 1, "");
	}

	return 0;
}
