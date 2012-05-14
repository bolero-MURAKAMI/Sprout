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
#include <sprout/weed.hpp>
#include <boost/mpl/print.hpp>
#include <boost/mpl/int.hpp>
#include <iostream>

//
// __TIME__ Parser
//
int
main(){
	namespace w = sprout::weed;
	
	//
	// __TIME__ to Sprout.String
	//
	static constexpr auto time = sprout::to_string(__TIME__);
// 	static constexpr auto time = sprout::to_string("23:22:45");
	

	//
	// parse __TIME__
	//
	constexpr auto expr = w::int_ >> ':' >> w::int_ >> ':' >> w::int_;
	static constexpr auto result = w::parse(time.begin(), time.end(), parser);
	static_assert(result.success(), "failed parse");
	
	
	//
	// get result
	//
	static constexpr sprout::array<long long int, 3> result_attr = result.attr();
	static constexpr auto hour    = result_attr[0];
	static constexpr auto minute = result_attr[1];
	static constexpr auto second  = result_attr[2];

// 	static_assert(hour   == 23, "");
// 	static_assert(minute == 22, "");
// 	static_assert(second == 45, "");

	std::cout << hour << std::endl;
	std::cout << minute << std::endl;
	std::cout << second << std::endl;
	
	
	//
	// compile time output
	//
	namespace m = boost::mpl;
	typedef m::print<m::int_<hour>>::type   hour_;
	typedef m::print<m::int_<minute>>::type minute_;
	typedef m::print<m::int_<second>>::type second_;

	return 0;
}
