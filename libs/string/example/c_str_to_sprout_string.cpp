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
#include <sprout/string.hpp>

//
// C style string to Sprout.String
//
int
main(){
	
	constexpr char const* c_str = "homu";

	//
	// String length is required
	//
	constexpr auto length = sprout::char_traits<char>::length(c_str);
	static_assert(length == 4, "");
	
	//
	// To Sprout.String
	//
	constexpr auto str = sprout::string_from_c_str<length>( c_str );
	static_assert(std::is_same<sprout::string<4> const, decltype(str)>{}, "");
	static_assert(str == "homu", "");

	constexpr auto str2 = sprout::string_from_c_str<length>( c_str, 2 );
	static_assert(std::is_same<sprout::string<4> const, decltype(str2)>{}, "");
	static_assert(str2 == "ho", "");

	
	return 0;
}
