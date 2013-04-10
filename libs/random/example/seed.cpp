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
// #include <boost/mpl/print.hpp>

int
main(){
	static constexpr sprout::uniform_int_distribution<int> dist(100, 999);

	{
		static constexpr auto seed = 2013;
		static constexpr sprout::default_random_engine engine(seed);

		static_assert(engine() == 33832491, "");
		static_assert(dist(engine) == 114, "");
	}

	{
		static constexpr auto seed = 8379842;
		static constexpr sprout::default_random_engine engine(seed);

		static_assert(engine() == 1253567439, "");
		static_assert(dist(engine) == 625, "");
	}

	//
	// Compile time unique seed
	//
	{
		static constexpr auto seed = SPROUT_UNIQUE_SEED;
		std::cout << seed << std::endl;

		static constexpr sprout::default_random_engine engine(seed);
		std::cout << engine() << std::endl;
		std::cout << dist(engine) << std::endl;

		// compile time output
// 		typedef boost::mpl::print<boost::mpl::int_<seed>>::type unique_seed_type;
// 		typedef boost::mpl::print<boost::mpl::int_<engine()>>::type engine_type;
// 		typedef boost::mpl::print<boost::mpl::int_<dist(engine)>>::type dist_type;
	}

	return 0;
}
