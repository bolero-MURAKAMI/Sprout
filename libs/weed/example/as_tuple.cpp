//
// Sprout C++ Library
//
// Copyright (c) 2012
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
#include <sprout/weed.hpp>


int
main(){
	namespace w = sprout::weed;

	static constexpr auto source = sprout::to_string("homu:mado");
	
	// String parser
	static constexpr auto item = *w::lim<4>(w::char_ - ':');
	
	
	//
	// If you do not want to use the as_tuple
	//
	{
		static constexpr auto parser = item >> ':' >> item;

		static constexpr auto result = w::parse(
			sprout::begin(source), sprout::end(source), parser
		);
		static_assert(result.success(), "");

		// !!!!
		static_assert(result.attr() == "homumado", "");
	}
	

	//
	// You need to use the as_tuple
	//
	{
		static constexpr auto parser = w::as_tuple[item] >> ':' >> w::as_tuple[item];

		static constexpr auto result = w::parse(
			sprout::begin(source), sprout::end(source), parser
		);
		static_assert(result.success(), "");

		static constexpr auto attr = result.attr();

		// OK
		static_assert(std::is_same<
			sprout::tuple<sprout::string<4>, sprout::string<4>> const,
			decltype(attr)
		>::value, "");
		static_assert(sprout::get<0>(attr) == "homu", "");
		static_assert(sprout::get<1>(attr) == "mado", "");
	}
	
	return 0;
}
