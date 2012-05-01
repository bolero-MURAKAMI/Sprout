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


int
main(){
	namespace w = sprout::weed;
	
	static constexpr auto max_string_size = 32;
	static constexpr auto space = *w::omit[ w::space ];
	static constexpr auto remove_space = *w::lim<max_string_size>(space >> w::char_);
	
	static constexpr auto source = sprout::to_string("  homu  :  mami=   10 ");
	static constexpr auto result = w::parse(
		sprout::begin(source), sprout::end(source),
		remove_space
	);

	static_assert(result.success(), "fail remove_space parse");
	static_assert(result.attr() == "homu:mami=10", "");

	return 0;
}
